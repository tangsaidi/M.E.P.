#!/bin/sh

#change directory into where the below file are located
cd ~/Desktop

#Initialize these three processes in the background with & sign
python ButtonTest.py &
python SerialHandler.py &
./detectChange &