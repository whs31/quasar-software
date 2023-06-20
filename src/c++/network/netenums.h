#pragma once

namespace Network
{
    enum class PingStatus
    {
        Success,
        DelayedSuccess,
        Timeout,
        Idle
    };
} // Network
