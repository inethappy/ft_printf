 #include "ft_printf.h"

void put_prec(long long int di, t_flags *fl, char *str)
{
    int i;

    (di < 0) ? ft_memset((str + (fl->width - fl->prec)), 48, (fl->prec - fl->len + 1)) 
            : ft_memset((str + (fl->width - fl->prec)), 48, (fl->prec - fl->len));
    i = 0;
    while (str[i + 1] != '0')
        i++;
    if (fl->plus && di > 0 && (fl->width > fl->prec))
        str[i] = '+';
    if (di < 0 && (fl->width > fl->prec))
        str[i] = '-';
}

char *print_padding(long long int di, t_flags *fl, int pad)
{
    int var = 0;
    char *str = NULL;
    int wd = 0;

    if ((fl->width > fl->prec && fl->width <= fl->len) 
        || (!fl->width && fl->prec <= fl->len))
        return NULL;
    if (fl->width >= fl->prec)
        wd = fl->width;
    else
        wd = (di < 0 || fl->plus) ? fl->prec + 1 : fl->prec;
    if (wd > fl->len)
        var = (di < 0) ? (wd - fl->len) : (wd - fl->len - fl->plus);
    str = ft_strnew(var + 1);
    ft_memset(str, pad, var);
    if (fl->prec >= fl->len && fl->width)
        put_prec(di, fl, str);
    else if (fl->prec < fl->len && fl->width > fl->len)
        if (fl->space && fl->null && (!fl->plus && di > 0))
            str[0] = 32;
    if (fl->hash && fl->null)
        str = hash_x_func(fl, str);
    return (str);
}




void put_dio_if_not_minus(long long int di, t_flags *fl, t_base *base)
{
    if (!fl->width && !fl->prec && !fl->null)
        base->str = join_all(base->sign, print_padding(di, fl, 48), base->str);
    else if ((fl->null && fl->width && !fl->prec && !fl->dot) || (fl->width <= fl->prec)
        || (fl->prec && !fl->width))
        base->str = join_all(base->sign, print_padding(di, fl, 48), base->str);
    else if (((!fl->null && ((fl->width && !fl->prec) || (fl->width > fl->prec))) 
        || (fl->null && (fl->prec || fl->dot) && fl->width > fl->prec)))
    {
        if (di == 0 && !fl->prec && fl->width)
            base->str[0] = 32;
        else if (fl->width > fl->prec && fl->prec >= fl->len)
            ft_strdel(&base->sign);
        base->str = join_all(print_padding(di, fl, 32), base->sign, base->str);
    }
}

void put_dio_if_minus(long long int di, t_flags *fl, t_base *base)
{
    int i;
    char *s;

    fl->null = 0;
    if (!fl->width && !fl->prec && !fl->null)
        base->str = join_all(base->sign, base->str, print_padding(di, fl, 32));
    else if ((fl->width && !fl->prec) || fl->width > fl->prec)
    {
        if (fl->width > fl->prec && fl->width > ft_len_nb(di) && fl->prec > ft_len_nb(di))
        {
            i = fl->width;
            fl->width = 0;
            s = (fl->con == 'u') ? print_padding(di, fl, 48) : ft_strjoin(base->sign, print_padding(di, fl, 48));
            s = ft_strjoin(s, base->str);
            fl->width = i - (fl->prec - fl->len);
            fl->prec = 0;  
            ft_strdel(&base->sign);              
            base->str = join_all(base->sign, s, print_padding(di, fl, 32));
        }
        else
            base->str = join_all(base->sign, base->str, print_padding(di, fl, 32));
    }
    else if ((fl->prec && !fl->width) || (fl->prec >= fl->width))
        base->str = join_all(base->sign, print_padding(di, fl, 48), base->str);
}

char *put_sign(long long di, t_flags *fl)
{
    char *sign;

    sign = ft_strnew(1);
    if (fl->plus && di >= 0)
        sign[0] = '+';
    else if (di < 0 || ((di < 0) && (fl->width > fl->prec || fl->width < fl->prec)))
        sign[0] = '-';
    else if (fl->space && di >= 0 && !fl->prec)
        sign[0] = ' ';
    else if (fl->space && di >= 0 && !fl->plus 
        && (!fl->width || fl->width <= fl->prec || (di == 0 && fl->width)))
    {
        sign[0] = ' ';
        if (fl->width > fl->prec)
            fl->width--;
    }
    if (!sign)
        {
            free(sign);
            return NULL;
        }
    return (sign);
}