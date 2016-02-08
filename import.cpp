#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <boost/program_options.hpp>

#include "leveldb/db.h"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

int main(int argc, const char * argv[]) {
    namespace po = boost::program_options;

    // declare the supported options.
    po::options_description desc("Reads key values from stdin.\nAllowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("delimiter,d", po::value<unsigned char>()->default_value('\t'), "delimiter of key and value")
        ("dbname", po::value<std::string>()->default_value("DB"), "dbname")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    unsigned char delimiter = vm["delimiter"].as<unsigned char>();
    std::string dbname = vm["dbname"].as<std::string>();

    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, dbname, &db);
    assert(status.ok());

    std::string input_line;

    while(std::cin) {
        getline(std::cin, input_line);

        std::vector<std::string> x = split(input_line, delimiter);

        if (x.size() == 2) {
            std::cout << x[0] << "  " << x[1] << std::endl;
            db->Put(leveldb::WriteOptions(), x[0], x[1]);
        }
    };

    delete db;
    db = nullptr;
}