#pragma once

#include "Metamorphic/pch.h"
#include "Metamorphic/Core/Core.h"

namespace Metamorphic{
    template <typename Vector=sfmath::Vec3>
    class Transform{
    public:
        Transform(GameObject* m_GameObject)noexcept;
        ~Transform()noexcept;

        void SetPosition(const Vector& vec)const noexcept;
        void SetOrientation(const sfmath::quat& quat)noexcept;
        void SetScale(const Vector& vec)noexcept;
        
        void Translate(const Vec3& vec)noexcept;
        void Rotate(const sfmath::quat& quat)noexcept;
        void Scale(const Vector& scale)noexcept;
    public:
        const Vector& GetPosition() const noexcept{return m_Position;}
        const sfmath::quat& GetQuaternion() const noexcept{return m_Orientation;}
        const Vector& GetScale() const noexcept{return m_Scale;}
        const sfmath::Mat4x4& GetTransformationMatrix() const noexcept{return m_TransformationMatrix;}
        const sfmath::Mat4x4& GetViewMatrix() const noexcept{return m_ViewMatrix;}
    private:
        Vector m_Position;
        Vector m_Scale;
        sfmath::quat m_Orientation;
        sfmath::Mat4x4 m_TransformationMatrix;
        sfmath::Mat4x4 m_ViewMatrix;
    };
}