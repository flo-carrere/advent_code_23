#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief This struct groups whats define a part
struct part {
    int x, y;          /// Position in the schematic
    int width;         /// Length in a schematic along the x-axis - number of digits also ;-)
    int number;        /// Part number
    struct part *next; /// next part in a list
};

/// @brief This struct groups whats define a symbol
struct symbol {
    int x, y;            /// Position in the schematic
    char value;          /// character of the symbol
    struct symbol *next; /// next symbol in a list
};

/**
 * \brief Determine the sum of adjacent part numbers of a given list of parts towards a list of symbols
 * \returns The sum of part numbers
 */
int determine_adjacency(struct part *list_parts, struct symbol *list_symbols);

/**
 * \brief Determine the sum of gear ratios of a given list of parts towards a list of symbols
 * \returns The sum of gear ratios
 */
int determine_gear_ratios(struct part *list_parts, struct symbol *list_symbols);

/**
 * \brief Determine whether a given part is adjacent to a symbol
 * \returns true if adjacent, false otherwise
 */
bool is_part_adjacent_to_symbol(struct part *part, struct symbol *symbol);

/**
 * \brief Extracts all part from the input - pushing back to the list
 */
int extract_parts(char *buffer, int y, struct part **list_parts);

/**
 * \brief Display all parts from list
 */
void display_parts(struct part *list) {
#if DISPLAY_PARTS
    printf("All parts:\n");
    while (list) {
        printf("number:%d, pos:%d, %d, width:%d\n", list->number, list->x, list->y, list->width);
        list = list->next;
    }
    printf("\n");
#endif // DISPLAY_PARTS
}

/**
 * \brief Delete all parts from list
 */
int delete_parts(struct part *list);

/**
 * \brief Extracts all symbols from the input - pushing back to the list
 */
int extract_symbols(char *buffer, int y, struct symbol **list_symbols);

/**
 * \brief Display all symbols from list
 */
void display_symbols(struct symbol *list) {
#if DISPLAY_SYMBOLS
    printf("All symbols:\n");
    while (list) {
        printf("value:%c, pos:%d, %d\n", list->value, list->x, list->y);
        list = list->next;
    }
    printf("\n");
#endif // DISPLAY_SYMBOLS
}

/**
 * \brief Delete all symbols from list
 */
int delete_symbols(struct symbol *list);

/**
 * \brief Get the next integer from the input
 * \details This is modifying the input in-place
 *
 * \returns 0 if no integer is found (input is consumed)
 * \returns integer found
 */
int next_integer_from_input(char **input, int *num_digits);

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

    // Initialize lists of parts and symbols with invalid first elements
    struct part list_parts = {
        .number = 0,
        .next   = NULL,
    };
    struct symbol list_symbols = {
        .value = '.',
        .next  = NULL,
    };
    struct part *current_last_part     = &list_parts;
    struct symbol *current_last_symbol = &list_symbols;

    // Read schematic line by line
    int line = -1;
    while (fgets(buffer, buffer_length, file_pointer)) {
        line++;

#if DISPLAY_SCHEMATIC
        // no new line accounting for \n in the input
        printf("%s", buffer);
#endif // DISPLAY_SCHEMATIC

        // 1. Extract part and symbols
        extract_parts(buffer, line, &current_last_part);
        extract_symbols(buffer, line, &current_last_symbol);
    }
#if DISPLAY_SCHEMATIC
    printf("\n");
#endif // DISPLAY_SCHEMATIC

    // Make a nice debug output
    display_parts(list_parts.next);
    display_symbols(list_symbols.next);

#if BUILD_FOR_PART_1
    // 2. Determine adjencency of parts vs symbols -> (real) parts
    int sum_part_numbers = determine_adjacency(list_parts.next, list_symbols.next);
    // Print the output value
    printf("Sum of all the part numbers in the schematic: %d\n", sum_part_numbers);
#else
    // 2. Determine gear ratios by looking at * adjacent to parts
    int sum_gear_ratios = determine_gear_ratios(list_parts.next, list_symbols.next);
    // Print the output value
    printf("Sum of all the gear ratios in the schematic: %d\n", sum_gear_ratios);
#endif

    // Free all parts and symbols
    delete_parts(list_parts.next);
    delete_symbols(list_symbols.next);

    fclose(file_pointer);
    return 0;
}

