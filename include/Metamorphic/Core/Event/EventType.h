#pragma once

enum class EventType{
    None,
    ExitApplication,
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