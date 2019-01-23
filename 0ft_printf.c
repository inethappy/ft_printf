#include "ft_printf.h"

//gcc ft_printf.c ft_putchar.c ft_putstr.c ft_putnbr.c

int ft_printf(const char *format, ...)
{
    char d;
    va_list ap;
    va_start(ap, format);
    while (*format)
    {
        if (*format == '%')
        {
            format++;
            d = va_arg(ap, int);
            ft_putchar(d);
            format++;
        } 
        ft_putchar(*format);
        format++;
    }
    va_end(ap);
    return 0;
}

int main()
{
    // int b;
    // b = 3400000;
    char b;
    b = 'b';
    int g;
    g = -666;
   // printf("printf: %s, %d\n", b, g); 
    //printf( "%0*X", 15 , 1);
    ft_printf("ft_printf: %c\n", b);
    return 0;
}