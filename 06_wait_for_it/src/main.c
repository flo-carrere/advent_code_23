#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief Get the next integer from the input up to the stop character or end of
 * \details This is modifying the input in-place
 *
 * \returns 0 if no integer is found (input is consumed)
 * \returns integer found
 */
int64_t next_integer_from_input(char **input, char stop_char);

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

    int64_t times[100]   = {};
    int64_t records[100] = {};
    int race             = 0;

    // Read 1st line of times
    fgets(buffer, buffer_length, file_pointer);
    char *current_pos = buffer;
    while (1) {
        int64_t time = next_integer_from_input(&current_pos, '*');

        if (time == 0)
            break;

        times[race++] = time;
    }

    // Read 2nd line of records
    fgets(buffer, buffer_length, file_pointer);
    race        = 0;
    current_pos = buffer;
    while (1) {
        int64_t record = next_integer_from_input(&current_pos, '*');
        if (record == 0)
            break;
        records[race++] = record;
    }

    // Resolution
    uint64_t product_ways = 1;
    for (int i = 0; i < race; ++i) {
        // This a 2nd degree inequation with x=hold time
        // (time-x)*x > record
        // -x^2 + time*x - distance > 0
        // solution range is: ]x1 ; x2[ <=> [ceil(x1) ; floor(x2)]
        int64_t a = -1, b = times[i], c = -records[i];
        double delta = (b * b) - (4 * a * c);
        // As a is negative will have x1 < x2
        double x1 = (-b + sqrt(delta)) / (2 * a);
        double x2 = (-b - sqrt(delta)) / (2 * a);

        if (x1 != (int64_t)x1) {
            // This solution should be rounded up to the next integer
            x1 = ceil(x1);
        } else {
            // If it is already rounded, it should be excluded as we want to break
            // the record, not equalize it
            x1 += 1;
        }

        if (x2 != (int64_t)x2) {
            // This solution should be rounded down to the next integer
            x2 = floor(x2);
        } else {
            // If it is already rounded, it should be excluded as we want to break
            // the record, not equalize it
            x2 -= 1;
        }

        // Display
        printf("Race: %lld %lld\n", times[i], records[i]);
        printf("x1:%f x2:%f delta:%f\n", x1, x2, delta);
        product_ways *= (x2 - x1 + 1);
    }

    // Print the output value
    printf("Product of ways to break records: %d\n", product_ways);

    fclose(file_pointer);
    return 0;
}

int64_t next_integer_from_input(char **input, char stop_char) {
    char *tmp = *input;
    // Consume input until the next digit indicating an integer
    while (*tmp && !isdigit(*tmp) && (*tmp != stop_char))
        tmp++;

    if (!*tmp)
        return 0;

    if (*tmp == stop_char) {
        *input = ++tmp;
        return 0;
    }

    // Extract next integer and characters read
    int64_t next = 0, pos = 0;
    if (sscanf(tmp, "%lld%n", &next, &pos) != 1)
        return 0;

    // Successful extraction
    // Update input for further extraction
    *input = tmp + pos;
    return next;
}
