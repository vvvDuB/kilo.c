#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

struct termios orig_termios;

// Reset the ECHO or type 'reset' if the terminal is broken 
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); 
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode); // Call after quit with 'q'
    
    struct termios raw = orig_termios;
    
    // the ECHO feature give what you type on terminal, we dont want it 
    // This c_lflag is a bit mask and 'ECHO' will be a specific 1, when ~(1)
    // will be 0, turning off the ECHO feature, like '11110111' 0 is ECHO
    // this is a bitwise-NOT so: 00001000 -> 11110111 
    raw.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main(void) {
    // Now the stdin input is hidden
    enableRawMode();
    
    // This while keep read from the stdin and p:wqrint the char quit the program at a 'q' char but
    // every char after the 'q' will be echoed to bash
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    return 0;
}
