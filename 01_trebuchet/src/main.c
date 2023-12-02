#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int extract_calibration_value(char *input);

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Missing input file");
        return -1;
    }

    // Get input file argument
    char *input = argv[1];
    printf("Input file: %s\n", input);

    FILE *file_pointer;
    int buffer_length = 100;
    char buffer[buffer_length];
    file_pointer = fopen(input, "r");

    // Read line by line
    int sum_calibration_for_elves = 0;
    while (fgets(buffer, buffer_length, file_pointer)) {
        int calibration = extract_calibration_value(buffer);
        printf("%s -> %d\n", buffer, calibration);
        sum_calibration_for_elves += calibration;
    }

    // Print the output value
    printf("Sum of calibration values: %d\n", sum_calibration_for_elves);

    fclose(file_pointer);
    return 0;
}

int extract_calibration_value(char *input) {
    size_t input_length = strlen(input) - 1; // excluding \n from the input

    char *start_tmp    = &input[0];
    char *end_tmp      = &input[input_length - 1];
    char calibration[] = "00";

    while (!isdigit(*start_tmp))
        start_tmp++;

    while (!isdigit(*end_tmp))
        end_tmp--;

    // Assign result to final calibration
    calibration[0] = *start_tmp;
    calibration[1] = *end_tmp;

    return atoi(calibration);
}