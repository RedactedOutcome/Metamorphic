#pragma once

#include "Metamorphic/pch.h"
#include "Metamorphic/Core/Core.h"

namespace Metamorphic{
    template <typename Vector=sfmath::Vec3>
    class Transform{
    public:
        Transform(GameObject* m_GameObject)noexcept{}
        ~Transform()noexcept{}

        void SetPosition(const Vector& vec)noexcept{
            m_Position = vec;
        }
        void SetOrientation(const sfmath::quat& quat)noexcept;
        void SetScale(const Vector& vec)noexcept;
        
        void Translate(const Vector& vec)noexcept;
        void Rotate(const sfmath::quat& quat)noexcept;
        void Scale(const Vector& scale)noexcept;

        void GenerateTransformationMatrix()noexcept;
    public:
        /// @brief Strict functions that do only what they say
        void StrictSetPosition(const Vector& vec)noexcept{m_Position = vec;}
        void StrictSetOrientation(const sfmath::quat& quat)noexcept{m_Orientation = quat;}
        void StrictSetScale(const Vector& vec)noexcept{m_Scale = vec;}

        void StrictTranslate(const Vector& vec)noexcept{m_Position += vec;}
        void StrictRotate(const sfmath::quat& rotate){m_Orientation = rotate * m_Orientation;}
        void StrictScale(const Vector& vec)noexcept{m_Scale *= vec;}
    public:
        const Vector& GetPosition() const noexcept{return m_Position;}
        const sfmath::quat& GetQuaternion() const noexcept{return m_Orientation;}
        const Vector& GetScale() const noexcept{return m_Scale;}
        const sfmath::SMat4x4& GetTransformationMatrix() const noexcept{return m_TransformationMatrix;}
    private:
        Vector m_Position;
        Vector m_Scale;
        sfmath::quat m_Orientation;
        sfmath::SMat4x4 m_TransformationMatrix;
    };
}