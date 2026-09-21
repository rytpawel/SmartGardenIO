#pragma once

#include <IPAddress.h>

namespace SmartGardenIO::Services
{
    class WifiService
    {
    public:
        bool connect();

        bool isConnected() const;

        IPAddress getLocalIp() const;
    };
}