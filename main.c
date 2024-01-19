#include <ncurses.h>
#include <stdio.h>
#include "bin_to_hex.h"

int main() {
    char* filename = "file.txt";

    FILE* file = fopen(filename, "r");

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char file_content[file_size];

    size_t real_readed = 0;
    if ((real_readed = fread(file_content, 1, file_size, file)) != file_size) {
        fprintf(stderr, "Readed (%lu) != expected (%lu)\n", real_readed, file_size);
        return 1;
    }
    
    initscr();

    //for (size_t ind = 0; ind < file_size; ++ind) {
    //}
    warr_to_hex(stdscr, file_content, file_size);
    getch();

    endwin();

    return 0;
}
