#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_PART_2

int extract_calibration_value(char *input);

int is_string_digit(char *input);

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

    char *start_tmp = &input[0];
    char *end_tmp   = &input[input_length - 1];
    int calibration[2];

    while (1) {
        if (isdigit(*start_tmp)) {
            calibration[0] = *start_tmp - '0';
            printf("Found %d\n", calibration[0]);
            break;
        }

#ifdef CHECK_PART_2
        int string_digit = is_string_digit(start_tmp);
        if (string_digit >= 0) {
            calibration[0] = string_digit;
            break;
        }
#endif
        start_tmp++;
    }

    while (1) {
        if (isdigit(*end_tmp)) {
            calibration[1] = *end_tmp - '0';
            printf("Found %d\n", calibration[1]);
            break;
        }

#ifdef CHECK_PART_2
        int string_digit = is_string_digit(end_tmp);
        if (string_digit >= 0) {
            calibration[1] = string_digit;
            break;
        }
#endif
        end_tmp--;
    }

    return (calibration[0] * 10) + calibration[1];
}

int is_string_digit(char *input) {
    char str_digits[10][6]  = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int str_digits_size[10] = {4, 3, 3, 5, 4, 4, 3, 5, 5, 4};

    for (int i = 0; i < 10; ++i) {
        if (!strncmp(input, &str_digits[i][0], str_digits_size[i])) {
            printf("Found %s\n", &str_digits[i][0]);
            return i;
        }
    }
    return -1;
}