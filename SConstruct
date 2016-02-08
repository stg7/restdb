import os
import sys
import glob
import multiprocessing

SetOption('num_jobs', multiprocessing.cpu_count()) # build with all aviable cpu cores/threads

env = Environment(CPPPATH = ['/', "leveldb/include/", "mongoose-cpp/"],
                  LIBS = [""],
                  LIBPATH = ['.', 'leveldb/out-shared/', "mongoose-cpp/"],
                  )

env.Decider('MD5')

conf = Configure(env)
libs = ['leveldb', 'mongoose', 'boost_program_options']
for l in libs:
    if not conf.CheckLib(l, language="c++"):
        print "Unable to find lib: " + l + ". Exiting."
        sys.exit(-1)

env.Append(LINKFLAGS=['-Wl,--rpath,leveldb/out-shared/', '-pthread'])

env.Append(CXXFLAGS=['-std=c++11', '-pthread'])

# if you call scons debug=1 debug build is activated
if ARGUMENTS.get('debug', 0) != 0:
    # more checks
    env.Append(CXXFLAGS=['-Wall','-pedantic-errors'])
    # "no" optimization
    env.Append(CCFLAGS=['-O0'])
else:
    env.Append(CXXFLAGS=['-march=native']) # use native architecture
    env.Append(CCFLAGS=['-O3']) # 03

    # loop unrolling and link time optimization, options should be testet
    env.Append(CCFLAGS=['-funroll-loops', '-flto', '-fwhole-program'])

sources = ["get.cpp"] + glob.glob("src/*.cpp")

env.Program('get', sources)

sources = ["import.cpp"] + glob.glob("src/*.cpp")

env.Program('import', sources)

sources = ["restdb.cpp"] + glob.glob("src/*.cpp")

env.Program('restdb', sources)
