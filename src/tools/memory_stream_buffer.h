#ifndef MEMORY_STREAM_BUFFER_H
#define MEMORY_STREAM_BUFFER_H

#include <iostream>
#include <uv.h>

class MemoryStreamBuffer : public std::streambuf
{
public:
    MemoryStreamBuffer(char *base, size_t size) noexcept
    {
        setp(base, base + size);
        setg(base, base, base + size);
    }

    MemoryStreamBuffer(const uv_buf_t &buf) noexcept :
        MemoryStreamBuffer(buf.base, buf.len)
    {

    }

    size_t written() const noexcept
    {
        return pptr() - pbase();
    }

    size_t read() const noexcept
    {
        return gptr() - eback();
    }
};

#endif // MEMORY_STREAM_BUFFER_H
