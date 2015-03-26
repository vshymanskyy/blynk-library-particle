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

    void begin(uint32_t a, uint16_t p) {
        port = p;
        addr = a;
    }

    bool connect() {
        uint8_t* a = (uint8_t*)&addr;
        BLYNK_LOG("Connecting to %d.%d.%d.%d:%d", a[3], a[2], a[1], a[0], port);
        return 1 == client.connect(addr, port);
    }

    void disconnect() { client.stop(); }

    size_t read(void* buf, size_t len) {
        char* beg = (char*)buf;
        char* end = beg + len;
        while (beg < end) {
            int c = client.read();
            if (c < 0)
                break;
            *beg++ = (char)c;
        }
        return len;
    }
    
    size_t write(const void* buf, size_t len) {
        return client.write((const uint8_t*)buf, len);
    }

    void flush() { client.stop(); }
    bool connected() { return client.connected(); }
    int available() { return client.available(); }

private:
    TCPClient   client;
    uint32_t    addr;
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
    }

    void begin( const char* auth,
                IPAddress addr,
                uint16_t port)
    {
        Base::begin(auth);
    }
private:

};

#endif
