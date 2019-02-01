#include "ft_printf.h"

void ft_parsing(t_base *base)
{
    t_flags flags;

    ft_bzero(&flags, sizeof(flags)); //ft_memalloc(sizeof(flags)); ?
    while (ft_strchr(" 0+#-12345789*.lhL", *base->fmt))
    {
        if (ft_strchr("#0- +", *base->fmt))
            ft_search_flags(base->fmt, &flags);
        else if (ft_strchr("123456789*", *base->fmt))
            ft_search_width(base, &flags);
        else if (ft_strchr(".", *base->fmt) && ft_strchr("123456789*", *(base->fmt + 1)))
            ft_search_prec(base, &flags);
        else if (ft_strchr("hlL", *base->fmt))
            ft_search_length(base->fmt, &flags);
        //printf("null = %d, plus = %d, w = %d\n", flags.null, flags.plus, flags.width);
        base->fmt++;
    }
    if (ft_strchr("diouxXscpfF", *base->fmt))
        flags.con = *base->fmt;
    base->fmt++;
    work_cur_case(base, &flags);
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
    int i;
    i = 42;
    char *s;
    s = "asdas";
    char c;
    c = 'z';
    int g;
    g = 12345678;
    printf("printf: %s, %c, [% 1.1d]\n", s, c, g); 
    //printf( "%0*.*d", 5, 5, 44);
    ft_printf("ft_printf: %s, %c, [% 1.1d]\n", s, c, g);

    //system("leaks ft_printf.out");
    return 0;
}