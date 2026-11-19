#include "kernel.h"

void kmain(void)
{
    // clear();            // you'll write clear() — fills screen with blanks
    // print_banner();

    // putstr("Hello from my kernel\n");
    // putchar('\n');

    // char *msg = "What's up bruv!?";
    // putstr(msg);

    // putchar('\n');
    // putchar('\n');
    // putchar('\n');
    // putchar('\n');
    // unsigned int len = strlen(msg);
    // putstr("the length of my message is => ");
    // putnbr(len);
    clear();
    print_banner();
    putstr("\n  Welcome to Yel-bouk & Nihamila's kernel. Booting complete.\n");
    putchar('\n');
    putchar('\n');
    putstr("42\n");
}

