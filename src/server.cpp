#include "server.h"
#include "server_client.h"
#include "timezone_db.h"

Server::Server(const char *ip, int port, const std::string &tzdb_filepath) :
    UVAbstractServer(ip, port), tzdb(std::make_unique<TimeZoneDB>())
{
    tzdb->read(tzdb_filepath);
}

Server::~Server() = default;

void Server::query_abbrev(const std::string &abbrev, std::ostream &out) MAYTHROW
{
    tzdb->query(abbrev, out);
}

UVAbstractClient *Server::create_client() MAYTHROW
{
    return new ServerClient(this);
}

void Server::on_client_connect(ServerClient */*client*/) MAYTHROW
{
    std::cout << "Server: client connected" << std::endl;
}

void Server::on_client_disconnect(ServerClient */*client*/) MAYTHROW
{
    std::cout << "Server: client disconnected" << std::endl;
}
