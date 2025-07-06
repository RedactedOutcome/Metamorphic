#pragma once

#include "Core/Logger.h"

namespace Metamorphic{
    enum class ResourceManagerError{
        None = 0,
        FailedToLoadFilePath,
        NoAssets,
        FailedToWriteToMap,
        FailedToWriteToAssets,
        UnsupportedResourceMapVersion,
        CorruptedResourceMapIndex,
        UnsupportedResourceVersion,
        InvalidResourceFormat,
        CorruptedResourceMap,
        CorruptedAssets,
        ResourceNotFound,
        FailedAllocation,
        AmbiguousResource, /// Multiple assets with the same name
        Unsupported,
        EndOfFile,
        CorruptedResource
    };

    /// @brief A asset manager to load assets from or to a map/asset glob.
    class ResourceManager {
    public:
        struct ResourceOffsets {
            /// @brief the offset into the map where we write the asset location
            uint32_t m_MapOffset = 0;
            /// @brief the offset defined in the map that defines where in the assets buffer the file data is located
            uint32_t m_AssetsOffset = 0;
        };
    public:
        ResourceManager() noexcept;
        ~ResourceManager()noexcept;

        /// @brief Allocates a asset of Type T.
        /// @tparam T. A type that contains a ResourceManagerError LoadResource(const HBuffer& assetBuffer)noexcept
        /// @param assetName the name to store the asset as.
        /// @param error the error status
        /// @return a pointer to a newly allocated Type T that does not have any memory management
        template <typename T>
        T* CreateResource(const HBuffer& assetName, ResourceManagerError* error)noexcept{
            T* asset = new T();
            ResourceManagerError error = LoadResource<T>(&asset, assetName);
            if(error == ResourceManagerError::None)return asset;
            delete asset;
            return error;
        }
        
        template <typename T>
        ResourceManagerError LoadResource(T* output, const HBuffer& assetName)noexcept{
            if(!m_IsMapLoaded){
                ResourceManagerError mapError = LoadMap();
                if(mapError != ResourceManagerError::None){
                    return mapError;
                }
            }
            if(m_ResourceMap.find(assetName) == m_ResourceMap.end()){
                return ResourceManagerError::ResourceNotFound;
            }
            ResourceOffsets offsets = m_ResourceMap[assetName];
            uint32_t assetsOffset = offsets.m_AssetsOffset;
            
            if(m_LoadWholeBuffer){
                if(!m_LoadedAssets){
                    ResourceManagerError assetError = LoadAssetsBuffer();
                    if(assetError != ResourceManagerError::None){
                        return assetError;
                    }
                }

                uint32_t assetSize;
                if(!m_AssetsBuffer.ExtractUInt32(assetsOffset, &assetSize)){
                    return ResourceManagerError::CorruptedAssets;
                }
                ResourceManagerError loadError = output->LoadResource(m_AssetsBuffer.SubBuffer(assetsOffset + sizeof(uint32_t), assetSize));
                if(loadError != ResourceManagerError::None)
                    return loadError;
                
                return ResourceManagerError::None;
            }

            if(m_AssetsStream.is_open() == false){
                std::filesystem::path assetsPath(m_AssetsPath.GetCStr());
                assetsPath.replace_extension(".cpr");
                m_AssetsStream = std::fstream(assetsPath, std::ios::binary | std::ios::in | std::ios::out);
            }
            if(!m_AssetsStream){
                return ResourceManagerError::FailedToLoadFilePath;
            }

            m_AssetsStream.seekg(0, std::ios::end);
            size_t fileSize = m_AssetsStream.tellg();
            if(fileSize <= assetsOffset + sizeof(uint32_t) - 1){
                return ResourceManagerError::CorruptedAssets;
            }
            m_AssetsStream.seekg(assetsOffset, std::ios::beg);
            uint32_t assetSize;

            /// @brief Windows uses little endian and HBuffer Configuration is little endian
            m_AssetsStream.read(reinterpret_cast<char*>(&assetSize), sizeof(uint32_t));
            if(!m_AssetsStream){
                /// Failed to read all bytes
                return ResourceManagerError::EndOfFile;
            }
            m_AssetsStream.seekg(assetsOffset + sizeof(uint32_t));

            HBuffer assetData(new char[assetSize], assetSize, assetSize, true, true);
            m_AssetsStream.read(assetData.GetData(), assetSize);
            if(!m_AssetsStream){
                return ResourceManagerError::EndOfFile;
            }

            ResourceManagerError loadError = output->LoadResource(assetData);
            if(loadError != ResourceManagerError::None)
                return loadError;
            return ResourceManagerError::None;
        }
    public:
        /// @brief creates an ofstream and prepares for saving files. If a map/assets already exists then we will append or rewrite
        /// @brief To save assets simple call StartSaving() then call Resource::SaveResource(resouceManager)
        /// @brief the output error message if ResourceManagerError != ResourceManagerError::None. May be ignored if else
        ResourceManagerError StartSaving(HBuffer& errorMessage)noexcept;
        void StopSaving()noexcept;

        ResourceManagerError AppendResource(const HBuffer& name, const HBuffer& data)noexcept;
    public:
        void SetMapPath(const HBuffer& mapPath)noexcept;
        void SetMapPath(HBuffer&& mapPath)noexcept;
    public:
        /// @brief loads the asset file map into memory. If Map is already loaded then we reload
        ResourceManagerError LoadMap()noexcept;
        /// @brief loads the whole assets buffer into memory whether or not m_LoadWholeBuffer
        ResourceManagerError LoadAssetsBuffer()noexcept;
    public:
        /// @brief returns the path to the asset map.
        const HBuffer& GetMapPath() const noexcept{return m_MapPath;}
        const HBuffer& GetAssetsPath() const noexcept{return m_AssetsPath;}
        const HBuffer& GetAssetsBuffer() const noexcept{return m_AssetsBuffer;}
        //EventDispatcher& GetEventDispatcher() const noexcept{return (EventDispatcher&)*m_EventDispatcher;}
        //std::ofstream& GetMapWriteStream() const noexcept{return (std::ofstream&)m_MapWriteStream;}
        //std::ofstream& GetAssetsWriteStream() const noexcept{return (std::ofstream&)m_AssetsWriteStream;}
    protected:
        bool m_IsMapLoaded = false;
        /// @brief decides to load all assets into the m_Data buffer. this way less io allocations but more memory usage
        bool m_LoadWholeBuffer = false;
        bool m_LoadedAssets = false;
        HBuffer m_MapPath;
        std::unordered_map<HBuffer, ResourceOffsets> m_ResourceMap;
        size_t m_WriteOffset = 0;
        /// @brief the file path that contains the array of data for assets. Located in the asset map
        HBuffer m_AssetsPath;
        HBuffer m_AssetsBuffer;
        //EventDispatcher* m_EventDispatcher = nullptr;
        std::fstream m_MapStream;
        std::fstream m_AssetsStream;
    };
}