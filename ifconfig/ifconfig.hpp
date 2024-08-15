#pragma once

#include <string>
#include "ifconfig.hpp"
#include <iostream>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>

namespace ifconfig {
    struct interface {
        std::string name;
        std::string addr_ipv4;
        std::string addr_ipv6;
    };

    inline interface get_interface() {
        struct ifaddrs *interfaces = nullptr, *ifa = nullptr;
        char ip[INET_ADDRSTRLEN];

        // Get all interfaces on machine
        if (getifaddrs(&interfaces) == -1) {
            std::cerr << "Error to open networks interfaces" << std::endl;
            return {};
        }

        // go througth all interfaces
        for (ifa = interfaces; ifa != nullptr; ifa = ifa->ifa_next) {
            
            if (!(ifa->ifa_addr)) 
                continue;

            if (ifa->ifa_addr->sa_family == AF_INET) {
                // ip family IPV4
                void* addr = &((struct sockaddr_in*)ifa->ifa_addr)->sin_addr;
                inet_ntop(AF_INET, addr, ip, INET_ADDRSTRLEN);

                if (std::string(ifa->ifa_name) != "lo") {
                    freeifaddrs(interfaces);
                    return {
                        .name = std::string(ifa->ifa_name),
                        .addr_ipv4 = std::string(ip)
                    };
                }
            }
        }

        freeifaddrs(interfaces);
        return {};
    }
}