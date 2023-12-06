#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief This struct groups whats define a part
struct number {
    int number;          /// Position in the schematic
    struct number *next; /// next part in a list
};

/**
 * \brief Intersection of the two input lists
 */
int intersect(struct number *list_1, struct number *list_2);

/**
 * \brief Extracts all numbers from the input - pushing back to the list
 */
int extract_numbers(char **buffer, struct number **list);

/**
 * \brief Display all parts from list
 */
void display(struct number *list, char *title);

/**
 * \brief Delete all number from a list
 */
int delete (struct number *list);

/**
 * \brief Get the next integer from the input up to the stop character or end of
 * \details This is modifying the input in-place
 *
 * \returns 0 if no integer is found (input is consumed)
 * \returns integer found
 */
int next_integer_from_input(char **input, char stop_char);

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

    // Initialize lists of winning and "yours" numbers
    struct number list_winning = {
        .number = 0,
        .next   = NULL,
    };
    struct number list_numbers = {
        .number = 0,
        .next   = NULL,
    };

    // Part 2 - map index/match/scratchcards
    int matches[250]      = {};
    int scratchcards[250] = {};

    // Read schematic line by line
    int sum_of_points = 0;
    int card_id       = 0;
    while (fgets(buffer, buffer_length, file_pointer)) {
        struct number *current_last_winning = &list_winning;
        struct number *current_last_number  = &list_numbers;
        int card_points                     = 0;

        // 1. Extract winning numbers and your numbers
        char *current_pos = buffer;
        card_id           = next_integer_from_input(&current_pos, ':'); // extract card id
        extract_numbers(&current_pos, &current_last_winning);
        extract_numbers(&current_pos, &current_last_number);

#if BUILD_FOR_PART_1
        // Make a nice debug output
        display(list_winning.next, "Winning numbers");
        display(list_numbers.next, "Your numbers");
#endif
        // 2. Intersect the two lists
        int match   = intersect(list_winning.next, list_numbers.next);
        card_points = (match > 0) ? (1 << (match - 1)) : 0;
#if BUILD_FOR_PART_1
        // no new line accounting for \n in the input
        printf("%s -> %d matche(s) -> %d points \n", buffer, match, card_points);
#endif
        sum_of_points += card_points;

        // Store id/match
        matches[card_id]      = match;
        scratchcards[card_id] = 1;

        // Free all numbers
        delete (list_winning.next);
        delete (list_numbers.next);
    }

#if BUILD_FOR_PART_1
    // Print the output value
    printf("Sum of points for all: %d\n", sum_of_points);
#else
    int sum_of_scratchcards = 0;
    // Traverse all scratchcards from 1 -> last card
    for (int i = 1; i <= card_id; i++) {
        printf("%d id -> %d sc\n", i, scratchcards[i]);
        sum_of_scratchcards += scratchcards[i];
        // For each subsequent scratchcard according to matches at index i
        for (int j = 1; j <= matches[i]; j++) {
            // Add "1" per scratchcard (original + copies) at index i
            scratchcards[i + j] += scratchcards[i];
        }
    }

    // Print the output value
    printf("Total number of scratchcards: %d\n", sum_of_scratchcards);
#endif

    fclose(file_pointer);
    return 0;
}

int intersect(struct number *list_1, struct number *list_2) {
    struct number *cur_number_l1 = list_1;
    int match                    = 0;

    while (cur_number_l1) {
        struct number *cur_number_l2 = list_2;
        while (cur_number_l2) {
            if (cur_number_l1->number == cur_number_l2->number) {
                match++;
                break;
            }
            cur_number_l2 = cur_number_l2->next;
        }
        cur_number_l1 = cur_number_l1->next;
    }
    return match;
}

int extract_numbers(char **buffer, struct number **list_parts) {
    struct number *list = *list_parts;
    char *current_pos   = *buffer;

    while (1) {
        int number = next_integer_from_input(&current_pos, '|');
        if (number == 0)
            break; // no more part number

        // Initialize a new part
        struct number *new_number = malloc(sizeof(struct number));
        new_number->number        = number;
        new_number->next          = NULL;

        // Append it to the list
        list->next = new_number;
        list       = new_number;
    }

    // Update input list with new end
    *list_parts = list;
    *buffer     = current_pos;
    return 0;
}

void display(struct number *list, char *title) {
    printf("%s:\n", title);
    while (list) {
        printf("number:%d\n", list->number);
        list = list->next;
    }
    printf("\n");
}

int delete (struct number *list) {
    if (!list)
        return 0;

    delete (list->next);
    free(list);
    return 0;
}

int next_integer_from_input(char **input, char stop_char) {
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
    int next = 0, pos = 0;
    if (sscanf(tmp, "%d%n", &next, &pos) != 1)
        return 0;

    // Successful extraction
    // Update input for further extraction
    *input = tmp + pos;
    return next;
}
