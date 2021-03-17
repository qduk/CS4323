#!/bin/bash
gcc driver.c server.c -o driver -lpthread
./driver