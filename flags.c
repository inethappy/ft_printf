//>gcc ft_printf.c flags.c libft\ft_bzero.c libft\ft_strchr.c libft\ft_atoi.c libft\ft_putchar.c libft\ft_putstr.c
#include "ft_printf.h"

void ft_search_flags(char *fmt, t_flags *flags)
{
    flags->hash = (*fmt == '#') ? 1 : 0;
    flags->space = (*fmt == ' ') ? 1 : 0;
    flags->null = (*fmt == '0') ? 1 : 0;
    flags->minus = (*fmt == '-') ? 1 : 0;
    flags->plus = (*fmt == '+') ? 1 : 0;
}

void ft_search_width(char *fmt, t_flags *flags)
{
    flags->h = (*fmt == 'h' && *(fmt + 1) != 'h') ? 1 : 0;
    flags->hh = (*fmt == 'h' && *(fmt + 1) == 'h') ? 1 : 0;
    flags->l = (*fmt == 'l' && *(fmt + 1) != 'l') ? 1 : 0;
    flags->ll = (*fmt == 'l' && *(fmt + 1) == 'l') ? 1 : 0;
    flags->L = (*fmt == 'L') ? 1 : 0;
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

