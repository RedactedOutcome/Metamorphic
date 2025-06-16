#pragma once

#include "Metamorphic/Core/Event/Event.h"

namespace Metamorphic{
    class ApplicationExitEvent : Event{
    public:
        ApplicationExitEvent()noexcept{}
        ~ApplicationExitEvent()noexcept{}

        SETUP_EVENT_DATA(EventType::ApplicationExit)
    };
}