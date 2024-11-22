#!/bin/bash
# Step3: Run the analysis program to analyze the weather data
gcc -o weather_analysis weather_analysis.c
./weather_analysis  # This will analyze the parsed weather data in parsed_weather.csV


   
OUTPUT_FILE="weather_analysis_output.txt"    # The output file where averages are saved
ALERT_EMAIL="ridanafeesqasmi@gmail.com" # The recipient email

# Run the C program to calculate averages and save to file
#$C_PROGRAM

# Fetch the last values of temperature, humidity, and visibility from the output file
RAW_TEMP=$(tail -n 10 $OUTPUT_FILE | grep "Average Temperature" | tail -n 1)
RAW_HUMIDITY=$(tail -n 10 $OUTPUT_FILE | grep "Average Humidity" | tail -n 1)
RAW_VISIBILITY=$(tail -n 10 $OUTPUT_FILE | grep "Average Visibility" | tail -n 1)

# Debugging prints to show raw lines
#echo "Raw Temperature Line: $RAW_TEMP"
#echo "Raw Humidity Line: $RAW_HUMIDITY"
#echo "Raw Visibility Line: $RAW_VISIBILITY"

# Extract the average values using awk and sed
AVERAGE_TEMP=$(echo $RAW_TEMP | awk -F'|' '{print $2}' | sed 's/[^0-9.]//g')
AVERAGE_HUMIDITY=$(echo $RAW_HUMIDITY | awk -F': ' '{print $2}' | sed 's/[^0-9.]//g')
AVERAGE_VISIBILITY=$(echo $RAW_VISIBILITY | awk -F': ' '{print $2}' | sed 's/[^0-9.]//g')

# Debugging prints to check extracted values
#echo "Extracted Temperature: $AVERAGE_TEMP"
#echo "Extracted Humidity: $AVERAGE_HUMIDITY"
#echo "Extracted Visibility: $AVERAGE_VISIBILITY"

# Check if the values are non-empty and valid
if [[ -z "$AVERAGE_TEMP" || -z "$AVERAGE_HUMIDITY" || -z "$AVERAGE_VISIBILITY" ]]; then
    echo "Error: One or more average values are missing."
    exit 1
fi

# Check the conditions
TEMP_ALERT=""
HUMIDITY_ALERT=""
VISIBILITY_ALERT=""

# Compare the values with the thresholds using bc
if [ $(echo "$AVERAGE_TEMP > 30" | bc) -eq 1 ]; then
    TEMP_ALERT="ALERT: The temperature is now above 30 degree celsius. Please stay hydrated and take cold bath!"
fi

if [ $(echo "$AVERAGE_HUMIDITY > 70" | bc) -eq 1 ]; then
    HUMIDITY_ALERT="ALERT: The humidity is now above 50%. Take shower, wear breathable clothes, and stay hydrated!"
fi

if [ $(echo "$AVERAGE_VISIBILITY < 25" | bc) -eq 1 ]; then
    VISIBILITY_ALERT="ALERT: The visibility is now below 25 meters. Use fog lights and be cautious. Make sure to drive carefully."
fi

# If any condition is met, send an email
if [ ! -z "$TEMP_ALERT" ] || [ ! -z "$HUMIDITY_ALERT" ] || [ ! -z "$VISIBILITY_ALERT" ]; then
    ALERT_MESSAGE="Weather Alert!\n\n"
    ALERT_MESSAGE+="$TEMP_ALERT\n"
    ALERT_MESSAGE+="$HUMIDITY_ALERT\n"
    ALERT_MESSAGE+="$VISIBILITY_ALERT\n"

    echo -e "Subject: WEATHER ALERTS!\n\n$ALERT_MESSAGE" | msmtp $ALERT_EMAIL

    #echo -e "$ALERT_MESSAGE" | msmtp $ALERT_EMAIL
    echo "Alert Email sent to $ALERT_EMAIL"
else
    echo "No alerts, all conditions are normal."
fi


