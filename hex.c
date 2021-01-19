#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    
    if (argc != 2) {
        printf("Usage: dump <file>\n");
        return 0;
    }
    FILE *file = fopen(argv[1], "rb");

    if (file == NULL) {
        printf("Error opening %s\n", argv[1]);
        return 1;
    }
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    rewind(file);
    unsigned char *chunk = malloc(16);
    int offset = 0;
    while (fread(chunk, 1, 16, file)){
        printf("%08x  ", offset);
        offset+=16;
        int i;
        for (i = 0; i < 8 && offset + i <= length + 15; i++) {
            printf("%02x ", chunk[i]);
        }
        printf(" ");
        for (; i < 16 && offset + i <= length + 15; i++) {
           printf("%02x ", chunk[i]);
        }
        for (int j = 0; j < 16 - i; i++) {
            printf("   ");
        } 
        printf(" |");
        for (int i = 0; i < 16 && offset + i <= length + 15; i++) {
            if (chunk[i] < 127 && chunk[i] > 31) {
                printf("%c", chunk[i]);
            }
            else {
                printf(".");
            }
        }
        printf("|");
        printf("\n");
    }

    printf("%08x\n", length);
}
