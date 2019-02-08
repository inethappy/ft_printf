//>gcc ft_printf.c flags.c libft\ft_bzero.c libft\ft_strchr.c libft\ft_atoi.c libft\ft_putchar.c libft\ft_putstr.c
#include "ft_printf.h"

void ft_search_flags(char *fmt, t_flags *flags)
{
    flags->hash = (*fmt == '#') ? 1 : flags->hash;
    flags->space = (*fmt == ' ') ? 1 : flags->space;
    flags->null = (*fmt == '0') ? 1 : flags->null;
    flags->minus = (*fmt == '-') ? 1 : flags->minus;
    flags->plus = (*fmt == '+') ? 1 : flags->plus;
}

void ft_search_length(char *fmt, t_flags *flags)
{
    flags->h = (*fmt == 'h' && *(fmt - 1) != 'h') ? 1 : 0;
    flags->hh = (*fmt == 'h' && *(fmt - 1) == 'h') ? 1 : 0;
    flags->l = (*fmt == 'l' && *(fmt - 1) != 'l') ? 1 : 0;
    flags->ll = (*fmt == 'l' && *(fmt - 1) == 'l') ? 1 : 0;
    flags->L = (*fmt == 'L') ? 1 : 0;
}

void ft_search_width(t_base *base, t_flags *flags)
{
    if ((flags->width = ft_atoi(base->fmt)))
        while (ft_strchr("1234567890", *(base->fmt + 1)))
             base->fmt += 1;
    else
        flags->width = va_arg(base->ap, int);
} 

void ft_search_prec(t_base *base, t_flags *flags)
{
    base->fmt++;
    if ((flags->prec = ft_atoi(base->fmt)))
        while (ft_strchr("0123456789", *(base->fmt + 1)))
            base->fmt += 1;
    else if (ft_strchr("*", *(base->fmt)))
    {
        flags->prec = va_arg(base->ap, int);
        base->fmt += 1;
    }
} 

void work_cur_case(t_base *base, t_flags *flags)
{
    if (ft_strchr("scp", flags->con))
        print_con_scp(base, flags);
    else if (ft_strchr("di", flags->con))
        base->res = base->res + ft_printing_di(base, flags);
    
    // else if (ft_strchr("ouxX", flags->con))
    //     print_con_oux(base, flags);
    // else if (ft_strchr("fF", flags->con))
    //     print_con_f(base, flags);
}
