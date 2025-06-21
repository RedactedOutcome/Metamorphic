#pragma once

#include "EventType.h"

namespace Metamorphic{
    class Event{
    public:
        Event() noexcept{}

    #pragma region Macros
        /// @brief a macro that defines various event information
        #define SETUP_EVENT_DATA(type)\
            /*Defines the token type so we can use callbacks*/ \
            const static EventType s_EventType = type; \
            EventType GetEventType() const noexcept override {return s_EventType;}
        
        virtual EventType GetEventType() const noexcept {return EventType::None;}
    #pragma endregion
    };
}