#include "Metamorphic/pch.h"
#include "Core/Objects/Transform.h"

namespace Metamorphic{

    template <typename Vector>
    void SetPosition(const Vector& vec)noexcept{
        m_Position = vec;
        GenerateTransformationMatrix();
    }
    template <typename Vector>
    void SetScale(const Vector& vec)noexcept{
        m_Scale = vec;
        GenerateTransformationMatrix();
    }

    template <template<typename> class Vector=sfmath::Vec3, typename T=float>
    void Transform<Vector<T>>::Translate(const Vector<T>& vec)noexcept{
        m_Position += vec;
        GenerateTransformationMatrix();
    }

    template <template<typename> class Vector=sfmath::Vec3, typename T=float>
    void Transform<Vector>::Scale(const Vector& scale)noexcept{
        m_Scale *=scale;
        GenerateTransformationMatrix();
    }

    template <typename Vector>
    void Transform<Vector>::SetOrientation(const sfmath::Quat& quat)noexcept{
        m_Orientation = quat;
        GenerateTransformationMatrix();
    }

    template <typename Vector>
    void Transform<Vector>::Rotate(const sfmath::Quat& quat)noexcept{
        m_Orientation = quat * m_Orientation;
        GenerateTransformationMatrix();
    }

    template <>
    void Transform<sfmath::Vec2>::GenerateTransformationMatrix()noexcept{
        m_TransformationMatrix.SetIdentity();
        m_TransformationMatrix.SetValue(0, 3, m_Position.m_X);
        m_TransformationMatrix.SetValue(1, 3, m_Position.m_Y);

        m_TransformationMatrix *= m_Orientation.ToSMat4x4Matrix();

        sfmath::SMat4x4 scalingMatrix;
        scalingMatrix.SetIdentity();
        scalingMatrix.SetValue(0, 0, m_Scale.m_X);
        scalingMatrix.SetValue(1, 1, m_Scale.m_Y);

        m_TransformationMatrix *= scalingMatrix;
    }

    template <>
    void Transform<sfmath::Vec3>::GenerateTransformationMatrix()noexcept{
        m_TransformationMatrix.SetIdentity();
        m_TransformationMatrix.SetValue(0, 3, m_Position.m_X);
        m_TransformationMatrix.SetValue(1, 3, m_Position.m_Y);
        m_TransformationMatrix.SetValue(2, 3, m_Position.m_Z);

        m_TransformationMatrix *= m_Orientation.ToSMat4x4Matrix();

        sfmath::SMat4x4 scalingMatrix;
        scalingMatrix.SetIdentity();
        scalingMatrix.SetValue(0, 0, m_Scale.m_X);
        scalingMatrix.SetValue(1, 1, m_Scale.m_Y);
        scalingMatrix.SetValue(2, 2, m_Scale.m_Z);

        m_TransformationMatrix *= scalingMatrix;
    }

    template class Transform<sfmath::Vec2>;
    template class Transform<sfmath::Vec3>;
}