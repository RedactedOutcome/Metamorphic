#pragma once

#include "Metamorphic/Rendering/IWindow.h"
#include "Metamorphic/SceneManagement/SceneManager.h"

namespace Metamorphic{
    enum ApplicationError{
        None=0,
        FailedToCreateWindow,
        FailedToInitializeRenderer
    };
    class Application{
    public:
        Application()noexcept;
        ~Application()noexcept;
        
        ApplicationError Init()noexcept;
        void Update()noexcept;
        void LateUpdate()noexcept;
        void Draw()noexcept;
        void LateDraw()noexcept;
        void Run()noexcept;
        void Shutdown()noexcept;
    public:
        /// @brief After program is initialized in the Run Method
        virtual void AfterInitialized()noexcept{}
        /// @brief Before shutting down the program in the Run Method, only called program was initially initialized correctly
        virtual void BeforeShutdown()noexcept{}
    protected:
        std::unique_ptr<IWindow> m_Window;
        SceneManager m_SceneManager;
    private:
    };

    extern Application* CreateApplication()noexcept;
}