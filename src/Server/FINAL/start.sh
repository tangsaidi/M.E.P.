#!/bin/sh
cd ~/Desktop
python ButtonTest.py &
python SerialHandler.py &
./detectChange &