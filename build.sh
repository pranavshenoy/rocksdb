#!/bin/bash

DEBUG_LEVEL=0 make static_lib

echo "Building benchmark"

DEBUG_LEVEL=0 make run_microbench