README: Weather Alert System
This README provides instructions for setting up and running the Weather Alert System, a
project that integrates environmental monitoring using C programs and Bash scripts. The
system fetches real-time weather data, processes it, calculates averages, and sends alerts
based on predefined thresholds.

Prerequisites
1. Linux Environment: Ensure you have a Linux-based system with Bash installed.
C Compiler: Install GCC to compile the C programs.
sudo apt-get install gcc
2. cJSON Library: Install the cJSON library for JSON parsing in C.
sudo apt-get install libcjson-dev
3. Curl: Ensure Curl is installed for API requests.
sudo apt-get install curl
4. msmtp: Configure msmtp for sending email alerts.
sudo apt-get install msmtp.

Setup Instructions
1. Clone the repository or place the project files in a directory.
2. Ensure the following files are present:
○ weather_fetch.sh
○ weather_monitor.c
○ calc_avg.sh
○ scheduler2.sh
3. Make all shell scripts executable:
chmod +x *.sh
4. Compile the C programs:
weather_monitor:
gcc -o weather_monitor weather_monitor.c -lcjson
weather_analysis:
gcc -o weather_analysis weather_analysis.c
Execution Instructions
Run the Main Scheduler Script: Execute scheduler2.sh, which automates the entire
process of fetching, parsing, and analyzing weather data:
./scheduler2.sh

1. Process Overview:
○ The script fetches weather data via the OpenWeather API using
weather_fetch.sh.
○ The weather_monitor C program parses the JSON data and saves it to
parsed_weather.csv.
○ The calc_avg.sh script calculates the averages and sends email alerts if
thresholds are met.
○ The entire process is scheduled to run multiple iterations, with logs saved for
monitoring execution status.
2. Check Outputs:
○ Weather Data: weather_data.json
○ Parsed Data: parsed_weather.csv
○ Averages: weather_analysis_output.txt
○ Logs: fetch_and_parse.log, fetch_and_parse_error.log
3. Example Outputs:
○ Averages for temperature, humidity, and visibility in
weather_analysis_output.txt.
○ Email alerts for conditions exceeding predefined thresholds.
