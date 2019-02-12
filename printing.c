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
    base->str = (di < 0) ? ft_itoa_new(-di) : ft_itoa_new(di);
    base->sign = put_sign(di, fl);
    if (di == 0 && fl->dot && !fl->width)
    {
        free(base->sign);
        return 0;
    }
    if (!fl->minus)
        put_di_if_not_minus(di, fl, base);
    else
        put_di_if_minus(di, fl, base);
    ft_putstr(base->str);
    return (ft_strlen(base->str));
}

int print_con_oux(t_base *base, t_flags *fl)
{
    int o;
    o = va_arg(base->ap, int);
    base->str = ft_itoa_base(o, 8);
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
        put_di_if_not_minus(o, fl, base);
    else
        put_di_if_minus(o, fl, base);
    ft_putstr(base->str);
    return (ft_strlen(base->str));
}



// void print_con_f(t_base *base, t_flags *fl)
// {}

