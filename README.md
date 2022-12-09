## RocksDB: A Persistent Key-Value Store for Flash and RAM Storage

[![CircleCI Status](https://circleci.com/gh/facebook/rocksdb.svg?style=svg)](https://circleci.com/gh/facebook/rocksdb)
[![Appveyor Build status](https://ci.appveyor.com/api/projects/status/fbgfu0so3afcno78/branch/main?svg=true)](https://ci.appveyor.com/project/Facebook/rocksdb/branch/main)
[![PPC64le Build Status](http://140-211-168-68-openstack.osuosl.org:8080/buildStatus/icon?job=rocksdb&style=plastic)](http://140-211-168-68-openstack.osuosl.org:8080/job/rocksdb)

RocksDB is developed and maintained by Facebook Database Engineering Team.
It is built on earlier work on [LevelDB](https://github.com/google/leveldb) by Sanjay Ghemawat (sanjay@google.com)
and Jeff Dean (jeff@google.com)

This code is a library that forms the core building block for a fast
key-value server, especially suited for storing data on flash drives.
It has a Log-Structured-Merge-Database (LSM) design with flexible tradeoffs
between Write-Amplification-Factor (WAF), Read-Amplification-Factor (RAF)
and Space-Amplification-Factor (SAF). It has multi-threaded compactions,
making it especially suitable for storing multiple terabytes of data in a
single database.

Start with example usage here: https://github.com/facebook/rocksdb/tree/main/examples

See the [github wiki](https://github.com/facebook/rocksdb/wiki) for more explanation.

The public interface is in `include/`.  Callers should not include or
rely on the details of any other header files in this package.  Those
internal APIs may be changed without warning.

Questions and discussions are welcome on the [RocksDB Developers Public](https://www.facebook.com/groups/rocksdb.dev/) Facebook group and [email list](https://groups.google.com/g/rocksdb) on Google Groups.

## License

RocksDB is dual-licensed under both the GPLv2 (found in the COPYING file in the root directory) and Apache 2.0 License (found in the LICENSE.Apache file in the root directory).  You may select, at your option, one of the above-listed licenses.


## How to run our code :

1. From the terminal, at root level run :
   'make static_lib'

2. then go to the examples folder where our test cases are present and make all files :
   'cd examples/; make all'

3. run 'python3 rand_str_gen.py' to generate 4M random keys.

4. now you can run the test case "simple_example.cc" by :
   ./simple_example

5. you will now see an output file 'output.txt' getting created which will contain metrics such as get time, put time and key comparison count.


We have fixed and tested compaction in the branch stable-so-far. But we are facing issues while running the code in skyros for some reason. The code works in mac OS but it works intermittently in skyros. So we are turning our old code that had failing compaction but we would like to put it on record that we fixed the compaction issue and evaluated it with 8.4 million keys. 


You can change the number of keys by changing the "rand_str_gen.py" file in examples. Keys will be generated in the "inputs.txt" file. You can also change the number of threads in the test script to 1,2,4,8,16.

After successfully running the test script "simple_example.cc", you can find the number of threads, execution time for put, get, key comparison count respectively in "examples\output.txt".

Also, if you want to run for lower workloads, which runs on all operating systems, you can refer to our other branch and run the code similarly.