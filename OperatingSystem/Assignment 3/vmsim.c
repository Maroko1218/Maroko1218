#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    char *algorithm, *frames, 
    
    
    if (argc != 7 || argc % 2 == 0) {
        printf("You entered an incorrect amount of flags\n");
        return 1;
    }
    for (size_t i = 0; i < argc; i++) {
        if (argv[i][0] != '-') {
            printf("You entered an incorrect flag\n");
            return 1;
        }
        if (!strcmp(argv[i], "-a")) {
            
        }
    }
}
