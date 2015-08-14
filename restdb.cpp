#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <unistd.h>

#include <boost/program_options.hpp>

#include <mongoose/Server.h>
#include <mongoose/WebController.h>
#include "leveldb/db.h"


using namespace Mongoose;

class WebServer : public WebController {
    private:
        leveldb::DB* db;
        std::string _dbname;

    public:
        WebServer(std::string dbname): _dbname(dbname) {}

        void index(Request &request, StreamResponse &response) {
            response << "{\"error\":\"not a valid request\"}" << std::endl;
        }

        void by_key(Request &request, StreamResponse &response) {
            std::string key = request.get("key", "");
            std::string value = "42";

            leveldb::Status s = db->Get(leveldb::ReadOptions(), key, &value);
            if (!s.ok()) {
                key = "invalid";
            }
            response << "{\"key\": \"" << key << "\", \"value\":" << value << " }" << std::endl;
        }

        void setup() {
            leveldb::Options options;
            options.create_if_missing = true;
            leveldb::Status status = leveldb::DB::Open(options, _dbname, &db);
            assert(status.ok());

            addRoute("GET", "/", WebServer, index);
            addRoute("GET", "/by_key", WebServer, by_key);
        }
};


int main(int argc, const char * argv[]) {
    namespace po = boost::program_options;

    // declare the supported options.
    po::options_description desc("Starts a webservice for lookup of values based on a key.\nAllowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("port,p", po::value<unsigned int>()->default_value(8080), "port number of webservice")
        ("dbname", po::value<std::string>()->default_value("DB"), "dbname")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    unsigned int port = vm["port"].as<unsigned int>();
    std::string dbname = vm["dbname"].as<std::string>();

    WebServer controller(dbname);
    Server server(port);
    server.registerController(&controller);

    server.start();

    while (1) {
        usleep(1000000);
    }
}
