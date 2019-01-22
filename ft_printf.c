#include "ft_printf.h"

void ft_parsing(t_base *base)
{
    t_flags flags;
   
   ft_bzero(&flags, sizeof(flags)); //???
   //ft_memalloc(sizeof(flags));
    while (ft_strchr("#0- +hldiouxXscp", *base->fmt))// all flags need to be here (?)
    {
        if (ft_strchr("#0- +", *base->fmt))
            ft_search_flags(base->fmt, &flags);
        else if (ft_strchr("hl", *base->fmt))
            ft_search_width(base->fmt, &flags);
        else if (ft_strchr("diouxXscp", *base->fmt))
            ft_search_specifier(base->fmt, &flags);
        base->fmt++;
    }
    base->fmt++;
    work_flags(base, &flags);
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
            // if (!*format)//?
            //     break ;
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
    b = 42343;
    // char *b;
    // b = "asdas";
    int g;
    g = -666;
    printf("printf: %d, %d\n", b, g); 
    //printf( "%0*.*d", 5, 5, 44);
    ft_printf("ft_printf: %hd, %d\n", b, g);
    return 0;
}