restdb -- leveldb rest server
==============
[TOC]

authors:
> stg7@gmx.de

About
-----
restdb is a small lookup rest server for [leveldb](https://github.com/google/leveldb).

Requirements
------------
* scons
* g++
* boost (boost_program_options)
* all dependencies that [leveldb](https://github.com/google/leveldb) and [mongoose-cpp](https://github.com/Gregwar/mongoose-cpp) has

First Start
-----------
First you must run
> ./prepare.sh

for downloading all needed thirdparty libs (leveldb and mongoose-cpp)

Then the server can be compiled with
> scons

After compilation runs without problems, you can run the webserver with
> ./restdb

```
Starts a webservice for lookup of values based on a key.
Allowed options:
  -h [ --help ]             produce help message
  -p [ --port ] arg (=8080) port number of webservice
  --dbname arg (=DB)        dbname
```

Import Data
-----------
In general the leveldb database is empty, therefore an import is needed, you can use the "import" tool for this step
> echo -e "mykey\tmyvalue" | ./import

will import "mykey-> myvalue" to the default database "DB"

```
Reads key values from stdin.
Allowed options:
  -h [ --help ]               produce help message
  -d [ --delimiter ] arg (= ) delimiter of key and value
  --dbname arg (=DB)          dbname
```

For more import speed just redirect stdout to /dev/null
