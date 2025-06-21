#pragma once

#include "Metamorphic/Core/Event/Event.h"

namespace Metamorphic{
    class ApplicationExitEvent : public Event{
    public:
        ApplicationExitEvent()noexcept{}
        ~ApplicationExitEvent()noexcept{}

        SETUP_EVENT_DATA(EventType::ApplicationExit)
    };
}