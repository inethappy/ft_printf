#ifndef FT_PRINTF_H
# define FT_PRINTF_H
#include <stdio.h>
#include <stdarg.h>
#include "libft/libft.h"

typedef struct s_base
{
    va_list ap;
    char *fmt;    
}              t_base;

typedef struct      s_flags
{
    int hash;
    int null;
    int minus;
    int space;
    int plus;
   
    int h;
    int hh;
    int l;
    int ll;
    
    int d;
}                   t_flags;

int ft_printf(const char *format, ...);
void ft_parsing(t_base *base);
void ft_search_flags(char *fmt, t_flags *flags);
void ft_search_width(char *fmt, t_flags *flags);
void ft_search_specifier(char *fmt, t_flags *flags);
void work_flags(t_base *base, t_flags *flags);




#endif