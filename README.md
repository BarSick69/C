show_ascii.c:
This program  makes some manipulations to the terminal to instantly read characters and type the corresponding ASCII value.
The main library is <termios.h> that allows the user to change terminal settings.I have set ECHO and ICANON flags to 0,which allowed me to:
Not print the characters to the terminal when I input them(ECHO flag=0) and to not wait for enter to be pressed to read the input (ICANON flag=0).
Then i have used printf() to show the inputed character as ECHO was set to 0 so without it,the characters would be read to c but you won't see anything
