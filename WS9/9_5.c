#include <stdio.h>
#include <string.h>

int main() {
    char input_string[100];

    while (1) {
        printf("Enter input string:\n");
        fgets(input_string, sizeof(input_string), stdin);
        input_string[strcspn(input_string, "\n")] = '\0'; // Remove the newline character

        if (strcmp(input_string, "q") == 0) {
            break;
        }

        if (strchr(input_string, ',') == NULL) {
            printf("Error: No comma in string.\n\n");
            continue;
        }

        char *first_word = strtok(input_string, ",");
        char *second_word = strtok(NULL, ",");
        
        if (first_word != NULL && second_word != NULL) {
            // Remove leading and trailing spaces
            while (*first_word == ' ') {
                first_word++;
            }
            int len = strlen(first_word);
            while (len > 0 && first_word[len - 1] == ' ') {
                first_word[len - 1] = '\0';
                len--;
            }
            
            while (*second_word == ' ') {
                second_word++;
            }
            len = strlen(second_word);
            while (len > 0 && second_word[len - 1] == ' ') {
                second_word[len - 1] = '\0';
                len--;
            }

            printf("First word: %s\n", first_word);
            printf("Second word: %s\n\n", second_word);
        }
    }

    return 0;
}
