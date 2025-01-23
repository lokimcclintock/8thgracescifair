#!/bin/bash

for i in $(seq 1 9)
do
    time (./sort dates $i > /dev/null)
done
