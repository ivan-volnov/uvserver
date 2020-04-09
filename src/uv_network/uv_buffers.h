#ifndef UV_BUFFERS_H
#define UV_BUFFERS_H

#include "../tools/stack.h"
#include "../tools/global.h"
#include <uv.h>


class UVBuffers
{
public:
    ~UVBuffers();

    UVBuffers(const UVBuffers &) = delete;
    UVBuffers(UVBuffers &&) = delete;
    UVBuffers &operator = (const UVBuffers &) = delete;
    UVBuffers &operator = (UVBuffers &&) = delete;

    static UVBuffers &instance() noexcept;

public:
    void store(const uv_buf_t &buf) noexcept;
    uv_buf_t take(size_t size = 65536) noexcept;
    void clear() MAYTHROW;

private:
    UVBuffers() noexcept = default;

    Stack<uv_buf_t, 2048> buffers;
};

#endif // UV_BUFFERS_H
