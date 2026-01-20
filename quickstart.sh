#!/bin/bash
cd database && make drop && make build
cd ..
cd build && cmake .. && cmake --build .
./rogue

