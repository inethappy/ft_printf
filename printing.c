#include "ft_printf.h"

int print_con_scp(t_base *base, t_flags *fl)
{
    if (fl->con == 's')
        return(ft_printing_s(base, fl));
    if (fl->con == 'c')
        return(ft_printing_c(base, fl));
    else
        return(ft_printing_p(base, fl));
    return 0;
}

int print_con_di(t_base *base, t_flags *fl)
{
    long long int di;

    di = cast_di(base, fl);
    base->str = (di < 0) ? ft_itoa_signed(-di) : ft_itoa_signed(di);
    base->sign = put_sign(di, fl);
    if (di == 0 && fl->dot && !fl->width)
    {
        free(base->sign);
        return 0;
    }
    if (!fl->minus)
        put_dio_if_not_minus(di, fl, base);
    else
        put_dio_if_minus(di, fl, base);
    ft_putstr(base->str);
    return (ft_strlen(base->str));
}

int print_con_o(t_base *base, t_flags *fl)
{
    unsigned long long int o;

    o = cast_ou(base, fl);
    base->str = ft_itoa_base(o, 8, fl);
    base->sign = ft_strnew(1);
    if (o == 0 && fl->dot && !fl->width && !fl->hash)
    {
        free(base->sign);
        return 0;
    }
    if (fl->hash)
    {
        if (!fl->prec && !fl->null)
            fl->prec = fl->dot ? (ft_len_nb(o)) : (ft_len_nb(o) + 1);
    }
    if (!fl->minus)
        put_dio_if_not_minus(o, fl, base);
    else
        put_dio_if_minus(o, fl, base);
    ft_putstr(base->str);
    return (ft_strlen(base->str));
}

int print_con_u(t_base *base, t_flags *fl)
{
    unsigned long long int u;

    u = cast_ou(base, fl);
    base->str = ft_itoa_unsigned(u);
    base->sign = ft_strnew(1);
    if (u == 0 && fl->dot && !fl->width)
    {
        free(base->sign);
        return 0;
    }
    if (!fl->minus)
        put_dio_if_not_minus(u, fl, base);
    else
        put_dio_if_minus(u, fl, base);
    ft_putstr(base->str);
    return (ft_strlen(base->str));
}

int print_con_xX(t_base *base, t_flags *fl)
{
    unsigned long long int x;

    x = cast_ou(base, fl);
    base->str = ft_itoa_base(x, 16, fl);
    base->sign = ft_strnew(1);
   
    if (x == 0 && fl->dot && !fl->width)
    {
        free(base->sign);
        return 0;
    }
    if (fl->hash && fl->width)
        fl->width -= 2;
    if (x != 0 && fl->hash && (!fl->null || fl->minus))
        base->str = hash_x_func(fl, base->str);
    if (!fl->minus)
        put_dio_if_not_minus(x, fl, base);
    else
        put_dio_if_minus(x, fl, base);
    ft_putstr(base->str);
    return (ft_strlen(base->str));
}

// void print_con_f(t_base *base, t_flags *fl)
// {

// }

