// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <execinfo.h>
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


#include "rocksdb/db.h"
#include "rocksdb/options.h"
#include "rocksdb/slice.h"
#include "rocksdb/statistics.h"
#include "rocksdb/system_clock.h"
#include "rocksdb/perf_context.h"

#include <chrono>
using namespace std::chrono;

using ROCKSDB_NAMESPACE::DB;
using ROCKSDB_NAMESPACE::Options;
using ROCKSDB_NAMESPACE::PinnableSlice;
using ROCKSDB_NAMESPACE::ReadOptions;
using ROCKSDB_NAMESPACE::Status;
using ROCKSDB_NAMESPACE::WriteBatch;
using ROCKSDB_NAMESPACE::WriteOptions;

#if defined(OS_WIN)
std::string kDBPath = "C:\\Windows\\TEMP\\rocksdb_simple_example";
#else
std::string kDBPath = "/tmp/rocksdb_simple_example";
#endif

namespace ROCKSDB_NAMESPACE {
int run(int threads) {

  rocksdb::SetPerfLevel(rocksdb::PerfLevel::kEnableTime);

  // Create and open a text file
  std::ofstream MyFile("output.txt");
    int i=8;

    DB* db;
    Options options;
    // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
    options.IncreaseParallelism(i);
    options.OptimizeLevelStyleCompaction();
    options.statistics = CreateDBStatistics();
    // options.write_buffer_size = 128; 
    // update the size of memtable using this option

    // create the DB if it's not already present
    options.create_if_missing = true;
    ROCKSDB_NAMESPACE::Env* env = ROCKSDB_NAMESPACE::Env::Default();
    const auto& clock = env->GetSystemClock();
    // signal(SIGSEGV, handler);   // install our handler

    // open DB
    Status s = DB::Open(options, kDBPath, &db);
    assert(s.ok());

    std::vector<std::string> keys;
    std::ifstream in;
    in.open("input.txt");
    std::string str;
    while (std::getline(in, str))
    {
    if(str. size() > 0)
      keys.push_back(str);
    }
    std::cout<<"keys size"<<keys.size()<<"\n";

    uint64_t start_time = clock->NowMicros();

    for(int i=0;i<keys.size();i++) {
      // Put key-value
      s = db->Put(WriteOptions(), keys[i], "value");
      assert(s.ok());
    }

    uint64_t end_time = clock->NowMicros();
    double elapsed = static_cast<double>(end_time - start_time) * 1e-6;

    MyFile << i << " " << elapsed << " ";

    // ----- read ------

    start_time = clock->NowMicros();

    for(int i=0;i<keys.size();i++) {
      std::string value;
      // get value
      s = db->Get(ReadOptions(), keys[i], &value);
      assert(s.ok());
      assert(value == "value");
    }
    end_time = clock->NowMicros();
    elapsed = static_cast<double>(end_time - start_time) * 1e-6;

    MyFile<< elapsed << " ";
    MyFile <<static_cast<double>(rocksdb::get_perf_context()->user_key_comparison_count)<<" ";
    MyFile <<static_cast<double>(rocksdb::get_perf_context()->get_from_memtable_time )<<" ";
    MyFile <<static_cast<double>(rocksdb::get_perf_context()->write_memtable_time )<<" ";


    delete db;
    MyFile.close();
    return 0;
}
}

using namespace ROCKSDB_NAMESPACE;
int main(int argc, char** argv) {
  run(std::atoi(argv[0]));
  return 0;
}