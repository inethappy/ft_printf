#include "ft_printf.h"

//gcc ft_printf.c ft_putchar.c ft_putstr.c ft_putnbr.c

void ft_parsing(const char *fmt)
{
    while (*fmt)
    {
        if (*fmt == '#' || *fmt == '0' || *fmt == ' ' || *fmt = '+')
            ft_flags_handling(*fmt);
        else if (*fmt == 'h' || *fmt == 'l')
            ft_wight_handling(*fmt);
        else
        {}
        fmt++;
    }
}

int ft_printf_d(const char *format, ...)
{
    int d = 0;
    va_list ap;
    va_start(ap, format);
    while (*format)
    {
        if (*format == '%')
        {
            ft_parsing(format + 1);
            format++;
            d = va_arg(ap, int);
            ft_putnbr(d);
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
    char *b;
    b = "asdas";
    int g;
    g = -666;
    printf("printf: %s, %d\n", b, g); 
    printf( "%0*X", 15 , 1);
    ft_printf_d("ft_printf: %d, %d\n", b, g);
    return 0;
}