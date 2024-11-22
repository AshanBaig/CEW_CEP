sed -i 's/\r//'weather_fetch.sh
#!/bin/bash

# Define the URL and API key
CITY="Karachi"
API_KEY="ac40257f82101fbacf3f2dee95130387"
URL="http://api.openweathermap.org/data/2.5/weather?q=$CITY&appid=$API_KEY"

# Define the output file
OUTPUT_FILE="weather_data.json"

# Fetch weather data and write it to the output file (automatically creates it if it doesn't exist')
curl -s "$URL" -o "$OUTPUT_FILE"

# Check if the file was created and display a message
if [ -f "$OUTPUT_FILE" ]; then
    echo "Weather data successfully fetched and saved to $OUTPUT_FILE"
else
    echo "Failed to fetch weather data."
fi
gcc -o weather_monitor main.c -lcjson



