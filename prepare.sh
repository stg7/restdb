#!/bin/bash

git clone https://github.com/google/leveldb.git
cd leveldb
make -j 4
cd ..

git clone https://github.com/Gregwar/mongoose-cpp.git
cd mongoose-cpp
cmake CMakeLists.txt
make -j 4
cd ..