#include "Metamorphic/pch.h"
#include "Metamorphic/Assets/AssetManager.h"
#include "Metamorphic/Core/Logger.h"

namespace Metamorphic{
    AssetManager::AssetManager() noexcept{
        
    }
    //AssetManager::AssetManager(EventDispatcher& dispatcher) noexcept : m_EventDispatcher(&dispatcher){  }

    AssetManager::~AssetManager()noexcept{
        StopSaving();
    }
    void AssetManager::SetMapPath(const HBuffer& path)noexcept{
        m_MapPath = path;
        m_MapPath.MakeSafeString();
    }

    void AssetManager::SetMapPath(HBuffer&& path)noexcept{
        m_MapPath = std::move(path);
        m_MapPath.MakeSafeString();
    }

    /// @brief TODO: have use m_MapStream and m_AssetsStream
    /// @return 
    AssetManagerError AssetManager::LoadMap()noexcept{
        std::filesystem::path path(m_MapPath.GetCStr());
        path.replace_extension(".cprm");
        std::ifstream file(path, std::ios::binary | std::ios::ate);

        if(!file){
            file.close();
            return AssetManagerError::FailedToLoadFilePath;
        }
        size_t mapSize = file.tellg();
        file.seekg(std::ios::beg);

        char* rawData = new char[mapSize];
        file.read(rawData, mapSize);
        if(!rawData)return AssetManagerError::FailedAllocation;

        HBuffer data(rawData, mapSize, mapSize, true, true);
        uint16_t pathSize;
        char assetMapMagicNumbers[3] = {0x16, 0x17, 0x62};
        if(data.StartsWith(assetMapMagicNumbers, 3) == false){
            file.close();
            return AssetManagerError::CorruptedAssetMap;
        }
        if(!data.ExtractUInt16(3, &pathSize)){
            file.close();
            return AssetManagerError::CorruptedAssetMap;
        }
        m_AssetsPath = data.SubString(5, pathSize);
        if(m_AssetsPath.GetSize() != pathSize){
            file.close();
            return AssetManagerError::CorruptedAssetMap;
        }
        m_AssetsMap.clear();
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
                return AssetManagerError::CorruptedAssetMap;
            }
            i+=characterCount;
            uint32_t resourceOffset;
            if(!data.ExtractUInt32(i, &resourceOffset)){
                file.close();
                return AssetManagerError::CorruptedAssetMap;
            }
            assetOffsets offset {static_cast<uint32_t>(i), resourceOffset};
            m_AssetsMap.insert(std::make_pair(std::move(resourceName), offset));
            i+=4;
        }
        file.close();
        m_IsMapLoaded = true;
        return AssetManagerError::None;
    }

    AssetManagerError AssetManager::LoadAssetsBuffer() noexcept{
        m_LoadedAssets = false;

        std::filesystem::path resourcePath(m_AssetsPath.GetCStr());
        resourcePath.replace_extension(".cpr");
        std::ifstream resourceFile(resourcePath, std::ios::binary | std::ios::ate);

        if(!resourceFile){
            return AssetManagerError::FailedToLoadFilePath;
        }

        size_t size = resourceFile.tellg();
        resourceFile.seekg(std::ios::beg);
        m_AssetsBuffer.Reserve(size);
        m_AssetsBuffer.SetSize(size);
        resourceFile.read(m_AssetsBuffer.GetData(), size);
        resourceFile.close();

        /// Verify Assets
        char magicNumbers[3] = {0x15, 0x18, 0x61};
        if(m_AssetsBuffer.StartsWith(magicNumbers, 3) == false){
            return AssetManagerError::CorruptedAssets;
        }
        if(m_AssetsBuffer.StartsWith(3, "0.0.1", 5) == false){
            return AssetManagerError::UnsupportedResourceVersion;
        }
        m_LoadedAssets = true;

        return AssetManagerError::None;
    }

    AssetManagerError AssetManager::StartSaving(HBuffer& errorMessage)noexcept{
        /// Assets Map
        std::filesystem::path mapPath(m_MapPath.GetCStr());
        mapPath.replace_extension(".cprm");

        if (!std::filesystem::exists(mapPath)) {
            // Create empty file first
            std::ofstream tmp(mapPath, std::ios::binary);
            tmp.close();
        }

        m_MapStream = std::fstream(mapPath, std::ios::in | std::ios::binary | std::ios::out);
        char assetsMapMagicNumbers[3] = {0x16, 0x17, 0x62};
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
                return AssetManagerError::CorruptedAssetMap;
            }
            if(strncmp(assetsMapMagicNumbers, test, 3) != 0){
                m_MapStream.close();
                errorMessage = "File Map has Invalid Magic Numbers";
                return AssetManagerError::CorruptedAssetMap;
            }

            /// Get Assets Path Size
            uint16_t resourcePathSize;
            m_MapStream.read(reinterpret_cast<char*>(&resourcePathSize), sizeof(uint16_t));
            if(!m_MapStream){
                m_MapStream.close();
                return AssetManagerError::CorruptedAssetMap;
            }
            /// Get Resource Path from non null terminated string
            size_t capacity = static_cast<size_t>(resourcePathSize + 1);
            char* string = new char[capacity];
            m_MapStream.read(string, resourcePathSize);
            if(!m_MapStream){
                m_MapStream.close();
                delete string;
                errorMessage = "Failed to get asset path from file map";
                return AssetManagerError::CorruptedAssetMap;
            }
            m_AssetsPath = HBuffer(string, resourcePathSize, capacity, true, true);
            m_AssetsBuffer.Free();
            m_LoadedAssets = false;
            m_AssetsMap.clear();

            /// @brief Putting all assets onto map incase rewrite
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
                        errorMessage = "asset map index failed to get asset name character count";
                        return AssetManagerError::CorruptedAssetMapIndex;
                    }
                    break;
                }

                char* stringData = new char[size + 1];
                stringData[size] = '\00';
                m_MapStream.read(stringData, size);

                if(!m_MapStream){
                    /// Failed to read Resource Name Corrupted File
                    delete stringData;
                    errorMessage = "Failed to read asset path string from asset map";
                    return AssetManagerError::CorruptedAssetMapIndex;
                }
                HBuffer resourceName(stringData, size, size + 1, true, true);
                if(m_AssetsMap.find(resourceName) != m_AssetsMap.end()){
                    /// Duplicate Assets Names
                    return AssetManagerError::AmbiguousResource;
                }
                uint32_t mapOffset = m_MapStream.tellg();
                uint32_t resourceOffset = 0;
                m_MapStream.read(reinterpret_cast<char*>(&resourceOffset), sizeof(uint32_t));
                if(!m_MapStream){
                    return AssetManagerError::CorruptedAssetMapIndex;
                }
                assetOffsets assetOffsets = {mapOffset, resourceOffset};

                m_AssetsMap.insert(std::make_pair(std::move(resourceName), assetOffsets));
            }

            m_MapStream.seekp(0, std::ios::end);
        }

        /// Setting Assets Path
        if(m_AssetsPath.GetSize() < 1){
            m_AssetsPath = m_MapPath;
        }
        std::filesystem::path assetsPath(m_AssetsPath.GetCStr());
        assetsPath.replace_extension(".cpr");

        if (!std::filesystem::exists(assetsPath)) {
            // Create empty file first
            std::ofstream tmp(assetsPath, std::ios::binary);
            tmp.close();
        }

        /// Writing Headers for Map if needed
        if(writeMapDefaultHeaders){
            m_MapStream.seekp(0, std::ios::beg);
            m_MapStream.write(assetsMapMagicNumbers, 3);
            std::string resourcePathString = assetsPath.string();
            uint16_t size = static_cast<uint16_t>(resourcePathString.size());
            m_MapStream.write(reinterpret_cast<char*>(&size), sizeof(uint16_t));
            m_MapStream.write(resourcePathString.data(), size);
        }
        m_IsMapLoaded = true;
        /// Assets
        /// Checking if there is already existing assets
        m_AssetsStream = std::fstream(assetsPath, std::ios::binary | std::ios::in | std::ios::out);
        
        char resourceMagicNumbers[3] = {0x15, 0x18, 0x61};
        bool addHeaders = true;

        m_AssetsStream.seekg(0, std::ios::end);
        if(m_AssetsStream.tellg() > 0){
            m_AssetsStream.seekg(0, std::ios::beg);
            /// Check if it valid
            char test[8];
            m_AssetsStream.read(test, 8);
            if(!m_AssetsStream){
                errorMessage = "Failed to read enough bytes for assets magic number and version";
                return AssetManagerError::CorruptedAssets;
            }
            if(strncmp(test, resourceMagicNumbers, 3) != 0){
                errorMessage = "assets had invalid magic number";
                return AssetManagerError::CorruptedAssets;
            }
            if(strncmp(test + 3, "0.0.1", 5) != 0){
                errorMessage = "assets had unsupported version";
                return AssetManagerError::UnsupportedResourceVersion;
            }

            m_AssetsStream.seekg(0, std::ios::end);
            /// TODO: check if there are any necessary assets that must exist via m_AssetsMap
            addHeaders = false;
            m_WriteOffset = m_AssetsStream.tellg();
        }

        if(addHeaders){
            /// File just created or corrupted.
            m_AssetsStream.seekp(0, std::ios::beg);
            m_AssetsStream.write(resourceMagicNumbers, 3);
            m_AssetsStream.write("0.0.1", 5);
            m_WriteOffset = m_AssetsStream.tellp();
        }

        if(m_LoadWholeBuffer){
            m_AssetsStream.seekg(0, std::ios::end);
            size_t fileSize = m_AssetsStream.tellg();
            m_AssetsStream.seekg(0, std::ios::beg);
            m_AssetsBuffer.Reserve(fileSize);
            m_AssetsStream.read(m_AssetsBuffer.GetData(), fileSize);
            if(!m_AssetsStream){
                /// TODO: have more error codes.
                return AssetManagerError::CorruptedAssetMap;
            }
            m_LoadedAssets = true;
        }

        return AssetManagerError::None;
    }
    void AssetManager::StopSaving()noexcept{
        if(m_MapStream.is_open())m_MapStream.close();
        if(m_AssetsStream.is_open())m_AssetsStream.close();
    }

    AssetManagerError AssetManager::AppendAsset(const HBuffer& name, const HBuffer& data)noexcept{
        if(!m_MapStream.is_open())
            return AssetManagerError::FailedToWriteToMap;
        if(!m_AssetsStream.is_open())
            return AssetManagerError::FailedToWriteToAssets;
        auto iterator = m_AssetsMap.find(name);
        if(iterator != m_AssetsMap.end()){
            /// ReWrite Assets
            /// @brief erase current asset and write all assets after it
            assetOffsets assetOffsets = iterator->second;
            m_WriteOffset = assetOffsets.m_AssetsOffset;
            
            /// Sort lowest to highest offset so no asset gets overwriten.
            std::vector<std::unordered_map<HBuffer, assetOffsets>::iterator> offsets;
            for (auto it = m_AssetsMap.begin(); it != m_AssetsMap.end(); ++it) {
                uint32_t offset = it->second.m_AssetsOffset;
                if(offset <= m_WriteOffset)continue;

                for(size_t i = 0; i < offsets.size(); i++){
                    if(offset < offsets[i]->second.m_AssetsOffset){
                        offsets.insert(offsets.begin() + i, it);
                        break;
                    }
                }
            }

            const int tempRawSize = 3200;
            char tempRaw[tempRawSize];
            HBuffer temp(tempRaw, tempRawSize, tempRawSize, false, false);

            for(size_t i = 0; i < offsets.size(); i++){
                assetOffsets otherOffsets = offsets[i]->second;
                m_AssetsStream.seekg(0, otherOffsets.m_AssetsOffset);
                uint32_t assetSize;
                m_AssetsStream.read(reinterpret_cast<char*>(&assetSize), sizeof(uint32_t));
                if(!m_AssetsStream){
                    return AssetManagerError::EndOfFile;
                }
                temp.Reserve(assetSize);
                m_AssetsStream.read(temp.GetData(), assetSize);
                if(!m_AssetsStream){
                    return AssetManagerError::EndOfFile;
                }

                m_AssetsStream.seekg(m_WriteOffset, std::ios::beg);
                m_AssetsStream.write(reinterpret_cast<char*>(&assetSize), sizeof(uint32_t));
                m_AssetsStream.write(temp.GetData(), assetSize);

                m_MapStream.seekg(otherOffsets.m_MapOffset, std::ios::beg);
                m_MapStream.write(reinterpret_cast<char*>(m_WriteOffset), sizeof(uint32_t));
                m_WriteOffset+=sizeof(uint32_t) + assetSize;
            }
            m_AssetsStream.seekp(m_WriteOffset, std::ios::beg);
            uint32_t assetSize = static_cast<uint32_t>(data.GetSize());
            m_AssetsStream.write(reinterpret_cast<char*>(&assetSize), sizeof(uint32_t));
            m_AssetsStream.write(data.GetData(), assetSize);

            m_MapStream.seekg(0, assetOffsets.m_MapOffset);
            m_MapStream.write(reinterpret_cast<char*>(&m_WriteOffset), sizeof(uint32_t));
            return AssetManagerError::None;
        }
        m_AssetsStream.seekp(0, std::ios::end);
        m_MapStream.seekp(0, std::ios::end);

        size_t mapOffset = m_MapStream.tellp();
        size_t assetsOffset = m_AssetsStream.tellg();

        uint32_t dataSize = static_cast<uint32_t>(data.GetSize());
        m_AssetsStream.write(reinterpret_cast<char*>(&dataSize), sizeof(uint32_t));
        m_AssetsStream.write(data.GetData(), dataSize);
        
        /// Write asset onto map
        uint16_t assetNameSize = static_cast<uint16_t>(name.GetSize());
        m_MapStream.write(reinterpret_cast<char*>(&assetNameSize), sizeof(uint16_t));
        m_MapStream.write(name.GetData(), assetNameSize);
        m_MapStream.write(reinterpret_cast<char*>(&m_WriteOffset), sizeof(uint32_t));
        m_WriteOffset+=data.GetSize();

        assetOffsets offsets{mapOffset, assetsOffset};
        m_AssetsMap.insert(std::make_pair(std::move(name), offsets));
        return AssetManagerError::None;
    }
}