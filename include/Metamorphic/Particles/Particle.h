#pragma once

#include "Metamorphic/pch.h"
#include "Metamorphic/Core/Core.h"

namespace Metamorphic{
    /// @brief A base particle struct
    struct Particle{
        METAMORPHIC_DEFAULT_VECTOR_TYPE m_Position;
        sfmath::Quat m_Orientation;
        METAMORPHIC_DEFAULT_VECTOR_TYPE m_Scale;
        float m_Lifetime = 0;
        float m_Age = 0;
        float m_Transparency = 0.0f;
        sfmath::Vec3<float> m_Color;
    };

    struct TexturedParticle : public Particle{
        /// @brief the image id to point to. -1 specifies unset/invalid image
        int32_t m_ImageId = -1;
        float m_BackgroundTransparency = 0.0f;
    };

    /// @brief A particle that takes an image as a Texture Atlas.
    /// @member m_TileIndex what frame of animation we are on. So far only supports 256 different frames.
    struct AnimatedParticle : public TexturedParticle{
        float m_TilesPerWidth=1.0f;
        float m_TilesPerHeight=1.0f;
        float m_CurrentTileX = 0.0f;
        float m_CurrentTileY = 0.0f;
        /// @brief How many seconds to wait before updating to the next tile
        float m_UpdateRate = -1.0f;
        float m_LastUpdate = 0.0f;
        uint8_t m_TileIndex = 0;
    };
}