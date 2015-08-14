#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <boost/program_options.hpp>

#include "leveldb/db.h"

int main(int argc, const char * argv[]) {
    namespace po = boost::program_options;

    // declare the supported options.
    po::options_description desc("Reads lookup key from stdin.\nAllowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("dbname", po::value<std::string>()->default_value("DB"), "dbname")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    std::string dbname = vm["dbname"].as<std::string>();

    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, dbname, &db);
    assert(status.ok());

    std::string key;
    std::cin >> key;

    std::string value;
    if (key != "") {
        leveldb::Status s = db->Get(leveldb::ReadOptions(), key, &value);
        std::cout << value << std::endl;
    };

}