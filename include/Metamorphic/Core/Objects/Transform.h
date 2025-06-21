#pragma once

#include "Metamorphic/pch.h"
#include "Metamorphic/Core/Core.h"

namespace Metamorphic{
    /// @brief A Transform class based of RedactedOutcomes sfmath library.
    /// @tparam Vector Supported Vector types are sfmath::Vec3, sfmath::Vec2
    template <template<typename> class Vector=sfmath::Vec3, typename T=float>
    class Transform{
    public:
        static_assert(
            std::is_same<Vector<T>, sfmath::Vec3<T>>::value || std::is_same<Vector<T>, sfmath::Vec2<T>>::value,
            "Transform Vector Must be either sfmath::Vec3 or sfmath::Vec2"
        );

        Transform()noexcept{}
        ~Transform()noexcept{}

        void Update()noexcept{
            if(!m_UpdateTransform)return;
            GenerateTransformationMatrix();
            m_UpdateTransform = false;
        }

        void SetPosition(const Vector<T>& vec)noexcept{
            m_Position = vec;
            m_UpdateTransform = true;
        }
        void SetOrientation(const sfmath::Quat& quat)noexcept{
            m_Orientation = quat;
            m_UpdateTransform = true;
        }
        void SetScale(const Vector<T>& vec)noexcept{
            m_Scale = vec;
            m_UpdateTransform = true;
        }
        
        void Translate(const Vector<T>& vec)noexcept{
            m_Position += vec;
            m_UpdateTransform = true;
        }
        void Rotate(const sfmath::Quat& quat)noexcept{
            m_Orientation = quat * m_Orientation;
            m_UpdateTransform = true;
        }
        void Scale(const Vector<T>& scale)noexcept{
            Scale = scale;
            m_UpdateTransform = true;
        }

        void GenerateTransformationMatrix()noexcept{
            m_TransformationMatrix.SetIdentity();
            m_TransformationMatrix.SetValue(0, 3, m_Position.m_X);
            m_TransformationMatrix.SetValue(1, 3, m_Position.m_Y);

            if constexpr (std::is_same<Vector<T>, sfmath::Vec3<T>>::value)
                m_TransformationMatrix.SetValue(2, 3, m_Position.m_Z);
            
            m_TransformationMatrix *= m_Orientation.ToSMat4x4Matrix();

            sfmath::SMat4x4 scalingMatrix;
            scalingMatrix.SetIdentity();
            scalingMatrix.SetValue(0, 0, m_Scale.m_X);
            scalingMatrix.SetValue(1, 1, m_Scale.m_Y);
            if constexpr (std::is_same<Vector<T>, sfmath::Vec3<T>>::value)scalingMatrix.SetValue(2, 2, m_Scale.m_Z);

            m_TransformationMatrix *= scalingMatrix;
        }
    public:
        /// @brief Strict functions that do only what they say. This way you may line up multiple things then generate matrices and ect
        void StrictSetPosition(const Vector<T>& vec)noexcept{m_Position = vec;}
        void StrictSetOrientation(const sfmath::Quat& quat)noexcept{m_Orientation = quat;}
        void StrictSetScale(const Vector<T>& vec)noexcept{m_Scale = vec;}

        void StrictTranslate(const Vector<T>& vec)noexcept{m_Position += vec;}
        void StrictRotate(const sfmath::Quat& rotate){m_Orientation = rotate * m_Orientation;}
        void StrictScale(const Vector<T>& vec)noexcept{m_Scale *= vec;}
    public:
        const Vector<T>& GetPosition() const noexcept{return m_Position;}
        const sfmath::Quat& GetQuaternion() const noexcept{return m_Orientation;}
        const Vector<T>& GetScale() const noexcept{return m_Scale;}
        const sfmath::SMat4x4& GetTransformationMatrix() const noexcept{return m_TransformationMatrix;}
    private:
        Vector<T> m_Position;
        Vector<T> m_Scale;
        sfmath::Quat m_Orientation;
        sfmath::SMat4x4 m_TransformationMatrix;
        bool m_UpdateTransform = true;
    };
}