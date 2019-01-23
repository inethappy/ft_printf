#include "ft_printf.h"

void ft_search_flags(char *fmt, t_flags *flags)
{
    flags->hash = (*fmt == '#') ? 1 : 0;
    flags->space = (*fmt == ' ') ? 1 : 0;
    flags->null = (*fmt == '0') ? 1 : 0;
    flags->minus = (*fmt == '-') ? 1 : 0;
    flags->plus = (*fmt == '+') ? 1 : 0;
}

void ft_search_width(char *fmt, t_flags *flags)
{
    flags->h = (*fmt == 'h' && *(fmt + 1) != 'h') ? 1 : 0;
    flags->hh = (*fmt == 'h' && *(fmt + 1) == 'h') ? 1 : 0;
    flags->l = (*fmt == 'l' && *(fmt + 1) != 'l') ? 1 : 0;
    flags->ll = (*fmt == 'l' && *(fmt + 1) == 'l') ? 1 : 0;
}

// void ft_search_specifier(char *fmt, t_flags *flags)
// {
//     flags->d = (*fmt == 'd') ? 1 : 0;
// }

void work_flags(t_base *base, t_flags *flags)
{
    int d = 0;
    if (/*flags->plus && */flags->con == 'd')
    {
        //while (*fmt)??
        d = va_arg(base->ap, int);
        ft_putnbr(d);
    }
}