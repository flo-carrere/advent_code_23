#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief Get the next integer from the input
 * \details This is modifying the input in-place
 *
 * \returns 0 if no integer is found (input is consumed)
 * \returns integer found
 */
int next_integer_from_input(char **input);

/**
 * \brief Max function
 */
int max(int a, int b) { return (a > b) ? a : b; }

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Missing input file");
        return -1;
    }

    // Get input file argument
    char *input = argv[1];
    printf("Input file: %s\n", input);

    FILE *file_pointer;
    int buffer_length = 250;
    char buffer[buffer_length];
    file_pointer = fopen(input, "r");

    // Read line by line
    while (fgets(buffer, buffer_length, file_pointer)) {
        printf("%s", buffer); // no new line accounting for \n in the input
    }

    int sum_part_numbers = 0;
    // Print the output value
    printf("Sum of all the part numbers in the schematic: %d\n", sum_part_numbers);

    fclose(file_pointer);
    return 0;
}

int next_integer_from_input(char **input) {
    char *tmp = *input;
    // Consume input until the next digit indicating an integer
    while (*tmp && !isdigit(*tmp))
        tmp++;

    if (!*tmp)
        return 0;

    // Extract next integer and characters read
    int next = 0, pos = 0;
    if (sscanf(tmp, "%d%n", &next, &pos) != 1)
        return 0;

    // Successful extraction
    // Update input for further extraction
    *input = tmp + pos;
    return next;
}
