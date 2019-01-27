#include "ft_printf.h"

void print_con_dioux(t_base *base, t_flags *flags)
{
    int d;

    if (flags->con == 'd' || flags->con == 'i')
    {
        d = va_arg(base->ap, int);
        ft_printing_d(d, flags);
    }
        

}

void print_con_scp(t_base *base, t_flags *flags)
{
    char *s;
    char c;
   // printf("%c\n", flags->con);
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



// char *padding(t_base *base, t_flags *flags)
// {
//     char *str;

//     str = ft_strnew(flags->width);
//     if (flags->null && flags->width)
//         ft_memset(str, 0, flags->width);
//     else if (!flags->null && flags->width)
//         ft_memset(str, ' ', flags->width);



    // else if (!flags->null && !flags-width)

    // else


//     prec
//     return (str);
//         if (d && flahs->plus) ...

// }