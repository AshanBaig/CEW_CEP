#!/bin/bash
#This file will first call the weather fetch and get the data from API in JSon file called "weather_data"
#Then it will call the weather_monitor which will parse the data from json file to csv file "Parse_weather" and display it on the terminal
#Then in the end weather_analysis is called that will calculate average and display it on the terminal and also save it in a txt file called "weather_analysis_output.txt"

# Step 1: Fetch weather dat
./weather_fetch.sh
# Step 2: Run the C program to parse the JSON da
./weather_monitor  # This will run the compiled C program

echo 'Parsed_weather file created'
