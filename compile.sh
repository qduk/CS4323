#!/bin/bash
gcc driver.c server.c assistant.c manager.c -o driver -lpthread
./driver