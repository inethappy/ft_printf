#ifndef FT_PRINTF_H
# define FT_PRINTF_H
#include <stdio.h>
#include <stdarg.h>
#include "libft/libft.h"


typedef struct s_base
{
    va_list ap;
    char *fmt;

    int d;
    char *s;
    char c;
    double f;
}              t_base;

typedef struct      s_flags
{
    int hash;
    int null;
    int minus;
    int space;
    int plus;

    int width;
   
    int prec;
   
    int h;
    int hh;
    int l;
    int ll;
    int L;

    //enum width{digit, star};

    char con;
 }                   t_flags;

int ft_printf(const char *format, ...);
void ft_parsing(t_base *base);

void ft_search_flags(char *fmt, t_flags *flags);
void ft_search_prec(t_base *base, t_flags *flags);
void ft_search_width(t_base *base, t_flags *flags);
void ft_search_length(char *fmt, t_flags *flags);
void ft_search_specifier(char *fmt, t_flags *flags);

void work_cur_case(t_base *base, t_flags *flags);

void print_con_scp(t_base *base, t_flags *flags);
void ft_printing_di(t_base *base, t_flags *flags);
void print_con_f(t_base *base, t_flags *flags);
void ft_print_padding(int di, t_flags *flags, int pad);
void put_sign(int di, t_flags *flags);


#endif