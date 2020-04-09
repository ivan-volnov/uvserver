#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include "uv_network/uv_network.h"

class Server;

class ServerClient : public UVAbstractClient
{
public:
    ServerClient(Server *server) noexcept;

private:
    void on_connect() MAYTHROW override;
    void on_read(char *data, size_t size) MAYTHROW override;
    void on_disconnect() MAYTHROW override;

private:
    Server * const server;
};

#endif // SERVER_CLIENT_H
