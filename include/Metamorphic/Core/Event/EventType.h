#pragma once

namespace Metamorphic{
    enum class EventType{
        None,
        ApplicationExit,
        OnBeforeApplicationExit,
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