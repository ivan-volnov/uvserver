#ifndef UV_NETWORK_H
#define UV_NETWORK_H

#include "uv_tcp_handle.h"

class UVAbstractClient;

class UVAbstractServer : public UVTCPHandle
{
public:
    UVAbstractServer(const char *ip, int port) MAYTHROW;

protected:
    virtual UVAbstractClient *create_client() MAYTHROW = 0;
};

class UVAbstractClient : public UVTCPHandle
{
    friend class UVAbstractServer;
public:
    UVAbstractClient(uv_loop_t *loop) noexcept;

public:
    void close() MAYTHROW;
    void write(const uv_buf_t &buf, size_t size) noexcept; // it takes control of buf and stores it after the use
    void write(char *data, size_t size) noexcept;
    static uv_buf_t get_buffer(size_t size = 65536) noexcept;

protected:
    virtual void on_connect() MAYTHROW = 0;
    virtual void on_read(char *data, size_t size) MAYTHROW = 0;
    virtual void on_disconnect() MAYTHROW = 0;

private:
    void start_reading() MAYTHROW;
};

#endif // UV_NETWORK_H
