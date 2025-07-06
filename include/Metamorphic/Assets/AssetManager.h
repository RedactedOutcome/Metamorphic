#pragma once

#include "Metamorphic/pch.h"

namespace Metamorphic{
    enum class AssetManagerError{
        None = 0,
        FailedToLoadFilePath,
        NoAssets,
        FailedToWriteToMap,
        FailedToWriteToAssets,
        UnsupportedAssetMapVersion,
        CorruptedAssetMapIndex,
        UnsupportedAssetVersion,
        InvalidAssetFormat,
        CorruptedAssetMap,
        CorruptedAssets,
        AssetNotFound,
        FailedAllocation,
        AmbiguousAsset, /// Multiple assets with the same name
        Unsupported,
        EndOfFile,
        CorruptedAsset
    };

    /// @brief A asset manager to load assets from or to a map/asset glob.
    class AssetManager {
    public:
        struct AssetOffsets {
            /// @brief the offset into the map where we write the asset location
            uint32_t m_MapOffset = 0;
            /// @brief the offset defined in the map that defines where in the assets buffer the file data is located
            uint32_t m_AssetsOffset = 0;
        };
    public:
        AssetManager() noexcept;
        ~AssetManager()noexcept;

        /// @brief Allocates a asset of Type T.
        /// @tparam T. A type that contains a AssetManagerError LoadAsset(const HBuffer& assetBuffer)noexcept
        /// @param assetName the name to store the asset as.
        /// @param error the error status
        /// @return a pointer to a newly allocated Type T that does not have any memory management
        template <typename T>
        T* CreateAsset(const HBuffer& assetName, AssetManagerError* error)noexcept{
            T* asset = new T();
            AssetManagerError error = LoadAsset<T>(&asset, assetName);
            if(error == AssetManagerError::None)return asset;
            delete asset;
            return error;
        }
        
        template <typename T>
        AssetManagerError LoadAsset(T* output, const HBuffer& assetName)noexcept{
            if(!m_IsMapLoaded){
                AssetManagerError mapError = LoadMap();
                if(mapError != AssetManagerError::None){
                    return mapError;
                }
            }
            if(m_AssetsMap.find(assetName) == m_AssetsMap.end()){
                return AssetManagerError::AssetNotFound;
            }
            AssetOffsets offsets = m_AssetsMap[assetName];
            uint32_t assetsOffset = offsets.m_AssetsOffset;
            
            if(m_LoadWholeBuffer){
                if(!m_LoadedAssets){
                    AssetManagerError assetError = LoadAssetsBuffer();
                    if(assetError != AssetManagerError::None){
                        return assetError;
                    }
                }

                uint32_t assetSize;
                if(!m_AssetsBuffer.ExtractUInt32(assetsOffset, &assetSize)){
                    return AssetManagerError::CorruptedAssets;
                }
                AssetManagerError loadError = output->LoadAsset(m_AssetsBuffer.SubBuffer(assetsOffset + sizeof(uint32_t), assetSize));
                if(loadError != AssetManagerError::None)
                    return loadError;
                
                return AssetManagerError::None;
            }

            if(m_AssetsStream.is_open() == false){
                std::filesystem::path assetsPath(m_AssetsPath.GetCStr());
                assetsPath.replace_extension(".cpr");
                m_AssetsStream = std::fstream(assetsPath, std::ios::binary | std::ios::in | std::ios::out);
            }
            if(!m_AssetsStream){
                return AssetManagerError::FailedToLoadFilePath;
            }

            m_AssetsStream.seekg(0, std::ios::end);
            size_t fileSize = m_AssetsStream.tellg();
            if(fileSize <= assetsOffset + sizeof(uint32_t) - 1){
                return AssetManagerError::CorruptedAssets;
            }
            m_AssetsStream.seekg(assetsOffset, std::ios::beg);
            uint32_t assetSize;

            /// @brief Windows uses little endian and HBuffer Configuration is little endian
            m_AssetsStream.read(reinterpret_cast<char*>(&assetSize), sizeof(uint32_t));
            if(!m_AssetsStream){
                /// Failed to read all bytes
                return AssetManagerError::EndOfFile;
            }
            m_AssetsStream.seekg(assetsOffset + sizeof(uint32_t));

            HBuffer assetData(new char[assetSize], assetSize, assetSize, true, true);
            m_AssetsStream.read(assetData.GetData(), assetSize);
            if(!m_AssetsStream){
                return AssetManagerError::EndOfFile;
            }

            AssetManagerError loadError = output->LoadAsset(assetData);
            if(loadError != AssetManagerError::None)
                return loadError;
            return AssetManagerError::None;
        }
    public:
        /// @brief creates an ofstream and prepares for saving files. If a map/assets already exists then we will append or rewrite
        /// @brief To save assets simple call StartSaving() then call Asset::SaveAsset(resouceManager)
        /// @brief the output error message if AssetManagerError != AssetManagerError::None. May be ignored if else
        AssetManagerError StartSaving(HBuffer& errorMessage)noexcept;
        void StopSaving()noexcept;

        AssetManagerError AppendAsset(const HBuffer& name, const HBuffer& data)noexcept;
    public:
        void SetMapPath(const HBuffer& mapPath)noexcept;
        void SetMapPath(HBuffer&& mapPath)noexcept;
    public:
        /// @brief loads the asset file map into memory. If Map is already loaded then we reload
        AssetManagerError LoadMap()noexcept;
        /// @brief loads the whole assets buffer into memory whether or not m_LoadWholeBuffer
        AssetManagerError LoadAssetsBuffer()noexcept;
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
        std::unordered_map<HBuffer, AssetOffsets> m_AssetsMap;
        size_t m_WriteOffset = 0;
        /// @brief the file path that contains the array of data for assets. Located in the asset map
        HBuffer m_AssetsPath;
        HBuffer m_AssetsBuffer;
        //EventDispatcher* m_EventDispatcher = nullptr;
        std::fstream m_MapStream;
        std::fstream m_AssetsStream;
    };
}