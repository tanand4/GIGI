#include "../server/server.hpp"
#include "../core/config.hpp"

int main(int argc, char **argv)
{
    srand(time(0));
    json config = getConfig(argc, argv);
    MEMOServer *server = new MEMOServer();
    server->run(config);
}
