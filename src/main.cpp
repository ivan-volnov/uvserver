#include "server.h"
#include "uv_network/uv_buffers.h"

int main(int /*argc*/, char **argv)
{
    const auto host = "0.0.0.0";
    const auto port = 9000;

    std::cout << "Listening " << host << " " << port << std::endl;
    {
        std::string tzdb_filepath(*argv);
        tzdb_filepath.resize(tzdb_filepath.rfind('/') + 1);
        tzdb_filepath.append("date_time_zonespec.csv");
        Server server(host, port, tzdb_filepath);
        server.run_loop();
        UVBuffers::instance().clear();
    }
    std::cout << "Shutdown" << std::endl;
}
