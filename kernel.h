#ifndef KERNEL_H
#define KERNEL_H
#define VGA ((unsigned short *)0xB8000)
#define COLOR 0x07
static unsigned int vga_pos = 0;   // persists between calls

typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;

unsigned int strlen(const char *s);
int          strcmp(const char *a, const char *b);
void	*memset(void *ptr, int value, unsigned int num);
int	ft_isalpha(int c);
int	ft_strncmp(const char *str1, const char *str2, unsigned int num);
void putnbr(int n);
void putchar(char c);
void print_banner(void);
void putstr(const char *s);
void clear(void);

#endif