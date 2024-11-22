#include "headerfile.h"

#define MAX_LINE_LENGTH 256

//THIS FILE IS CALCULATING THE AVERAGE OF DATA AND PRINTING IT ON THE TERMINAL TOO

// Structure to hold the weather data
typedef struct {
    char datetime[30];  // Human-readable date/time
    double temperature;  // Temperature in Kelvin
    double humidity;     // Humidity in percentage
    double visibility;   // Visibility in meters
    char weather_description[100]; // Weather description
    time_t timestamp;    // Unix timestamp
} WeatherData;

// Function to read the CSV file and parse the data
int read_weather_data(const char *filename, WeatherData *data, int max_entries) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file %s for reading\n", filename);
        return -1;
    }

    int count = 0;
    char line[MAX_LINE_LENGTH];

    // Skip the header line
    fgets(line, sizeof(line), file);

    // Read each line and parse the data
    while (fgets(line, sizeof(line), file) && count < max_entries) {
        sscanf(line, "%[^,],%lf,%lf,%lf,%[^,],%ld",
               data[count].datetime,
               &data[count].temperature,
               &data[count].humidity,
               &data[count].visibility,
               data[count].weather_description,
               &data[count].timestamp);
        count++;
    }

    fclose(file);
    return count;
}

// Function to calculate the average of a given data array
double calculate_average(double *values, int count) {
    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += values[i];
    }
    return sum / count;
}

// Function to convert Kelvin to Celsius
double kelvin_to_celsius(double kelvin) {
    return kelvin - 273.15;
}

// Function to convert Kelvin to Fahrenheit
double kelvin_to_fahrenheit(double kelvin) {
    return (kelvin - 273.15) * 9.0 / 5.0 + 32.0;
}

// Function to format the Unix timestamp into a readable date-time
void format_datetime(time_t timestamp, char *datetime_str) {
    struct tm *time_info = localtime(&timestamp);
    strftime(datetime_str, 30, "%Y-%m-%d %H:%M:%S", time_info);
}

// Function to analyze the weather data and save the results to a file
void analyze_weather_data(WeatherData *data, int count, const char *output_filename) {
    double temperatures[count];
    double humidities[count];
    double visibilities[count];

    // Extract the data for analysis
    for (int i = 0; i < count; i++) {
        temperatures[i] = data[i].temperature;
        humidities[i] = data[i].humidity;
        visibilities[i] = data[i].visibility;
    }

    // Calculate averages
    double avg_temp = calculate_average(temperatures, count);
    double avg_humidity = calculate_average(humidities, count);
    double avg_visibility = calculate_average(visibilities, count);

    // Write the results to the output file
    FILE *output_file = fopen(output_filename, "a");  // Open in append mode
    if (!output_file) {
        fprintf(stderr, "Could not open file %s for writing\n", output_filename);
        return;
    }

    // Write to the file
    fprintf(output_file, "Weather Data Analysis (Date: %s)\n", data[0].datetime);
    fprintf(output_file, "-------------------------------------------------\n");

    // Printing and saving the average values
    fprintf(output_file, "Average Temperature: %.2f K | %.2f �C | %.2f �F\n", avg_temp, kelvin_to_celsius(avg_temp), kelvin_to_fahrenheit(avg_temp));
    fprintf(output_file, "Average Humidity: %.2f %%\n", avg_humidity);
    fprintf(output_file, "Average Visibility: %.2f m\n", avg_visibility);
    fprintf(output_file, "-------------------------------------------------\n");

    fclose(output_file);


    // Print the results to the terminal
    printf("\nWeather Data Analysis (Date: %s)\n", data[0].datetime);
    printf("-------------------------------------------------\n");

    // Printing the average values to terminal
    printf("Average Temperature: %.2f K | %.2f �C | %.2f �F\n", avg_temp, kelvin_to_celsius(avg_temp), kelvin_to_fahrenheit(avg_temp));
    printf("Average Humidity: %.2f %%\n", avg_humidity);
    printf("Average Visibility: %.2f m\n", avg_visibility);
    printf("-------------------------------------------------\n");

    printf("\nAnalysis results saved to %s\n", output_filename);
}

int main() {
    WeatherData weather_data[1000]; // Assuming a max of 1000 records in the file

    int data_count = read_weather_data("temp.csv", weather_data, 1000);
    if (data_count > 0) {
        const char *output_filename = "weather_analysis_output.txt";
        analyze_weather_data(weather_data, data_count, output_filename);
    } else {
        printf("No data available for analysis.\n");
    }

    return 0;
}
