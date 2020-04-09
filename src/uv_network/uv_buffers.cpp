#include "uv_buffers.h"

UVBuffers::~UVBuffers()
{
    clear();
}

UVBuffers &UVBuffers::instance() noexcept
{
    static UVBuffers instance;
    return instance;
}

void UVBuffers::store(const uv_buf_t &buf) noexcept
{
    if (buf.len < 65536) {
        delete[] buf.base;
        return;
    }
    if (buffers.haveSpace()) { // 2048 * >=65536 bytes
        buffers.push(buf);
    }
    else {
        delete[] buffers.top().base;
        buffers.top() = buf;
    }
}

uv_buf_t UVBuffers::take(size_t size) noexcept
{
    if (buffers.empty() or buffers.top().len < size) {
        return uv_buf_init(new char[size], size);
    }
    return buffers.take();
}

void UVBuffers::clear() MAYTHROW
{
    while (not buffers.empty()) {
        delete[] buffers.take().base;
    }
}
