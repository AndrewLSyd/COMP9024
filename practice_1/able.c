// Write a C-program that outputs, in alphabetical order, all strings that use each of the characters
// 'a', 'b', 'l', 'e' exactly once.

// How many strings are there actually? 

// create array that indicates whether each letter has been used - this array is in alpha order

#include <stdio.h>
#include <stdlib.h>

char letters[5] = {'a', 'b', 'e', 'l', '\0'};
int used_letters[] = {0, 0, 0, 0};
int let_1, let_2, let_3, let_4, i;

int main(void){
    for (let_1=0; let_1 < 4; let_1 ++){  // first letter
        // reseting things
        char out[5];
        // char used_letters[] = {0, 0, 0, 0, 0};
        out[0] = letters[let_1];
        // printf("%s, ", out);
        for (let_2=0; let_2 < 4; let_2 ++){  // second letter
            out[1] = letters[let_2];
            // printf("%s, ", out);
            for (let_3=0; let_3 < 4; let_3 ++){  // third letter
                out[2] = letters[let_3];
                // printf("%s, ", out);
                for (let_4=0; let_4 < 4; let_4 ++){  // fourth letter
                    out[3] = letters[let_4];
                    // printf("%s, ", out);
                    // needs ONE of every character to be unique!
                    for (i=0; i < 4; i ++){
                        // printf(" comparing %s ", out[i]);
                        if (out[i] == (int) 'a'){used_letters[0] += 1;}
                        if (out[i] == (int) 'b'){used_letters[1] += 1;}
                        if (out[i] == (int) 'e'){used_letters[2] += 1;}
                        if (out[i] == (int) 'l'){used_letters[3] += 1;}
                    }
                    // printf(" used letters %d %d %d %d ", used_letters[0], used_letters[1], used_letters[2], used_letters[3]);
                    if(used_letters[0] == 1 && used_letters[1] == 1 && used_letters[2] == 1 && used_letters[3] == 1){
                        printf("%s, ", out);
                    }
                }
            }
        }
    }
    return EXIT_SUCCESS;
}