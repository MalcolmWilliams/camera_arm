#!/bin/bash
cd mjpg-streamer
./mjpg_streamer -i "./input_uvc.so -f ./temp -n 20160530_212524_6.png" -o "./output_http.so -w ./www" &