int determine_adjacency(struct part *list_parts, struct symbol *list_symbols) {
    int sum_of_parts_in_schematic = 0;
    struct part *current_part     = list_parts;

    // For each part
    while (current_part) {
        // Initialise to first symbol again
        struct symbol *current_symbol = list_symbols;
        // For each symbol
        while (current_symbol) {
            if (current_symbol->y > (current_part->y + 1))
                break; // There will be no other adjacent symbol, as there are sorted by line

            if (is_part_adjacent_to_symbol(current_part, current_symbol)) {
                printf("%d -> %c\n", current_part->number, current_symbol->value);
                sum_of_parts_in_schematic += current_part->number;
                break;
            }
            // Inspect next symbol
            current_symbol = current_symbol->next;
        }
        // Inspect next part
        current_part = current_part->next;
    }

    return sum_of_parts_in_schematic;
}

int determine_gear_ratios(struct part *list_parts, struct symbol *list_symbols) {
    int sum_of_gear_ratios        = 0;
    struct symbol *current_symbol = list_symbols;

    // For each symbol
    while (current_symbol) {
        if (current_symbol->value != '*') {
            // Skip this as not relevant
            current_symbol = current_symbol->next;
            continue;
        }

        // Initialise to first part again
        struct part *current_part = list_parts;
        int gear_ratio            = 1;
        int adjacent_part         = 0;

        // For each part
        while (current_part && (adjacent_part <= 2)) {
            if (is_part_adjacent_to_symbol(current_part, current_symbol)) {
                adjacent_part++;
                gear_ratio *= current_part->number;
                printf("* -> %d\n", current_part->number);
            }
            // Inspect next symbol
            current_part = current_part->next;
        }

        // If not exactly two adjacent part, just clear the gear_ratio
        if (adjacent_part != 2)
            gear_ratio = 0;

        sum_of_gear_ratios += gear_ratio;
        // Inspect next symbol
        current_symbol = current_symbol->next;
    }

    return sum_of_gear_ratios;
}

bool is_part_adjacent_to_symbol(struct part *part, struct symbol *symbol) {
    // is symbol in part bounding box (-1/+1 along x/y axis)?
    if ((symbol->x >= (part->x - 1)) && (symbol->x <= (part->x + part->width)) && (symbol->y >= (part->y - 1)) &&
        (symbol->y <= (part->y + 1)))
        return true;
    return false;
}

int extract_parts(char *buffer, int y, struct part **list_parts) {
    struct part *list = *list_parts;
    char *current_pos = buffer;

    while (1) {
        int x           = buffer - current_pos;
        int num_digits  = 0;
        int part_number = next_integer_from_input(&current_pos, &num_digits);
        if (part_number == 0)
            break; // no more part number

        // Initialize a new part
        struct part *new_part = malloc(sizeof(struct part));
        new_part->number      = part_number;
        new_part->x           = (current_pos - buffer - num_digits);
        new_part->y           = y;
        new_part->width       = num_digits;
        new_part->next        = NULL;

        // Append it to the list
        list->next = new_part;
        list       = new_part;
    }

    // Update input list with new end
    *list_parts = list;
    return 0;
}

int delete_parts(struct part *list) {
    if (!list)
        return 0;

    delete_parts(list->next);
    free(list);
    return 0;
}

int extract_symbols(char *buffer, int y, struct symbol **list_symbols) {
    struct symbol *list = *list_symbols;
    char *current_pos   = buffer;

    while (*current_pos) {
        // Consume input while we find digit or .
        while ((isdigit(*current_pos) || (*current_pos == '.')))
            current_pos++;

        if (*current_pos == '\n')
            break;

        // Initialize a new symbol
        struct symbol *new_symbol = malloc(sizeof(struct symbol));
        new_symbol->value         = *current_pos;
        new_symbol->x             = (current_pos - buffer);
        new_symbol->y             = y;
        new_symbol->next          = NULL;

        // Append it to the list
        list->next = new_symbol;
        list       = new_symbol;

        current_pos++;
    }

    // Update input list with new end
    *list_symbols = list;
    return 0;
}

int delete_symbols(struct symbol *list) {
    if (!list)
        return 0;

    delete_symbols(list->next);
    free(list);
    return 0;
}

int next_integer_from_input(char **input, int *num_digits) {
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
    *input      = tmp + pos;
    *num_digits = pos;
    return next;
}
