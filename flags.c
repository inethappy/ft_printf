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
    flags->h = (*fmt == 'h' && *(fmt + 1) != 'h') ? 1 : 0;
    flags->hh = (*fmt == 'h' && *(fmt + 1) == 'h') ? 1 : 0;
    flags->l = (*fmt == 'l' && *(fmt + 1) != 'l') ? 1 : 0;
    flags->ll = (*fmt == 'l' && *(fmt + 1) == 'l') ? 1 : 0;
    flags->L = (*fmt == 'L') ? 1 : 0;
}

void ft_search_width(char *fmt, t_flags *flags)
{
    if (ft_atoi(fmt))
    {
        flags->width = ft_atoi(fmt);
        //  while (ft_strchr("123456789", *(fmt + 1)))
        //      fmt += 1;
    }
    // else
} 

void work_cur_case(t_base *base, t_flags *flags)
{
    if (ft_strchr("scp", flags->con))
        print_con_scp(base, flags);
    else if (ft_strchr("diouxX", flags->con))
        print_con_dioux(base, flags);
    // else if (ft_strchr("fF", flags->con))
    //     print_con_f(base, flags);
}

void ft_printing_d(int d, t_flags *flags)
{
    int var;

    var = 0;
    char *str;

    if (!flags->minus)
    {
        //padding(t_base base, t_flags flags);
        if (flags->null && flags->width)
        {
            var = (d < 0) ? (flags->width - (ft_len_numb(d) + 1) + 1) 
                : (flags->width - ft_len_numb(d) - flags->plus + 1);
            str = ft_strnew(var + 1);
            ft_memset(str, 48, var);
            if (flags->plus)
                str[0] = (d < 0) ? '-' : '+';
            d = (d < 0) ? -d : d;
            ft_putstr(str);
            ft_putnbr(d);
        }
        else
        {
            var = (d < 0) ? (flags->width - (ft_len_numb(d) + 1) + 1) 
                : (flags->width - ft_len_numb(d) - flags->plus + 1);
            str = ft_strnew(var + 1);
            ft_memset(str, 32, var);
            ft_putstr(str);
            if (flags->plus)
                (d < 0) ? ft_putchar('-') : ft_putchar('+');
            d = (d < 0) ? -d : d;
            ft_putnbr(d);
        }
    }
}
