#include "Metamorphic/pch.h"
#include "Core/Objects/Transform.h"

namespace Metamorphic{
    template <typename Vector>
    class Transform{
        void SetOrientation(const sfmath::quat& quat)noexcept{
            m_Orientation = quat;
            GenerateTransformationMatrix();
        }
        void Rotate(const sfmath::quat& quat)noexcept{
            m_Orientation = quat * m_Orientation;
        }
        void Transform::GenerateTransformationMatrix()noexcept{
            m_TransformationMatrix.SetValue(0, 3, m_Position.m_X);


        }
    };
}