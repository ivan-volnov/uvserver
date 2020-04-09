#include "uv_tcp_handle.h"

UVTCPHandle::UVTCPHandle() noexcept :
    UVTCPHandle(uv_default_loop())
{
    auto sigint = new uv_signal_t;
    uv_signal_init(handle->loop, sigint);
    uv_signal_start(sigint, [](uv_signal_t *handle, int signum) {
        uv_walk(handle->loop, [](uv_handle_t *handle, void *arg) {
            uv_close(handle, [](uv_handle_t *handle) {
                delete handle;
            });
        }, nullptr);
    }, SIGINT);
}

UVTCPHandle::UVTCPHandle(uv_loop_t *loop) noexcept
{
    handle = new uv_tcp_t;
    uv_tcp_init(loop, handle);
    handle->data = this;
}

UVTCPHandle::~UVTCPHandle()
{
    auto handle = reinterpret_cast<uv_handle_t *>(this->handle);
    if (not uv_is_closing(handle)) {
        uv_close(handle, [](uv_handle_t *handle) {
            delete handle;
        });
    }
}

uv_stream_t *UVTCPHandle::get_uv_stream() noexcept
{
    return reinterpret_cast<uv_stream_t *>(handle);
}

uv_handle_t *UVTCPHandle::get_uv_handle() noexcept
{
    return reinterpret_cast<uv_handle_t *>(handle);
}

uv_tcp_t *UVTCPHandle::get_uv_tcp() noexcept
{
    return handle;
}

uv_loop_t *UVTCPHandle::get_loop() noexcept
{
    return handle->loop;
}

bool UVTCPHandle::run_loop() MAYTHROW
{
    return uv_run(handle->loop, UV_RUN_DEFAULT) == 0;
}

void UVTCPHandle::stop_loop() noexcept
{
    uv_stop(handle->loop);
}
