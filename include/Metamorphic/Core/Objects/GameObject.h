#pragma once

#include "Component.h"
namespace Metamorphic{
    class GameObject{
    public:
        GameObject()noexcept;
        ~GameObject()noexcept;

        void Awake()noexcept;
        void Start()noexcept;
        void Update()noexcept;
        void LateUpdate()noexcept;
        void Draw()noexcept;
        void LateDraw()noexcept;
    public:
        template<typename T, typename... Args>
        std::unique_ptr<T>& CreateComponent(Args&& args)noexcept{
            m_Components.emplace_back(std::make_unique<T>(std::forward<Args>(args)));
            return m_Components[m_Components.size() - 1];
        }
    private:
        bool m_Enabled = true;
        std::vector<std::unique_ptr<Component>> m_Components;
    };
}