#include "kernel.h"

void putstr(const char *s)
{
    while (*s)
        putchar(*s++);
}
void clear(void)
{
    unsigned char *vga = (unsigned char *)0xB8000;   // byte pointer

    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga[i * 2]     = ' ';      // character byte
        vga[i * 2 + 1] = COLOR;    // color byte
    }
    vga_pos = 0;
}

void putchar(char c)
{
    unsigned char *vga = (unsigned char *)0xB8000;

    if (c == '\n') {
        vga_pos = (vga_pos / VGA_WIDTH + 1) * VGA_WIDTH;   // jump to next line
    } else {
        vga[vga_pos * 2]     = c;       // character byte
        vga[vga_pos * 2 + 1] = COLOR;   // color byte
        vga_pos++;
    }
}

unsigned int    strlen(const char *s)
{
    unsigned int len = 0;
    while (s[len])
        len++;
    return len;
}

int          strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	*memset(void *ptr, int value, unsigned int num)
{
	unsigned int	i;
	char	*str;

	i = 0;
	str = (char *)ptr;
	while (i < num)
	{
		str[i] = (char)value;
		i++;
	}
	return (str);
}

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	ft_strncmp(const char *str1, const char *str2, unsigned int num)
{
	unsigned int	i;

	i = 0;
	while (str1[i] && str2[i] && i < num)
	{
		if ((unsigned char)str1[i] != (unsigned char)str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	if (i < num)
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	return (0);
}

void putnbr(int n)
{
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n >= 10)
        putnbr(n / 10);      // print all but the last digit FIRST
    putchar('0' + n % 10);   // then print the last digit
}
void print_banner(void)
{
    putstr("================================================================\n");
    putstr(" __   __ _____ _          ____   ___  _   _ _  __\n");
    putstr(" \\ \\ / /| ____| |        | __ ) / _ \\| | | | |/ /\n");
    putstr("  \\ V / |  _| | |   _____ |  _ \\| | | | | | | ' / \n");
    putstr("   | |  | |___| |__|_____|| |_) | |_| | |_| | . \\ \n");
    putstr("   |_|  |_____|_____|     |____/ \\___/ \\___/|_|\\_\\\n");
    putstr("================================================================\n");
    putstr("             42 - Kernel From Scratch (KFS_1)\n");
    putstr("================================================================\n");
}
