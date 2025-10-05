#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define BUF_SIZE 1024

bool is_vowel(char c) {
    char lower_c = tolower((unsigned char)c);
    return (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' ||
            lower_c == 'o' || lower_c == 'u');
}

int copy_non_vowels(size_t num_chars, char* in_buf, char* out_buf) {
    int out_index = 0;
    for (size_t i = 0; i < num_chars; i++) {
        if (!is_vowel(in_buf[i])) {
            out_buf[out_index++] = in_buf[i];
        }
    }
    return out_index;
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
    char in_buf[BUF_SIZE];
    char out_buf[BUF_SIZE];

    while (fgets(in_buf, BUF_SIZE, inputFile)) {
        size_t chars_read = strlen(in_buf);
        int chars_written = copy_non_vowels(chars_read, in_buf, out_buf);

        if (chars_written > 0) {
            if (fwrite(out_buf, sizeof(char), chars_written, outputFile) != chars_written) {
                fprintf(stderr, "Error writing to output file.\n");
                break;
            }
        }
    }

    if (ferror(inputFile)) {
        fprintf(stderr, "Error reading from input file.\n");
    }
}

int main(int argc, char *argv[]) {
    FILE *inputFile = stdin;
    FILE *outputFile = stdout;

    if (argc > 3) {
        fprintf(stderr, "Usage: %s [input_file] [output_file]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc >= 2) {
        inputFile = fopen(argv[1], "r");
        if (inputFile == NULL) {
            fprintf(stderr, "Error: Could not open input file %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    if (argc == 3) {
        outputFile = fopen(argv[2], "w");
        if (outputFile == NULL) {
            fprintf(stderr, "Error: Could not open output file %s\n", argv[2]);
            if (inputFile != stdin) fclose(inputFile);
            return EXIT_FAILURE;
        }
    }

    if (argc == 1) {
        fprintf(stderr, "Reading from stdin and writing to stdout. Use Ctrl+D to end input.\n");
    }

    disemvowel(inputFile, outputFile);

    if (inputFile != stdin) fclose(inputFile);
    if (outputFile != stdout) fclose(outputFile);

    return EXIT_SUCCESS;
}