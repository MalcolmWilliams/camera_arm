#!/bin/bash
cd mjpg-streamer
./mjpg_streamer -i "./input_uvc.so" -o "./output_http.so -w ./www" &
