/**
 * @file       BlynkSparkCore.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Mar 2015
 * @brief
 *
 */

#ifndef BlynkSparkCore_h
#define BlynkSparkCore_h

#define BLYNK_INFO_CONNECTION "CC3000"

#include "BlynkApiSparkCore.h"
#include "BlynkProtocol.h"

class BlynkTransportSparkCore
{
public:
    BlynkTransportSparkCore()
        : addr(0), port(0)
    {}

    void begin(IPAddress a, uint16_t p) {
        domain = NULL;
        port = p;
        addr = a;
    }

    void begin(const char* d, uint16_t p) {
        domain = d;
        port = p;
    }

    bool connect() {
        if (domain) {
            BLYNK_LOG("Connecting to %s:%d", domain, port);
            return (1 == client.connect(domain, port));
        } else if (addr) {
            BLYNK_LOG("Connecting to %d.%d.%d.%d:%d", addr[0], addr[1], addr[2], addr[3], port);
            return (1 == client.connect(addr, port));
        }
        return 0;
    }

    void disconnect() { client.stop(); }

    size_t read(void* buf, size_t len) {
        return client.readBytes((char*)buf, len);
    }
    
    size_t write(const void* buf, size_t len) {
        return client.write((const uint8_t*)buf, len);
    }

    void flush() { client.flush(); }
    bool connected() { return client.connected(); }
    int available() { return client.available(); }

private:
    TCPClient   client;
    IPAddress   addr;
    const char* domain;
    uint16_t    port;
};

class BlynkSparkCore
    : public BlynkProtocol<BlynkTransportSparkCore>
{
    typedef BlynkProtocol<BlynkTransportSparkCore> Base;
public:
    BlynkSparkCore(BlynkTransportSparkCore& transp)
        : Base(transp)
    {}

    void begin( const char* auth,
                const char* domain = BLYNK_DEFAULT_DOMAIN,
                uint16_t port      = BLYNK_DEFAULT_PORT)
    {
        Base::begin(auth);
        this->conn.begin(domain, port);
    }

    void begin( const char* auth,
                IPAddress addr,
                uint16_t port)
    {
        Base::begin(auth);
        this->conn.begin(addr, port);
    }
private:

};

#endif
