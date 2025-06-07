#pragma once

#include "Core/Logger.h"

namespace Metamorphic{
    enum class ResourceManagerError{
        None = 0,
        FailedToLoadFilePath,
        NoResources,
        FailedToWriteToMap,
        FailedToWriteToResources,
        UnsupportedResourceMapVersion,
        CorruptedResourceMapIndex,
        UnsupportedResourceVersion,
        InvalidResourceFormat,
        CorruptedResourceMap,
        CorruptedResources,
        ResourceNotFound,
        FailedAllocation,
        AmbiguousResource, /// Multiple resources with the same name
        Unsupported,
        EndOfFile,
        CorruptedResource
    };

    /// @brief A resource manager to load resources from or to a map/resource glob.
    class ResourceManager {
    public:
        struct ResourceOffsets {
            /// @brief the offset into the map where we write the resource location
            uint32_t m_MapOffset = 0;
            /// @brief the offset defined in the map that defines where in the resources buffer the file data is located
            uint32_t m_ResourcesOffset = 0;
        };
    public:
        ResourceManager() noexcept;
        ~ResourceManager()noexcept;

        /// @brief Allocates a resource of Type T.
        /// @tparam T. A type that contains a ResourceManagerError LoadResource(const HBuffer& resourceBuffer)noexcept
        /// @param resourceName the name to store the resource as.
        /// @param error the error status
        /// @return a pointer to a newly allocated Type T that does not have any memory management
        template <typename T>
        T* CreateResource(const HBuffer& resourceName, ResourceManagerError* error)noexcept{
            T* resource = new T();
            ResourceManagerError error = LoadResource<T>(&resource, resourceName);
            if(error == ResourceManagerError::None)return resource;
            delete resource;
            return error;
        }
        
        template <typename T>
        ResourceManagerError LoadResource(T* output, const HBuffer& resourceName)noexcept{
            if(!m_IsMapLoaded){
                ResourceManagerError mapError = LoadMap();
                if(mapError != ResourceManagerError::None){
                    return mapError;
                }
            }
            if(m_ResourceMap.find(resourceName) == m_ResourceMap.end()){
                return ResourceManagerError::ResourceNotFound;
            }
            ResourceOffsets offsets = m_ResourceMap[resourceName];
            uint32_t resourcesOffset = offsets.m_ResourcesOffset;
            
            if(m_LoadWholeBuffer){
                if(!m_LoadedResources){
                    ResourceManagerError resourceError = LoadResourcesBuffer();
                    if(resourceError != ResourceManagerError::None){
                        return resourceError;
                    }
                }

                uint32_t resourceSize;
                if(!m_ResourcesBuffer.ExtractUInt32(resourcesOffset, &resourceSize)){
                    return ResourceManagerError::CorruptedResources;
                }
                ResourceManagerError loadError = output->LoadResource(m_ResourcesBuffer.SubBuffer(resourcesOffset + sizeof(uint32_t), resourceSize));
                if(loadError != ResourceManagerError::None)
                    return loadError;
                
                return ResourceManagerError::None;
            }

            if(m_ResourcesStream.is_open() == false){
                std::filesystem::path resourcesPath(m_ResourcesPath.GetCStr());
                resourcesPath.replace_extension(".cpr");
                m_ResourcesStream = std::fstream(resourcesPath, std::ios::binary | std::ios::in | std::ios::out);
            }
            if(!m_ResourcesStream){
                return ResourceManagerError::FailedToLoadFilePath;
            }

            m_ResourcesStream.seekg(0, std::ios::end);
            size_t fileSize = m_ResourcesStream.tellg();
            if(fileSize <= resourcesOffset + sizeof(uint32_t) - 1){
                return ResourceManagerError::CorruptedResources;
            }
            m_ResourcesStream.seekg(resourcesOffset, std::ios::beg);
            uint32_t resourceSize;

            /// @brief Windows uses little endian and HBuffer Configuration is little endian
            m_ResourcesStream.read(reinterpret_cast<char*>(&resourceSize), sizeof(uint32_t));
            if(!m_ResourcesStream){
                /// Failed to read all bytes
                return ResourceManagerError::EndOfFile;
            }
            m_ResourcesStream.seekg(resourcesOffset + sizeof(uint32_t));

            HBuffer resourceData(new char[resourceSize], resourceSize, resourceSize, true, true);
            m_ResourcesStream.read(resourceData.GetData(), resourceSize);
            if(!m_ResourcesStream){
                return ResourceManagerError::EndOfFile;
            }

            ResourceManagerError loadError = output->LoadResource(resourceData);
            if(loadError != ResourceManagerError::None)
                return loadError;
            return ResourceManagerError::None;
        }
    public:
        /// @brief creates an ofstream and prepares for saving files. If a map/resources already exists then we will append or rewrite
        /// @brief To save resources simple call StartSaving() then call Resource::SaveResource(resouceManager)
        /// @brief the output error message if ResourceManagerError != ResourceManagerError::None. May be ignored if else
        ResourceManagerError StartSaving(HBuffer& errorMessage)noexcept;
        void StopSaving()noexcept;

        ResourceManagerError AppendResource(const HBuffer& name, const HBuffer& data)noexcept;
    public:
        void SetMapPath(const HBuffer& mapPath)noexcept;
        void SetMapPath(HBuffer&& mapPath)noexcept;
    public:
        /// @brief loads the resource file map into memory. If Map is already loaded then we reload
        ResourceManagerError LoadMap()noexcept;
        /// @brief loads the whole resources buffer into memory whether or not m_LoadWholeBuffer
        ResourceManagerError LoadResourcesBuffer()noexcept;
    public:
        /// @brief returns the path to the resource map.
        const HBuffer& GetMapPath() const noexcept{return m_MapPath;}
        const HBuffer& GetResourcesPath() const noexcept{return m_ResourcesPath;}
        const HBuffer& GetResourcesBuffer() const noexcept{return m_ResourcesBuffer;}
        //EventDispatcher& GetEventDispatcher() const noexcept{return (EventDispatcher&)*m_EventDispatcher;}
        //std::ofstream& GetMapWriteStream() const noexcept{return (std::ofstream&)m_MapWriteStream;}
        //std::ofstream& GetResourcesWriteStream() const noexcept{return (std::ofstream&)m_ResourcesWriteStream;}
    protected:
        bool m_IsMapLoaded = false;
        /// @brief decides to load all resources into the m_Data buffer. this way less io allocations but more memory usage
        bool m_LoadWholeBuffer = false;
        bool m_LoadedResources = false;
        HBuffer m_MapPath;
        std::unordered_map<HBuffer, ResourceOffsets> m_ResourceMap;
        size_t m_WriteOffset = 0;
        /// @brief the file path that contains the array of data for resources. Located in the resource map
        HBuffer m_ResourcesPath;
        HBuffer m_ResourcesBuffer;
        //EventDispatcher* m_EventDispatcher = nullptr;
        std::fstream m_MapStream;
        std::fstream m_ResourcesStream;
    };
}