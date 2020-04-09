#include "server_client.h"
#include "server.h"
#include "utility/memory_stream_buffer.h"

ServerClient::ServerClient(Server *server) noexcept :
    UVAbstractClient(server->get_loop()), server(server)
{

}

void ServerClient::on_connect() MAYTHROW
{
    server->on_client_connect(this);
    std::cout << "Connected" << std::endl;
}

void ServerClient::on_read(char *data, size_t size) MAYTHROW
{
    auto req = std::string_view(data, size);
    if (req.back() == '\n') {
        req.remove_suffix(1);
    }
    std::cout << "Got request: " << req << std::endl;
    std::string request;
    request.reserve(req.size());
    std::transform(req.begin(), req.end(), std::back_inserter(request), toupper);
    auto buf = get_buffer();
    MemoryStreamBuffer sbuf(buf);
    std::ostream out(&sbuf);
    try {
        server->query_abbrev(request, out);
    }
    catch (std::out_of_range &) {
        out << "timezone abbreviation is not found" << std::endl;
    }
    write(buf, sbuf.written());
}

void ServerClient::on_disconnect() MAYTHROW
{
    std::cout << "Disconnected" << std::endl;
    server->on_client_disconnect(this);
    delete this;
}
