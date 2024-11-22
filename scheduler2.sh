#!/bin/bash

TEMP_FILE="temp.csv"
PARSED_WEATHER="parsed_weather.csv"

> $TEMP_FILE

counter=0
max_iterations=13

while [ $counter -lt $max_iterations ]; do
	./fetch_and_parse.sh >> fetch_and_parse.log 2>> fetch_and_parse_error.log
	((counter++))
	sleep 5
done
tail -n 12 $PARSED_WEATHER > $TEMP_FILE
echo "DATA COLLECTION COMPLETED. TOTAL ITR: $max_iterations" >> fetch_and_parse.log

echo "Calculating AVG..." >> fetch_and_parse.log
./calc_avg.sh
if [ $? -eq 0 ]; then
echo "calc_avg.sh exceuted!" >> fetch_and_parse.log
else
echo "ERROR!" >> fetch_and_parse.log
fi 
echo "Avg calculated"  >> fetch_and_parse.log



