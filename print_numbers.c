#include "ft_printf.h"

int put_prec(int di, int i, t_flags *flags, char *str)
{
    (di < 0) ? ft_memset((str + (flags->width - flags->prec)), 48, (flags->prec - ft_len_numb(di) + 1)) 
            : ft_memset((str + (flags->width - flags->prec)), 48, (flags->prec - ft_len_numb(di)));
    i = -1;
    while (str[++i + 1] != '0')
        ft_putchar(str[i]);
    if (flags->plus && di > 0 && (flags->width >= flags->prec))
    {
        if (flags->width > flags->prec)
            i++;
        ft_putchar('+');
    }
    if (di < 0 && (flags->width >= flags->prec))
    {
        if (flags->width > flags->prec)
            i++;
        ft_putchar('-');
    }
    return i;
}

void ft_print_padding(int di, t_flags *flags, int pad)
{
    int var = 0;
    char *str;
    int fl = 0;
    int i = 0;
    if (flags->width >= flags->prec)
        fl = flags->width;
    else
        fl = (di < 0 || flags->plus) ? flags->prec + 1 : flags->prec;
    if (fl > ft_len_numb(di))
        var = (di < 0) ? (fl - ft_len_numb(di)) : (fl - ft_len_numb(di) - flags->plus);
    str = ft_strnew(var + 1);
    ft_memset(str, pad, var);
    if (flags->prec >= ft_len_numb(di)/*flags->width*/)
    {
        if (fl > ft_len_numb(di))
            i = put_prec(di, i, flags, str);
        ft_putstr(str + i);
    }
    else
    {
        if (flags->space && flags->null && (!flags->plus && di > 0))
            str[0] = 32;
        ft_putstr(str);
    }
    free(str);
}

void ft_printing_di(t_base *base, t_flags *flags)
{
    long long di;
    di = va_arg(base->ap, int);
    if (!flags->width && !flags->prec && !flags->plus && !flags->null)
            put_sign(di, flags);
    if (!flags->minus)
    {
        if ((flags->null && flags->width && !flags->prec) 
            || (flags->prec && !flags->width) || (flags->width <= flags->prec))
        {
            put_sign(di, flags);          
            ft_print_padding(di, flags, 48);
        }
        else if ((!flags->null && flags->width && !flags->prec) || (flags->width > flags->prec))
        {
            ft_print_padding(di, flags, 32);
            if (flags->prec < ft_len_numb(di))
                put_sign(di, flags);            
        }
        // else if (flags->width >= flags->prec)
        // {
        //     ft_print_padding(di, flags, 32);
        //     put_sign(di, flags);
        // }
        (di < 0) ? ft_putnbr(-di) : ft_putnbr(di);
    }
    else
    {
        if (flags->width && !flags->prec)
        {
            put_sign(di, flags);
            if (flags->width > ft_len_numb(di))
            {
                flags->width = 0;
                ft_print_padding(di, flags, 48);
            }
            (di < 0) ? ft_putnbr(-di) : ft_putnbr(di);
        }
        else if ((flags->prec && !flags->width) || (flags->prec >= flags->width))
        {
            if (flags->prec >= flags->width)
                put_sign(di, flags);
            ft_print_padding(di, flags, 48);
            (di < 0) ? ft_putnbr(-di) : ft_putnbr(di);
        }
        else if (flags->width > flags->prec)
        {
            put_sign(di, flags);
            if (flags->width > ft_len_numb(di))
                put_prec_minus(di, flags);
            else
                (di < 0) ? ft_putnbr(-di) : ft_putnbr(di);
        }
    }
}

void put_prec_minus(int di, t_flags *flags)
{
    char *str = NULL;
    int fl = 0;
    int i = -1;

    fl = flags->width - flags->prec;
    str = ft_strnew(flags->width - ft_len_numb(di) + 1);
    if (di > 0)
    {
        ft_memset(str, 48, (flags->prec - ft_len_numb(di)));
        ft_memset((str + (flags->prec - ft_len_numb(di))), 32, fl);
    }
    else
    {
        ft_memset(str, 48, (flags->prec - ft_len_numb(di) + 1));
        ft_memset((str + (flags->prec - ft_len_numb(di) + 1)), 32, (fl - 1));
    }
    while (str[++i] == 48)
        ft_putchar(str[i]);
    (di < 0) ? ft_putnbr(-di) : ft_putnbr(di);
    ft_putstr(str + i);
    free(str);
}

void put_sign(int di, t_flags *flags)
{
    if (flags->plus && di > 0 && (flags->width > flags->prec || flags->width < flags->prec))
        ft_putchar('+');
    else if (di < 0 && (flags->width > flags->prec || flags->width < flags->prec))
        ft_putchar('-');
    else if (flags->space && di > 0 && !flags->width && !flags->prec)
        ft_putchar(' ');
    else if (/*flags->minus && */flags->space && di > 0 && !flags->plus && (!flags->width || flags->width <= flags->prec))//
    {
        ft_putchar(' ');
        if (flags->width > flags->prec)
            flags->width--;
    }
}