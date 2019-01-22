#include "ft_printf.h"

void ft_search_flags(char *fmt, t_flags *flags)
{

    flags->hash = (*fmt == '#') ? 1 : 0;
    flags->space = (*fmt == ' ') ? 1 : 0;
    flags->null = (*fmt == '0') ? 1 : 0;
    flags->minus = (*fmt == '-') ? 1 : 0;
    flags->plus = (*fmt == '+') ? 1 : 0;
    // if (*fmt == '#')
    //     flags->hash = 1;
    // else if (*fmt == ' ')
    //     flags->space = 1;
    // else if (*fmt == '0')
    //     flags->null = 1;
    // else if (*fmt == '-')
    //     flags->minus = 1;
    // else if (*fmt == '+')
    //     flags->plus = 1;  
}

void ft_search_width(char *fmt, t_flags *flags)
{

    flags->h = (*fmt == 'h' && *(fmt + 1) != 'h') ? 1 : 0;
    flags->hh = (*fmt == 'h' && *(fmt + 1) == 'h') ? 1 : 0;
    flags->l = (*fmt == 'l' && *(fmt + 1) != 'l') ? 1 : 0;
    flags->hh = (*fmt == 'l' && *(fmt + 1) == 'l') ? 1 : 0;
    // if (*fmt == 'h' && *(fmt + 1) != 'h')
    //     flags->h = 1;
    // else if (*fmt == 'h' && *(fmt + 1) == 'h')
    //     {§
    //         flags->space = 1;
    //         fmt++;
    //     }
    // if (*fmt == 'l' && *(fmt + 1) != 'h')
    //     flags->h = 1;
    // else if (*fmt == 'h' && *(fmt + 1) == 'h')
    //     {
    //         flags->space = 1;
    //         fmt++;
    //     }
}

void ft_search_specifier(char *fmt, t_flags *flags)
{
    printf("{d = %d\n", flags->d);
    flags->d = (*fmt == 'd') ? 1 : 0;

}

void work_flags(t_base *base, t_flags *flags)
{
    int d = 0;
        printf("d = %d\n", flags->d);
    printf("h = %d\n", flags->h);
    printf("hh = %d\n", flags->hh);
    printf("# = %d\n", flags->hash);
    if (/*flags->plus && */flags->d)
    {
        //while (*fmt)??
        d = va_arg(base->ap, int);
        ft_putnbr(d);
    }
}