#!/bin/bash
gcc driver_server.c server.c -o driver_server -lpthread
./driver_server