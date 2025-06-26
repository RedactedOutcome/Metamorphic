#pragma once

#include "Metamorphic/Core/Event/Event.h"

namespace Metamorphic{
    class OnBeforeApplicationExitEvent : public Event{
    public:
        OnBeforeApplicationExitEvent()noexcept{}
        ~OnBeforeApplicationExitEvent()noexcept{}

        SETUP_EVENT_DATA(EventType::OnBeforeApplicationExit)
    };
}