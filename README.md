show_ascii.c:
This program  makes some manipulations to the terminal to instantly read characters and type the corresponding ASCII value.
The main library is <termios.h> that allows the user to change terminal settings.I have set ECHO and ICANON flags to 0,which allowed me to:
Not print the characters to the terminal when I input them(ECHO flag=0) and to not wait for enter to be pressed to read the input (ICANON flag=0).
Then i have used printf() to show the inputed character as ECHO was set to 0 so without it,the characters would be read to c but you won't see anything

kilo.c:
A small project that follows the tutorial from https://viewsourcecode.org/snaptoken/kilo.It has a lot of features right now(v0.0.1),some of which are taken from show_ascii.c
For now(v0.0.1) it displays a welcome message and tildas,that adjust based on the terminal size.A string buffer was used to reduce flickering,and each iteration,only the line we are on,updates,
this also reduces flickering.Also made the cursor disappear before each screen update,and appear after the update,this also fixed the cursor appearing in the middle of the screen.
