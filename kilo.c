#include <stdio.h>
#include <unistd.h>
#include <termios.h>

void enableRawMode() {
    // raw struct
    struct termios raw;
    
    // the ECHO feature give what you type on terminal, we dont want it 
    tcgetattr(STDIN_FILENO, &raw);
    // This c_lflag is a bit mask and 'ECHO' will be a specific 1, when ~(1)
    // will be 0, turning off the ECHO feature, like '11110111' 0 is ECHO
    raw.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// TODO: Reset the ECHO, type 'reset' if the terminal is broken 

int main(void) {
    // Now the stdin input is hidden
    enableRawMode();
    
    // This while keep read from the stdin and p:wqrint the char quit the program at a 'q' char but
    // every char after the 'q' will be echoed to bash
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    return 0;
}
