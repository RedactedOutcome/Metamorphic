#include "Metamorphic/pch.h"
#include "Metamorphic/Resources/ResourceManager.h"
#include "Metamorphic/Core/Logger.h"

namespace Metamorphic{
    ResourceManager::ResourceManager() noexcept{
        
    }
    //ResourceManager::ResourceManager(EventDispatcher& dispatcher) noexcept : m_EventDispatcher(&dispatcher){  }

    ResourceManager::~ResourceManager()noexcept{
        StopSaving();
    }
    void ResourceManager::SetMapPath(const HBuffer& path)noexcept{
        m_MapPath = path;
        m_MapPath.MakeSafeString();
    }

    void ResourceManager::SetMapPath(HBuffer&& path)noexcept{
        m_MapPath = std::move(path);
        m_MapPath.MakeSafeString();
    }

    /// @brief TODO: have use m_MapStream and m_ResourcesStream
    /// @return 
    ResourceManagerError ResourceManager::LoadMap()noexcept{
        std::filesystem::path path(m_MapPath.GetCStr());
        path.replace_extension(".cprm");
        std::ifstream file(path, std::ios::binary | std::ios::ate);

        if(!file){
            file.close();
            return ResourceManagerError::FailedToLoadFilePath;
        }
        size_t mapSize = file.tellg();
        file.seekg(std::ios::beg);

        char* rawData = new char[mapSize];
        file.read(rawData, mapSize);
        if(!rawData)return ResourceManagerError::FailedAllocation;

        HBuffer data(rawData, mapSize, mapSize, true, true);
        uint16_t pathSize;
        char resourceMapMagicNumbers[3] = {0x16, 0x17, 0x62};
        if(data.StartsWith(resourceMapMagicNumbers, 3) == false){
            file.close();
            return ResourceManagerError::CorruptedResourceMap;
        }
        if(!data.ExtractUInt16(3, &pathSize)){
            file.close();
            return ResourceManagerError::CorruptedResourceMap;
        }
        m_ResourcesPath = data.SubString(5, pathSize);
        if(m_ResourcesPath.GetSize() != pathSize){
            file.close();
            return ResourceManagerError::CorruptedResourceMap;
        }
        m_ResourceMap.clear();
        size_t i = 5 + pathSize;
        while(i <= mapSize){
            uint16_t characterCount;
            if(!data.ExtractUInt16(i, &characterCount)){
                break;
            }
            i+=2;
            HBuffer resourceName = data.SubString(i, characterCount);
            if(resourceName.GetSize() != characterCount){
                file.close();
                return ResourceManagerError::CorruptedResourceMap;
            }
            i+=characterCount;
            uint32_t resourceOffset;
            if(!data.ExtractUInt32(i, &resourceOffset)){
                file.close();
                return ResourceManagerError::CorruptedResourceMap;
            }
            ResourceOffsets offset {static_cast<uint32_t>(i), resourceOffset};
            m_ResourceMap.insert(std::make_pair(std::move(resourceName), offset));
            i+=4;
        }
        file.close();
        m_IsMapLoaded = true;
        return ResourceManagerError::None;
    }

    ResourceManagerError ResourceManager::LoadResourcesBuffer() noexcept{
        m_LoadedResources = false;

        std::filesystem::path resourcePath(m_ResourcesPath.GetCStr());
        resourcePath.replace_extension(".cpr");
        std::ifstream resourceFile(resourcePath, std::ios::binary | std::ios::ate);

        if(!resourceFile){
            return ResourceManagerError::FailedToLoadFilePath;
        }

        size_t size = resourceFile.tellg();
        resourceFile.seekg(std::ios::beg);
        m_ResourcesBuffer.Reserve(size);
        m_ResourcesBuffer.SetSize(size);
        resourceFile.read(m_ResourcesBuffer.GetData(), size);
        resourceFile.close();

        /// Verify Resources
        char magicNumbers[3] = {0x15, 0x18, 0x61};
        if(m_ResourcesBuffer.StartsWith(magicNumbers, 3) == false){
            return ResourceManagerError::CorruptedResources;
        }
        if(m_ResourcesBuffer.StartsWith(3, "0.0.1", 5) == false){
            return ResourceManagerError::UnsupportedResourceVersion;
        }
        m_LoadedResources = true;

        return ResourceManagerError::None;
    }

