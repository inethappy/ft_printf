#include "ft_printf.h"

int print_con_scp(t_base *base, t_flags *fl)
{
    if (fl->con == 's' || fl->con == 'S')
        return (ft_printing_s(base, fl));
    if (fl->con == 'c' || fl->con == 'C')
        return (ft_printing_c(base, fl));
    else
        return (ft_printing_p(base, fl));
    return 0;
}

int print_con_di(t_base *base, t_flags *fl)
{
    long long int di;

    di = cast_di(base, fl);
    base->str = (di < 0) ? ft_itoa_signed(-di) : ft_itoa_signed(di);
    fl->len = (di < 0) ? (ft_strlen(base->str) + 1) : (ft_strlen(base->str));
    base->sign = put_sign(di, fl);
    if (di == 0 && fl->dot && !fl->width)
    {
        free(base->sign);
        return (0);
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
    base->sign = NULL;
    fl->len = (ft_strlen(base->str));
    if (o == 0 && fl->dot && !fl->width && !fl->hash)
        return 0;
    if (fl->hash)
    {
        if (!fl->prec && !fl->null)
            fl->prec = (o == 0) ? (fl->len) : (fl->len + 1);
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
    base->sign = NULL;
    fl->len = (ft_strlen(base->str));
    if (u == 0 && fl->dot && !fl->width)
        return 0;
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
    base->sign = NULL;
    fl->len = (ft_strlen(base->str));
    if (x == 0 && fl->dot && !fl->width)
        return 0;
    if (fl->hash && fl->width)
        fl->width -= 2;
    
    if (x != 0 && fl->hash && (!fl->null || fl->minus) && !fl->prec)
        base->str = hash_x_func(fl, base->str, x);
    
    if (!fl->minus)
        put_dio_if_not_minus(x, fl, base);
    else
        put_dio_if_minus(x, fl, base);
    if (x != 0 && fl->hash && fl->prec && (!fl->null || fl->minus))
        base->str = hash_x_func(fl, base->str, x);
    ft_putstr(base->str);
    return (ft_strlen(base->str));
}

int print_con_fF(t_base *base, t_flags *fl)
{
    double f;

    f = va_arg(base->ap, double);
    ft_ftoa(f, base, fl);
    ft_putstr(base->str);
    return (ft_strlen(base->str));
}

void	ft_ftoa(double nb, t_base *base, t_flags *fl)
{
	char    *fresh;
	double  tmp;
    double  del;
    int     i;

    i = 1;
    del = 1;
    base->sign = put_sign((long long int)nb, fl);
    nb = (nb < 0) ? -nb : nb; 
    tmp = nb;
    while (tmp > 10 && ++i && (tmp /= 10))
        del *= 10;
    fresh = (fl->dot || fl->hash) ? ft_strnew(i + 1) : ft_strnew(i);
    i = 0;
    while (nb >= 1 && (tmp = nb) && (tmp /= del))
    {   
        tmp = (long long int)tmp;
        fresh[i++] = (long long int)tmp % 10 + '0';
        tmp *= del;
        nb -= tmp;
        del /= 10;
        // printf("%f, %d\n", nb, (long long int)nb);
        if (nb < 10 && fl->dot)
            nb += ((long long int)(nb + 0.5) % 2 == 0) ? (0.5) : (0.49);
    }
        // printf("2 %f, %d\n", nb, (long long int)nb);
    base->str = ft_prec_f(fresh, base, fl, nb);
}

char *ft_make_str_f(t_base *base, t_flags *fl, char *str, char *fresh)
{
    char *new;
    if (fl->width)
    {
        if (fl->minus)
            new = join_all(base->sign, str, print_padding(ft_atoi(fresh), fl, fl->pad));
        else
            new = (fl->null) ? join_all(base->sign, print_padding(ft_atoi(fresh), fl, fl->pad), str) 
                : join_all(print_padding(ft_atoi(fresh), fl, fl->pad), base->sign, str);
    }
    else
        new = ft_strjoin(base->sign, str);
    if (fl->dot && fl->hash)
        new[ft_strlen(new)] = '.';
    ft_strdel(&str);
    return (new);
}

void del_str(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

char *ft_prec_f(char *fresh, t_base *base, t_flags *fl, double nb)
{
    char pad;
    char *new;
    char *buf;
    int i;
    double j;

    fl->len = ft_strlen(fresh);
    fl->pad = (fl->null && !fl->minus) ? (48) : (32);
    if (fl->dot)
        return (ft_make_str_f(base, fl, fresh, fresh));
    j = 5;
    fresh[fl->len] = '.';
    fl->prec = fl->prec ? fl->prec : 6;
    i = -1;
    while (++i <= fl->prec)
        j /= 10;
    nb += j;
    while (--i)
        nb *= 10; 
    new = ft_itoa_unsigned((unsigned long long int)nb);
    buf = ft_strjoin(fresh, new);
    fl->len = ft_strlen(buf);
    del_str(fresh, new);
    fl->prec = 0;
    return (ft_make_str_f(base, fl, buf, fresh));
}
