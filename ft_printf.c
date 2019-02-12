#include "ft_printf.h"

void ft_parsing(t_base *base)
{
    t_flags fl;

    ft_bzero(&fl, sizeof(fl)); //ft_memalloc(sizeof(fl)); ?
    while (*base->fmt != '\0' && ft_strchr(" 0+#-123456789*.lzhjL", *base->fmt))
    {
        if (ft_strchr("#0- +", *base->fmt))
            ft_search_fl(base->fmt, &fl);
        else if (ft_strchr("123456789*", *base->fmt))
            ft_search_width(base, &fl);
        else if (ft_strchr(".", *base->fmt)) //&& ft_strchr("0123456789*", *(base->fmt + 1)))
            ft_search_prec(base, &fl);
        else if (ft_strchr("zhlLj", *base->fmt))
            ft_search_length(base->fmt, &fl);
        // printf("space = %d, hash = %d, dot = %d, h = %d, hh = %d, ll = %d, l = %d, prec = %d, null = %d, plus = %d, w = %d\n", fl.space, fl.hash, fl.dot, fl.h, fl.hh, fl.ll, fl.l, fl.prec, fl.null, fl.plus, fl.width);
        base->fmt++;
    }
    if (*base->fmt == '\0')
        return ;
    if (ft_strchr("diouxXscpfF", *base->fmt))
        fl.con = *base->fmt;
    base->fmt++;
    work_cur_case(base, &fl);
    ft_strdel(&base->str);
}

int ft_printf(const char *format, ...)
{
    t_base base;

    ft_bzero(&base, sizeof(base));
    base.fmt = (char *)format;
    va_start(base.ap, format);
    while (*base.fmt != '\0')
    {
        if (*base.fmt == '%')
        {
            base.fmt++;
            ft_parsing(&base);
        }
        if (*base.fmt && *base.fmt != '%')
        {
            ft_putchar(*base.fmt); //save in str?
            base.res++;
            base.fmt++; 
        }
    }
    va_end(base.ap);
    return (base.res);
}

