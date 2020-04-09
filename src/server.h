#ifndef SERVER_H
#define SERVER_H

#include "uv_network/uv_network.h"
#include <iostream>

class ServerClient;
class TimeZoneDB;

class Server : public UVAbstractServer
{
    friend class ServerClient;
public:
    Server(const char *ip, int port, const std::string &tzdb_filepath) MAYTHROW;
    ~Server() override;

    Server(const Server &) = delete;
    Server(Server &&) = delete;
    Server &operator = (const Server &) = delete;
    Server &operator = (Server &&) = delete;

public:
    void query_abbrev(const std::string &abbrev, std::ostream &out) MAYTHROW;

private:
    UVAbstractClient *create_client() MAYTHROW override;

    void on_client_connect(ServerClient *client) MAYTHROW;
    void on_client_disconnect(ServerClient *client) MAYTHROW;

private:
    std::unique_ptr<TimeZoneDB> tzdb;
};

#endif // SERVER_H
