#include "ft_printf.h"

int ft_printing_c(t_base *base, t_flags *fl)
{
    char c;

    fl->width = (fl->width == 0) ? 1 : fl->width;
    c = va_arg(base->ap, int);
    base->str = (ft_strnew(fl->width) + fl->space);
    fl->null ? ft_memset(base->str, 48, fl->width) : ft_memset(base->str, 32, fl->width); 
    fl->minus ? (base->str[0] = c) : (base->str[fl->width - 1] = c);
    ft_putstr(base->str);
    if (c == 0)
    {
        ft_putchar('\0');
        return (ft_strlen(base->str) + 1);
    }
    return (ft_strlen(base->str));
}

int ft_null(t_base *base)
{
    base->str = ft_strdup("(null)\0");
    ft_putstr(base->str);
    return (6);
}

int ft_printing_s(t_base *base, t_flags *fl)
{
    char *s;
    char *ss;
    char *s_pr;

    s = va_arg(base->ap, char*);
    if (s == NULL)
        return (ft_null(base));
    if (fl->prec)
    {
        s_pr = ft_strnew(fl->prec);
        s_pr = ft_strncpy(s_pr, s, fl->prec);
        s = ft_strdup(s_pr);
        free(s_pr);
    }  
    if (fl->width > ft_strlen(s))
    {
        ss = ft_strnew(fl->width - ft_strlen(s));
        (fl->null && !fl->minus) ? ft_memset(ss, 48, (fl->width - ft_strlen(s))) 
            : ft_memset(ss, 32, (fl->width - ft_strlen(s))); 
        base->str = fl->minus ? (ft_strjoin(s, ss)) : (ft_strjoin(ss, s));
        free(ss);
    }
    else
        base->str = ft_strdup(s);
    ft_putstr(base->str);
    return (ft_strlen(base->str));
}

int ft_printing_p(t_base *base, t_flags *fl)
{
    char *p;
    p = va_arg(base->ap, void *);
   
    return (ft_strlen(p));
}
