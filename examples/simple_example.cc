// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>

#include "rocksdb/db.h"
#include "rocksdb/options.h"
#include "rocksdb/slice.h"

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

int main() {
  auto start = high_resolution_clock::now();

  DB* db;
  Options options;
  // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
  options.IncreaseParallelism();
  options.OptimizeLevelStyleCompaction();
  // create the DB if it's not already present
  options.create_if_missing = true;

  // open DB
  Status s = DB::Open(options, kDBPath, &db);
  assert(s.ok());

  std::vector<std::string> keys;
  std::ifstream in;
  in.open("input.txt");
  std::string str;
  // Read the next line from File untill it reaches the end.
  while (std::getline(in, str))
  {
  // Line contains string of length > 0 then save it in vector.
  if(str. size() > 0)
    keys.push_back(str);
  }
  std::cout<<"keys size"<<keys.size()<<"\n";

  for(int i=0;i<keys.size();i++) {
    // Put key-value
    s = db->Put(WriteOptions(), keys[i], "value");
    assert(s.ok());

    std::string value;
    // get value
    s = db->Get(ReadOptions(), keys[i], &value);
    assert(s.ok());
    assert(value == "value");
  }

  // // atomically apply a set of updates
  // {
  //   WriteBatch batch;
  //   batch.Delete("key1");
  //   batch.Put("zey2", value);
  //   s = db->Write(WriteOptions(), &batch);
  // }

  // s = db->Get(ReadOptions(), "key1", &value);
  // assert(s.IsNotFound());

  // db->Get(ReadOptions(), "zey2", &value);
  // assert(value == "value");

  // {
  //   PinnableSlice pinnable_val;
  //   db->Get(ReadOptions(), db->DefaultColumnFamily(), "zey2", &pinnable_val);
  //   assert(pinnable_val == "value");
  // }

  // {
  //   std::string string_val;
  //   // If it cannot pin the value, it copies the value to its internal buffer.
  //   // The intenral buffer could be set during construction.
  //   PinnableSlice pinnable_val(&string_val);
  //   db->Get(ReadOptions(), db->DefaultColumnFamily(), "zey2", &pinnable_val);
  //   assert(pinnable_val == "value");
  //   // If the value is not pinned, the internal buffer must have the value.
  //   assert(pinnable_val.IsPinned() || string_val == "value");
  // }

  // PinnableSlice pinnable_val;
  // s = db->Get(ReadOptions(), db->DefaultColumnFamily(), "key1", &pinnable_val);
  // assert(s.IsNotFound());
  // // Reset PinnableSlice after each use and before each reuse
  // pinnable_val.Reset();
  // db->Get(ReadOptions(), db->DefaultColumnFamily(), "zey2", &pinnable_val);
  // assert(pinnable_val == "value");
  // pinnable_val.Reset();
  // // The Slice pointed by pinnable_val is not valid after this point
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);

  std::cout << duration.count() <<"ms";
  delete db;

  return 0;
}
