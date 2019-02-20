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
    fl->len = (di < 0) ? (ft_strlen(base->str) + 1) : (ft_strlen(base->str));
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
    fl->len = (ft_strlen(base->str));
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
    fl->len = (ft_strlen(base->str));
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
    fl->len = (ft_strlen(base->str));
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

int print_con_fF(t_base *base, t_flags *fl)
{
    double f;

    f = va_arg(base->ap, double);
    // printf("====%d\n", ft_len_nb(f));
    ft_ftoa(f, base, fl);
    ft_putstr(base->str);
    return (ft_strlen(base->str));
}

void	ft_ftoa(double nb, t_base *base, t_flags *fl)
{
	char	*fresh;
	double tmp;
    double del;
    int i = 1;

    tmp = nb;
    del = 1;
    while (tmp > 10 && ++i)
    {
        tmp /= 10;
        del *= 10;
    }
    fresh = (fl->dot) ? ft_strnew(i) : ft_strnew(i + 1);
    i = 0;
    while (nb >= 1)
    {   
        tmp = nb;
        tmp /= del;
        tmp = (int)tmp;
        fresh[i++] = (int)tmp % 10 + '0';
        tmp *= del;
        nb -= tmp;
        del /= 10;
        // printf("1-%f\n", nb);
        if (nb < 1 && fl->dot)
            nb += ((int)(nb + 0.5) % 2 == 0) ? (0.5) : (0.49);
        // printf("2-%f\n", nb);
    }
    (fl->dot) ? 0: (fresh[i++] = '.');
    // printf("fresh = %s, nb = %f, atoi_fr = %d\n", fresh, nb, ft_atoi(fresh));
    base->str = ft_prec_f(fresh, base, fl, nb);
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
    double j = 5;
    
    pad = (fl->null && !fl->minus) ? (48) : (32);
    base->sign = put_sign(ft_atoi(fresh), fl); // ????????!
    if (fl->dot)
    {
        fl->len = ft_strlen(fresh);
        if (fl->width)
        {
            if (fl->minus)
                new = join_all(base->sign, fresh, print_padding(ft_atoi(fresh), fl, pad));
            else
                new = (fl->null) ? join_all(base->sign, print_padding(ft_atoi(fresh), fl, pad), fresh) 
                    : join_all(print_padding(ft_atoi(fresh), fl, pad), base->sign, fresh);
        }
        else
            new = ft_strjoin(base->sign, fresh);
        return (new);
    }
    fl->prec = fl->prec ? fl->prec : 6;
    i = -1;
        while (++i <= fl->prec)
            j /= 10;
    if (fl->prec < ft_strlen(fresh))
        nb += j;
    while (--i)
        nb *= 10; 
    new = ft_itoa_unsigned((unsigned long long int)nb);
    buf = ft_strjoin(fresh, new);
    del_str(fresh, new);
    fl->prec= 0;
    if (fl->width)
    {
        fl->len = ft_strlen(buf);
        if (fl->minus)
            base->str = join_all(base->sign, buf, print_padding(ft_atoi(fresh), fl, pad));
        else
            base->str = (fl->null) ? join_all(base->sign, print_padding(ft_atoi(fresh), fl, pad), buf) 
                : join_all(print_padding(ft_atoi(fresh), fl, pad), base->sign, buf);
    }
    else
        base->str = ft_strjoin(base->sign, buf);
    // printf("4---%d, %s, base->str = [%s]\n", i, new, base->str);
    return (base->str);
    
    
        // printf("%.7f, prec = %d\n", j, fl->prec);
    // nb += ((int)(nb + 0.5) % 2 == 0) ? (0.5) : (0.49);// base->str = ft_itoa_unsigned(nb);

    // i = fl->width;
    // fl->width = 0;
    // fl->prec = fl->prec ? fl->prec : 6;
    // fl->len = ft_strlen(base->str);
    // buf = print_padding(nb, fl, 48);
    // new = (fl->prec > fl->len) ? ft_strjoin(base->str, buf): ft_strdup(base->str);
    // del_str(base->str, buf);
    // base->str = ft_strjoin(fresh, new);
    // del_str(fresh, new);
    // fl->len = ft_strlen(base->str);
    // fl->width = i;
    // fl->prec = 0;
    // if (i > fl->len)
    //     new = (fl->minus) ? (join_all(base->sign, base->str, print_padding(nb, fl, pad))) 
    //         : (join_all(print_padding(nb, fl, pad), base->sign, base->str));
    // else
    // {
    //     new = ft_strjoin(base->sign, base->str);
    //     del_str(base->sign, base->str);
    // }
    // return (new);
}
