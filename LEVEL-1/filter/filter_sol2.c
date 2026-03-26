#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Outputs a '*' for every character in the target string's length.
 */
void replace_with_asterisks(size_t length) {
    for (size_t i = 0; i < length; i++) {
        putchar('*');
    }
}

/**
 * Shifts the buffer to the left by one character.
 * Used when the current sequence cannot form a complete match.
 */
void shift_buffer_left(char *buffer, size_t *current_len) {
    if (*current_len > 0) {
        for (size_t i = 1; i < *current_len; i++) {
            buffer[i - 1] = buffer[i];
        }
        (*current_len)--;
    }
}

/**
 * Handles the logic of comparing the current buffer against the target string.
 * It identifies partial matches and flushes characters that definitely won't match.
 */
void process_input_stream(const char *target_string) {
    size_t target_len = strlen(target_string);
    char *match_buffer = malloc(target_len + 1);
    
    if (!match_buffer) {
        perror("Error");
        exit(1);
    }

    size_t active_len = 0;
    char current_char;
    ssize_t bytes_read;

    while ((bytes_read = read(STDIN_FILENO, &current_char, 1)) > 0) {
        match_buffer[active_len++] = current_char;

        // Check if the current buffer is still a prefix of the target
        if (strncmp(match_buffer, target_string, active_len) == 0) {
            // Full match found
            if (active_len == target_len) {
                replace_with_asterisks(target_len);
                active_len = 0;
            }
        } else {
            // Mismatch: The first char of the buffer is definitely not part of a match
            putchar(match_buffer[0]);
            shift_buffer_left(match_buffer, &active_len);

            // Keep flushing and shifting until the buffer matches the start of target or is empty
            while (active_len > 0 && strncmp(match_buffer, target_string, active_len) != 0) {
                putchar(match_buffer[0]);
                shift_buffer_left(match_buffer, &active_len);
            }
        }
    }

    if (bytes_read == -1) {
        perror("Error");
        free(match_buffer);
        exit(1);
    }

    // Flush any remaining partial match at End of File
    for (size_t i = 0; i < active_len; i++) {
        putchar(match_buffer[i]);
    }

    free(match_buffer);
}

int main(int argc, char **argv) {
    // Requirements: Exactly one argument, and it must not be empty.
    if (argc != 2 || argv[1][0] == '\0') {
        return 1;
    }

    process_input_stream(argv[1]);

    return 0;
}