    ResourceManagerError ResourceManager::StartSaving(HBuffer& errorMessage)noexcept{
        /// Resources Map
        std::filesystem::path mapPath(m_MapPath.GetCStr());
        mapPath.replace_extension(".cprm");

        if (!std::filesystem::exists(mapPath)) {
            // Create empty file first
            std::ofstream tmp(mapPath, std::ios::binary);
            tmp.close();
        }

        m_MapStream = std::fstream(mapPath, std::ios::in | std::ios::binary | std::ios::out);
        char resourcesMapMagicNumbers[3] = {0x16, 0x17, 0x62};
        bool writeMapDefaultHeaders = true;

        m_MapStream.seekg(0, std::ios::end);
        size_t mapSize = m_MapStream.tellg();
        if(m_MapStream.is_open() && mapSize > 0){
            m_MapStream.seekg(0, std::ios::beg);
            writeMapDefaultHeaders = false;
            char test[3];
            m_MapStream.read(test, 3);
            if(!m_MapStream){
                m_MapStream.close();
                errorMessage = "Failed to read enough bytes for file map";
                return ResourceManagerError::CorruptedResourceMap;
            }
            if(strncmp(resourcesMapMagicNumbers, test, 3) != 0){
                m_MapStream.close();
                errorMessage = "File Map has Invalid Magic Numbers";
                return ResourceManagerError::CorruptedResourceMap;
            }

            /// Get Resources Path Size
            uint16_t resourcePathSize;
            m_MapStream.read(reinterpret_cast<char*>(&resourcePathSize), sizeof(uint16_t));
            if(!m_MapStream){
                m_MapStream.close();
                return ResourceManagerError::CorruptedResourceMap;
            }
            /// Get Resource Path from non null terminated string
            size_t capacity = static_cast<size_t>(resourcePathSize + 1);
            char* string = new char[capacity];
            m_MapStream.read(string, resourcePathSize);
            if(!m_MapStream){
                m_MapStream.close();
                delete string;
                errorMessage = "Failed to get resource path from file map";
                return ResourceManagerError::CorruptedResourceMap;
            }
            m_ResourcesPath = HBuffer(string, resourcePathSize, capacity, true, true);
            m_ResourcesBuffer.Free();
            m_LoadedResources = false;
            m_ResourceMap.clear();

            /// @brief Putting all resources onto map incase rewrite
            while(true){
                /// Get Resource Name Character Count
                uint16_t size;
                m_MapStream.read(reinterpret_cast<char*>(&size), sizeof(uint16_t));
                if(!m_MapStream){
                    /// No more data to read or just file corruption
                    size_t at = m_MapStream.tellg();
                    m_MapStream.seekg(std::ios::end);
                    size_t size = m_MapStream.tellg();
                    if(size - at > 0){
                        errorMessage = "resource map index failed to get resource name character count";
                        return ResourceManagerError::CorruptedResourceMapIndex;
                    }
                    break;
                }

                char* stringData = new char[size + 1];
                stringData[size] = '\00';
                m_MapStream.read(stringData, size);

                if(!m_MapStream){
                    /// Failed to read Resource Name Corrupted File
                    delete stringData;
                    errorMessage = "Failed to read resource path string from resource map";
                    return ResourceManagerError::CorruptedResourceMapIndex;
                }
                HBuffer resourceName(stringData, size, size + 1, true, true);
                if(m_ResourceMap.find(resourceName) != m_ResourceMap.end()){
                    /// Duplicate Resources Names
                    return ResourceManagerError::AmbiguousResource;
                }
                uint32_t mapOffset = m_MapStream.tellg();
                uint32_t resourceOffset = 0;
                m_MapStream.read(reinterpret_cast<char*>(&resourceOffset), sizeof(uint32_t));
                if(!m_MapStream){
                    return ResourceManagerError::CorruptedResourceMapIndex;
                }
                ResourceOffsets resourceOffsets = {mapOffset, resourceOffset};

                m_ResourceMap.insert(std::make_pair(std::move(resourceName), resourceOffsets));
            }

            m_MapStream.seekp(0, std::ios::end);
        }

        /// Setting Resources Path
        if(m_ResourcesPath.GetSize() < 1){
            m_ResourcesPath = m_MapPath;
        }
        std::filesystem::path resourcesPath(m_ResourcesPath.GetCStr());
        resourcesPath.replace_extension(".cpr");

        if (!std::filesystem::exists(resourcesPath)) {
            // Create empty file first
            std::ofstream tmp(resourcesPath, std::ios::binary);
            tmp.close();
        }

        /// Writing Headers for Map if needed
        if(writeMapDefaultHeaders){
            m_MapStream.seekp(0, std::ios::beg);
            m_MapStream.write(resourcesMapMagicNumbers, 3);
            std::string resourcePathString = resourcesPath.string();
            uint16_t size = static_cast<uint16_t>(resourcePathString.size());
            m_MapStream.write(reinterpret_cast<char*>(&size), sizeof(uint16_t));
            m_MapStream.write(resourcePathString.data(), size);
        }
        m_IsMapLoaded = true;
        /// Resources
        /// Checking if there is already existing resources
        m_ResourcesStream = std::fstream(resourcesPath, std::ios::binary | std::ios::in | std::ios::out);
        
        char resourceMagicNumbers[3] = {0x15, 0x18, 0x61};
        bool addHeaders = true;

        m_ResourcesStream.seekg(0, std::ios::end);
        if(m_ResourcesStream.tellg() > 0){
            m_ResourcesStream.seekg(0, std::ios::beg);
            /// Check if it valid
            char test[8];
            m_ResourcesStream.read(test, 8);
            if(!m_ResourcesStream){
                errorMessage = "Failed to read enough bytes for resources magic number and version";
                return ResourceManagerError::CorruptedResources;
            }
            if(strncmp(test, resourceMagicNumbers, 3) != 0){
                errorMessage = "resources had invalid magic number";
                return ResourceManagerError::CorruptedResources;
            }
            if(strncmp(test + 3, "0.0.1", 5) != 0){
                errorMessage = "resources had unsupported version";
                return ResourceManagerError::UnsupportedResourceVersion;
            }

            m_ResourcesStream.seekg(0, std::ios::end);
            /// TODO: check if there are any necessary resources that must exist via m_ResourceMap
            addHeaders = false;
            m_WriteOffset = m_ResourcesStream.tellg();
        }

        if(addHeaders){
            /// File just created or corrupted.
            m_ResourcesStream.seekp(0, std::ios::beg);
            m_ResourcesStream.write(resourceMagicNumbers, 3);
            m_ResourcesStream.write("0.0.1", 5);
            m_WriteOffset = m_ResourcesStream.tellp();
        }

        if(m_LoadWholeBuffer){
            m_ResourcesStream.seekg(0, std::ios::end);
            size_t fileSize = m_ResourcesStream.tellg();
            m_ResourcesStream.seekg(0, std::ios::beg);
            m_ResourcesBuffer.Reserve(fileSize);
            m_ResourcesStream.read(m_ResourcesBuffer.GetData(), fileSize);
            if(!m_ResourcesStream){
                /// TODO: have more error codes.
                return ResourceManagerError::CorruptedResourceMap;
            }
            m_LoadedResources = true;
        }

        return ResourceManagerError::None;
    }
    void ResourceManager::StopSaving()noexcept{
        if(m_MapStream.is_open())m_MapStream.close();
        if(m_ResourcesStream.is_open())m_ResourcesStream.close();
    }

