#pragma once

#include "Particle.h"

namespace Metamorphic{
    /// @brief a base particle system that has basic particles, textured Particles, and AnimatedParticles.
    class METAMORPHIC_API ParticleSystem{
    public:
        ParticleSystem()noexcept;
        ~ParticleSystem()noexcept;
    };
}