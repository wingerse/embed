#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void print_usage(void)
{
    printf("Usage: embed [-h] <input>\n");
}

int main(int argc, char **argv) {
    char *input_name;
    bool header = false;
    if (argc == 2) {
        input_name = argv[1];
        input_name = argv[1];
    } else if (argc == 3) {
        if (strcmp(argv[1], "-h") != 0) {
            print_usage();
            exit(EXIT_FAILURE);
        }
        header = true;
        input_name = argv[2];
    } else {
        print_usage();
        exit(EXIT_FAILURE);
    }

    FILE *input = fopen(input_name, "rb");
    if (!input) {
        exit(EXIT_FAILURE);
    }
    fseek(input, 0, SEEK_END);
    long input_size = ftell(input);
    fseek(input, 0, SEEK_SET);

    char *c_name = strdup(input_name);
    size_t c_name_len = strlen(c_name);
    for (size_t i = 0; i < c_name_len; i++) {
        if (!isalnum(c_name[i])) {
            c_name[i] = '_';
        }
    }

    if (header) {
        printf("extern unsigned char %s[%ld];", c_name, input_size);
    } else {
        printf("unsigned char %s[%ld] = {\n", c_name, input_size);
        int c;
        int count = 0;
        printf("    ");
        while ((c = fgetc(input)) != EOF) {
            printf("0x%.2x, ", c);
            count++;
            if (count == 22) {
                printf("\n");
                printf("    ");
                count = 0;
            }
        }
        printf("\n};\n");
    }

    fclose(input);
    return 0;
}