    ResourceManagerError ResourceManager::AppendResource(const HBuffer& name, const HBuffer& data)noexcept{
        if(!m_MapStream.is_open())
            return ResourceManagerError::FailedToWriteToMap;
        if(!m_ResourcesStream.is_open())
            return ResourceManagerError::FailedToWriteToResources;
        auto iterator = m_ResourceMap.find(name);
        if(iterator != m_ResourceMap.end()){
            /// ReWrite Resources
            /// @brief erase current resource and write all resources after it
            ResourceOffsets resourceOffsets = iterator->second;
            m_WriteOffset = resourceOffsets.m_ResourcesOffset;
            
            /// Sort lowest to highest offset so no resource gets overwriten.
            std::vector<std::unordered_map<HBuffer, ResourceOffsets>::iterator> offsets;
            for (auto it = m_ResourceMap.begin(); it != m_ResourceMap.end(); ++it) {
                uint32_t offset = it->second.m_ResourcesOffset;
                if(offset <= m_WriteOffset)continue;

                for(size_t i = 0; i < offsets.size(); i++){
                    if(offset < offsets[i]->second.m_ResourcesOffset){
                        offsets.insert(offsets.begin() + i, it);
                        break;
                    }
                }
            }

            const int tempRawSize = 3200;
            char tempRaw[tempRawSize];
            HBuffer temp(tempRaw, tempRawSize, tempRawSize, false, false);

            for(size_t i = 0; i < offsets.size(); i++){
                ResourceOffsets otherOffsets = offsets[i]->second;
                m_ResourcesStream.seekg(0, otherOffsets.m_ResourcesOffset);
                uint32_t resourceSize;
                m_ResourcesStream.read(reinterpret_cast<char*>(&resourceSize), sizeof(uint32_t));
                if(!m_ResourcesStream){
                    return ResourceManagerError::EndOfFile;
                }
                temp.Reserve(resourceSize);
                m_ResourcesStream.read(temp.GetData(), resourceSize);
                if(!m_ResourcesStream){
                    return ResourceManagerError::EndOfFile;
                }

                m_ResourcesStream.seekg(m_WriteOffset, std::ios::beg);
                m_ResourcesStream.write(reinterpret_cast<char*>(&resourceSize), sizeof(uint32_t));
                m_ResourcesStream.write(temp.GetData(), resourceSize);

                m_MapStream.seekg(otherOffsets.m_MapOffset, std::ios::beg);
                m_MapStream.write(reinterpret_cast<char*>(m_WriteOffset), sizeof(uint32_t));
                m_WriteOffset+=sizeof(uint32_t) + resourceSize;
            }
            m_ResourcesStream.seekp(m_WriteOffset, std::ios::beg);
            uint32_t resourceSize = static_cast<uint32_t>(data.GetSize());
            m_ResourcesStream.write(reinterpret_cast<char*>(&resourceSize), sizeof(uint32_t));
            m_ResourcesStream.write(data.GetData(), resourceSize);

            m_MapStream.seekg(0, resourceOffsets.m_MapOffset);
            m_MapStream.write(reinterpret_cast<char*>(&m_WriteOffset), sizeof(uint32_t));
            return ResourceManagerError::None;
        }
        m_ResourcesStream.seekp(0, std::ios::end);
        m_MapStream.seekp(0, std::ios::end);

        size_t mapOffset = m_MapStream.tellp();
        size_t resourcesOffset = m_ResourcesStream.tellg();

        uint32_t dataSize = static_cast<uint32_t>(data.GetSize());
        m_ResourcesStream.write(reinterpret_cast<char*>(&dataSize), sizeof(uint32_t));
        m_ResourcesStream.write(data.GetData(), dataSize);
        
        /// Write resource onto map
        uint16_t resourceNameSize = static_cast<uint16_t>(name.GetSize());
        m_MapStream.write(reinterpret_cast<char*>(&resourceNameSize), sizeof(uint16_t));
        m_MapStream.write(name.GetData(), resourceNameSize);
        m_MapStream.write(reinterpret_cast<char*>(&m_WriteOffset), sizeof(uint32_t));
        m_WriteOffset+=data.GetSize();

        ResourceOffsets offsets{mapOffset, resourcesOffset};
        m_ResourceMap.insert(std::make_pair(std::move(name), offsets));
        return ResourceManagerError::None;
    }
}