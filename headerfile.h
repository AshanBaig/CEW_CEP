#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cjson/cJSON.h>

// Function declarations
char* read_file(const char *filename);
double kelvin_to_celsius(double kelvin);
double kelvin_to_fahrenheit(double kelvin);
void parse_and_write_weather_data(const char *json_data, const char *output_filename);


#endif // HEADERFILE_H
