#ifndef UV_TCP_HANDLE_H
#define UV_TCP_HANDLE_H

#include "../utility/global.h"
#include <uv.h>

class UVTCPHandle
{
public:
    UVTCPHandle() noexcept;
    UVTCPHandle(uv_loop_t *loop) noexcept;
    virtual ~UVTCPHandle();

    UVTCPHandle(const UVTCPHandle &) = delete;
    UVTCPHandle(UVTCPHandle &&) = delete;
    UVTCPHandle &operator = (const UVTCPHandle &) = delete;
    UVTCPHandle &operator = (UVTCPHandle &&) = delete;

public:
    uv_stream_t *get_uv_stream() noexcept;
    uv_handle_t *get_uv_handle() noexcept;
    uv_tcp_t *get_uv_tcp() noexcept;
    uv_loop_t *get_loop() noexcept;

    bool run_loop() MAYTHROW;
    void stop_loop() noexcept;

private:
    uv_tcp_t *handle;
};

#endif // UV_TCP_HANDLE_H
