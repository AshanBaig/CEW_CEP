#!/bin/bash


counter=0
max_iterations=12

while [ $counter -lt $max_iterations ]; do 
       /home/rida/CEP/fetch_and_parse.sh >> /home/rida/CEP/fetch_and_parse.log 2>> /home/rida/CEP/fetch_and_parse_error.log
       ((counter++))
       sleep 60
done 

echo "Data Collection completed. Total itr: $max_iterations" >> /home/rida/CEP/fetch_and_parse.log


