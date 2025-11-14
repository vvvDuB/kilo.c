#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main(void) {
    char c;
    /* This while keep read from the stdin and print the char */
    while (read(STDIN_FILENO, &c, 1) == 1) {
        if (c != '\n')
            printf("Char: %c\n", c);
    }
    return 0;
}
