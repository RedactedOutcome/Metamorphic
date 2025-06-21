#pragma once

namespace Metamorphic{
    enum class EventType{
        None,
        ApplicationExit,
        WindowMovedEvent,
        WindowResizedEvent,
        MouseMovedEvent,
        MouseButtonDown, 
        MouseButtonUp,
        
        LoadedResourceManager,

        ConnectedToServer,
        FailedToServer,
        DisconnectedFromServer,
        PacketReceivedEvent
    };
}