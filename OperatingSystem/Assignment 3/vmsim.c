#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int algorithm_flag = 0, frames_flag = 0, file_flag = 0; //Booleans for checking flags
    int mode = 0; //Mode will be 1 for FIFO, 2 for Optimal, 3 for Lru
    int frames = 0;
    FILE *infile = NULL;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'a' && !algorithm_flag) {
                if (strcmp(argv[++i], "fifo") == 0) {
                    mode = 1;
                } else if (strcmp(argv[i], "optimal") == 0) {
                    mode = 2;
                } else if (strcmp(argv[i], "lru") == 0) {
                    mode = 3;
                } else {
                    printf("Entered an incorrect algorithm\nThe available options are fifo, optimal or lru\n");
                    return 1;                
                }
                algorithm_flag = 1;
            } else if (argv[i][1] == 'n' && !frames_flag) {
                if (atoi(argv[++i]) != 0) {
                    frames = atoi(argv[i]);
                } else {
                    printf("Incorrect amount of frames\nPlease enter an integer\n");
                    return 1;
                }
                frames_flag = 1;
            } else if (argv[i][1] == 'f' && !file_flag) {
                infile = fopen(argv[++i], "r");
                if (infile) {
                    file_flag = 1;
                } else {
                    printf("Error opening specified file\nPlease make sure the file exists\n");
                    return 1;
                }
            } else {
                printf("Entered an incorrect flagn\nThe available options are -a, -n, -f\n");
                return 1;
            }
        }
    }
    return 0;
}
