#include "ft_printf.h"

// void ft_parsing(const char *fmt)
// {
//     while (*fmt)
//     {
//         if (*fmt == '#' || *fmt == '0' || *fmt == ' ' || *fmt = '+')
//             ft_flags_handling(*fmt);
//         else if (*fmt == 'h' || *fmt == 'l')
//             ft_wight_handling(*fmt);
//         else
//         {}
//         fmt++;
//     }
// }

// int ft_printf(const char *format, ...)
// {
//     int d = 0;
//     va_list ap;
//     va_start(ap, format);
//     while (*format)
//     {
//         if (*format == '%')
//         {
//             format++;
//             ft_parsing(format);
//             if (!*format)//?
//                 break ;
//         }
//         else
//             ft_putchar(*format);
//         format++;       
//     }
//     va_end(ap);
//     return 0;
// }

int main()
{
    char *b;
    b = "asdas";
    int g;
    g = -666;
    printf("printf: %s, %d\n", b, g); 
    printf( "%0*.*d", 5, 5, 44);
    //ft_printf("ft_printf: %d, %d\n", b, g);
    return 0;
}