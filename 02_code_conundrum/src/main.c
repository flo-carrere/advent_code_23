#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief Handy structure to store cube limits
 */
struct limits_s {
    int red;
    int green;
    int blue;
};

/**
 * \brief Returns whether the game is possible based on cube limits
 * \returns ID (>0) of the game if it is possible
 * \returns 0 if it is impossible
 */
int is_game_possible(char *input, struct limits_s *limits);

/**
 * \brief Returns the minimum power of a set for the given game
 */
int minimum_power_of_set(char *input, struct limits_s *limits);

/**
 * \brief Get the next integer from the input
 * \details This is modifying the input in-place
 *
 * \returns 0 if no integer is found (input is consumed)
 * \returns integer found
 */
int next_integer_from_input(char **input);

/**
 * \brief Get the color limit for a given color
 * \returns color limit or 0 if invalid
 */
int get_color_limit(char color, struct limits_s *limits);

/**
 * \brief Set the color limit for a given color
 * \returns 0 if successfully update, -1 otherwise
 */
int set_color_limit(int new_limit, char color, struct limits_s *limits);

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

#if CHECK_PART == 1
    // Initialized with hard limits
    struct limits_s limits = {
        .red   = 12,
        .green = 13,
        .blue  = 14,
    };

    // Read line by line
    int sum_ids_game = 0;
    while (fgets(buffer, buffer_length, file_pointer)) {
        int id = is_game_possible(buffer, &limits);
        printf("%s -> %d\n", buffer, id);
        sum_ids_game += id;
    }

    // Print the output value
    printf("Sum of IDs of possible games: %d\n", sum_ids_game);
#elif CHECK_PART == 2
    // Read line by line
    int sum_power_of_sets = 0;
    while (fgets(buffer, buffer_length, file_pointer)) {
        // Initialized with minimum amounts (empty)
        struct limits_s limits = {
            .red   = 0,
            .green = 0,
            .blue  = 0,
        };

        int power = minimum_power_of_set(buffer, &limits);
        printf("%s -> %d\n", buffer, power);
        sum_power_of_sets += power;
    }

    // Print the output value
    printf("Sum of the power of the sets: %d\n", sum_power_of_sets);
#endif

    fclose(file_pointer);
    return 0;
}

int is_game_possible(char *input, struct limits_s *limits) {
    size_t input_length = strlen(input) - 1; // excluding \n from the input
    // Extract info from the input
    int id = next_integer_from_input(&input);

    while (*input) {
        // Extract next cube count
        int cube_count = next_integer_from_input(&input);

        if (cube_count == 0)
            break; // Should exit from here normally

        // Extract color
        char cube_color = input[1]; // either r,g,b
        printf("%d %c ", cube_count, cube_color);

        // Check limits according to the color
        int current_color_limit = get_color_limit(cube_color, limits);
        if (cube_count > current_color_limit) {
            printf("-> Impossible\n");
            return 0;
        }
        printf("\n");
    }
    return id;
}

int minimum_power_of_set(char *input, struct limits_s *limits) {
    size_t input_length = strlen(input) - 1; // excluding \n from the input
    // Extract info from the input
    int id = next_integer_from_input(&input);

    while (*input) {
        // Extract next cube count
        int cube_count = next_integer_from_input(&input);

        if (cube_count == 0)
            break; // Should exit from here normally

        // Extract color
        char cube_color = input[1]; // either r,g,b

        int current_color_limit = get_color_limit(cube_color, limits);
        // There is no checks only "limits" to update if needed
        set_color_limit(max(cube_count, current_color_limit), cube_color, limits);
    }

    // Return the power of this set
    printf("%d %d %d\n", limits->red, limits->green, limits->blue);
    return limits->red * limits->green * limits->blue;
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

int get_color_limit(char color, struct limits_s *limits) {
    switch (color) {
    case 'r':
        return limits->red;
    case 'g':
        return limits->green;
    case 'b':
        return limits->blue;
    default:
        return 0;
    }
    return 0;
}

int set_color_limit(int new_limit, char color, struct limits_s *limits) {
    switch (color) {
    case 'r':
        limits->red = new_limit;
        break;
    case 'g':
        limits->green = new_limit;
        break;
    case 'b':
        limits->blue = new_limit;
    default:
        return -1;
    }
    return 0;
}
