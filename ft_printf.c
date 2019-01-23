#include "ft_printf.h"

void ft_parsing(t_base *base)
{
    t_flags flags;

    ft_bzero(&flags, sizeof(flags));
    //ft_memalloc(sizeof(flags));
    while (ft_strchr("#0- +12345789*.lhLdiouxXscp", *base->fmt))// all flags need to be here (?)
    {
        if (ft_strchr("#0- +", *base->fmt))
            ft_search_flags(base->fmt, &flags);
        else if (ft_strchr("123456789*", *base->fmt))
            flags.width = (ft_atoi(base->fmt)) ? ft_atoi(base->fmt) : -1;
        else if (ft_strchr(".", *base->fmt) && ft_strchr("123456789*", *(base->fmt + 1)))
            flags.prec = ft_atoi(++base->fmt) ? ft_atoi(base->fmt) : -1;
        else if (ft_strchr("hlL", *base->fmt))
            ft_search_width(base->fmt, &flags);
        else if (ft_strchr("diouxXscp", *base->fmt))
            flags.con = *base->fmt;
        base->fmt++;
    }
    printf("%d\n", flags.prec);
    work_flags(base, &flags);
    base->fmt--;
}

int ft_printf(const char *format, ...)
{
    t_base base;
   
    base.fmt = (char *)format;
    va_start(base.ap, format);
    while (*base.fmt)
    {
        if (*base.fmt == '%')
        {
            base.fmt++;
            ft_parsing(&base);
        }
        else
            ft_putchar(*base.fmt); //save in str?
        base.fmt++; 
    }
    va_end(base.ap);
    return 0;
}

int main()
{
    int b;
    b = 42;
    // char *b;
    // b = "asdas";
    int g;
    g = 4397440;
    printf("printf: %.7d, %d\n", b, g); 
    //printf( "%0*.*d", 5, 5, 44);
    ft_printf("ft_printf: %.*d, %d\n", b, g);
    //system("leaks ft_printf.out");
    return 0;
}