#!/bin/bash

#sudo apt install linux-tools-common
#sudo apt-get install linux-tools-5.0.0-23-generic
#sudo apt-get install linux-cloud-tools-5.0.0-23-generic

sudo cpupower frequency-set --governor performance
./mybenchmark
sudo cpupower frequency-set --governor powersave