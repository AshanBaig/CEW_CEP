#include "headerfile.h"
//THIS C FILE READS THE CONTENTS OF THE JSON FILE AND PARSES THEM INTO A CSV FILE WHILE ALSO PRINTING THE CURRENT DATA ONTO THE TERMINAL

// Function to read the contents of the JSON file into a string
char* read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file %s for reading\n", filename);
        return NULL;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file contents
    char *file_data = (char *)malloc(file_size + 1);
    if (!file_data) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    // Read the file content into the buffer
    fread(file_data, 1, file_size, file);
    file_data[file_size] = '\0';  // Null-terminate the string

    fclose(file);

    return file_data;
}

// Function to convert Kelvin to Celsius
double kelvin_to_celsius(double kelvin) {
    return kelvin - 273.15;
}

// Function to convert Kelvin to Fahrenheit
double kelvin_to_fahrenheit(double kelvin) {
    return (kelvin - 273.15) * 9.0 / 5.0 + 32.0;
}

// Function to parse the JSON data, extract necessary weather details,
// write them to a CSV file, and display the current weather details
void parse_and_write_weather_data(const char *json_data, const char *output_filename) {
    cJSON *json = cJSON_Parse(json_data);
    if (json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    // Extract temperature, humidity, visibility, and weather description from the JSON
    cJSON *main_obj = cJSON_GetObjectItemCaseSensitive(json, "main");
    cJSON *weather_arr = cJSON_GetObjectItemCaseSensitive(json, "weather");
    cJSON *visibility_item = cJSON_GetObjectItemCaseSensitive(json, "visibility");

    if (cJSON_IsObject(main_obj) && cJSON_IsArray(weather_arr) && cJSON_IsNumber(visibility_item)) {
        // Extract the first weather description (if present)
        cJSON *weather_item = cJSON_GetArrayItem(weather_arr, 0);
        const char *weather_description = cJSON_GetObjectItemCaseSensitive(weather_item, "description")->valuestring;

        // Extract other weather data
        cJSON *temp_item = cJSON_GetObjectItemCaseSensitive(main_obj, "temp");
        cJSON *humidity_item = cJSON_GetObjectItemCaseSensitive(main_obj, "humidity");

        if (cJSON_IsNumber(temp_item) && cJSON_IsNumber(humidity_item)) {
            // Get the current date and time
            time_t now;
            struct tm *time_info;
            char date_time_str[20];  // Format: YYYY-MM-DD HH:MM:SS
            time(&now);
            time_info = localtime(&now);
            strftime(date_time_str, sizeof(date_time_str), "%Y-%m-%d %H:%M:%S", time_info);

            // Display the current weather details
            printf("\nCurrent Weather (Date: %s)\n", date_time_str);
            printf("-------------------------------------------------\n");
            printf("Temperature: %.2f K | %.2f �C | %.2f �F\n",
                   temp_item->valuedouble,
                   kelvin_to_celsius(temp_item->valuedouble),
                   kelvin_to_fahrenheit(temp_item->valuedouble));
            printf("Humidity: %.2f %%\n", humidity_item->valuedouble);
            printf("Visibility: %.2f m\n", visibility_item->valuedouble);
            printf("Description: %s\n", weather_description);
            printf("-------------------------------------------------\n");

            // Open the output file for appending (create if doesn't exist)
            FILE *output_file = fopen(output_filename, "a");
            if (!output_file) {
                fprintf(stderr, "Could not open file %s for writing\n", output_filename);
                cJSON_Delete(json);
                return;
            }

            // Write the header to the file if it's the first time running
            if (ftell(output_file) == 0) {
                fprintf(output_file, "Date/Time,Temperature (K),Temperature (�C),Temperature (�F),Humidity (%%),Visibility (m),Weather Description\n");
            }

            // Write the weather data in CSV format
            fprintf(output_file, "\"%s\",%.2f,%.2f,%.2f,%.2f,%.2f,\"%s\"\n",
                    date_time_str,
                    temp_item->valuedouble,
                    kelvin_to_celsius(temp_item->valuedouble),
                    kelvin_to_fahrenheit(temp_item->valuedouble),
                    humidity_item->valuedouble,
                    visibility_item->valuedouble,
                    weather_description);

            // Close the output file
            fclose(output_file);
            printf("Data saved to %s\n", output_filename);
        } else {
            printf("Temperature, humidity, or visibility data not found in JSON\n");
        }
    } else {
        printf("Main object or weather array not found in JSON\n");
    }

    // Clean up the parsed JSON object
    cJSON_Delete(json);
}

int main() {
    // Read the JSON data from the file
    const char *filename = "weather_data.json";  // Name of the file containing the fetched weather data
    char *json_data = read_file(filename);
    if (json_data == NULL) {
        return 1;
    }

    // Parse the JSON and write the weather data to a CSV file
    const char *output_filename = "parsed_weather.csv";  // Output file for parsed data
    parse_and_write_weather_data(json_data, output_filename);

    // Clean up the allocated memory
    free(json_data);

    return 0;
}
