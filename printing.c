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

void ft_print_padding(int di, t_flags *flags, int pad)
{
    int var = 0;
    char *str;
    int fl = 0;
    if (flags->width > flags->prec)
        fl = (flags->width);
    else
        fl = (di < 0 || flags->plus) ? flags->prec + 1 : flags->prec;
    if (fl > ft_len_numb(di))
        var = (di < 0) ? (fl - ft_len_numb(di)) : (fl - ft_len_numb(di) - flags->plus);
    str = ft_strnew(var + 1);
    ft_memset(str, pad, var);
    if (!flags->prec)
        ft_putstr(str);
    else
    {
        ft_memset((str + (flags->width - flags->prec)), 48, (flags->prec - ft_len_numb(di) + 1));
        int i = -1;
        while (str[++i + 1] != '0')
            ft_putchar(str[i]);
        if (flags->plus && di > 0)
            str[i] = '+';
        if (di < 0)
            str[i] = '-';
        ft_putstr(str + i);
    }
    free(str);
}

void ft_printing_di(t_base *base, t_flags *flags)
{
    int di;
    di = va_arg(base->ap, int);

    if (!flags->minus)
    {
        if (flags->null && flags->width && !flags->prec)
        {
            if (flags->plus && di > 0)
                ft_putchar('+');
            if (di < 0)
                ft_putchar('-');
            ft_print_padding(di, flags, 48);
            (di < 0) ? ft_putnbr(-di) : ft_putnbr(di);
        }
        else if (!flags->null && flags->width && !flags->prec)
        {
            ft_print_padding(di, flags, 32);
            if (flags->plus && di > 0)
                ft_putchar('+');
            if (di < 0)
                ft_putchar('-');
            (di < 0) ? ft_putnbr(-di) : ft_putnbr(di);
        }
        else if ((flags->prec && !flags->width) || (flags->width < flags->prec))
        {
            if (flags->plus && di > 0)
                ft_putchar('+');
            if (di < 0)
                ft_putchar('-');
            ft_print_padding(di, flags, 48);
            (di < 0) ? ft_putnbr(-di) : ft_putnbr(di);
        }
        else if (flags->width > flags->prec)
        {
            ft_print_padding(di, flags, 32);
            (di < 0) ? ft_putnbr(-di) : ft_putnbr(di);
        }
    }
}

