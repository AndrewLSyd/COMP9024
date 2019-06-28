// read text from std input and writes a list of the distinct word that appear
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAXWORDS 1000
#define INPUT "Mary had a Little Lamb, Little Lamb"

char input[MAXWORDS][11];  // 2D array: 1000 x (10 + 1) characters
char next[11];

int main(void){
    int word_counter = 0;
    char * p;

    while (scanf("%s", next) == 1){  // while there is still input
        printf("\nprocessing in %s", next);
        p = next;  // setting pointer to start of array
        // loading in word char by char
        int j = 0;
        while (*p){
            if (j > 9){  // if the word is longer than 9 char, dump into next word
                input[word_counter][j] = '\0';
                printf(", just loaded in %s", input[word_counter]);
                word_counter += 1;
                j = 0;
            }
            input[word_counter][j] = *p;
            p += 1;
            j += 1;
        }
        input[word_counter][j] = '\0';
        printf(", just loaded in %s", input[word_counter]);
        word_counter += 1;
    }

    puts("\nWORDS LOADED:\n");
    int word;
    for (word = 0; word < word_counter; word ++){
        printf("Word #%d is \"%s\"\n", word, input[word]);
    }
    return EXIT_SUCCESS;
}

