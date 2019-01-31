#include "ft_printf.h"

void print_con_scp(t_base *base, t_flags *flags)
{
    char *s;
    char c;
    if (flags->con == 's')
    {
        s = va_arg(base->ap, char*);
        ft_putstr(s);
    }
    else if (flags->con == 'c')//можно сократить
    {
        c = va_arg(base->ap, int);
        ft_putchar(c);
    }
    // else
    //     pointer
}

// void print_con_f(t_base *base, t_flags *flags)
// {}

