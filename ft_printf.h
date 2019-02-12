#ifndef FT_PRINTF_H
# define FT_PRINTF_H
#include <stdio.h>
#include <stdarg.h>
#include "libft/libft.h"


typedef struct s_base
{
    va_list ap;
    char *fmt;

    char *str;
    char *sign;
    int res;
}              t_base;

typedef struct      s_flags
{
    int hash;
    int null;
    int minus;
    int space;
    int plus;
    
    int dot;

    int width;
   
    int prec;
   
    int h;
    int hh;
    int l;
    int ll;
    int L;
    int z;
    int j;

    //enum width{digit, star};

    char con;
 }                   t_flags;

int ft_printf(const char *format, ...);
void ft_parsing(t_base *base);

void ft_search_fl(char *fmt, t_flags *flags);
void ft_search_prec(t_base *base, t_flags *flags);
void ft_search_width(t_base *base, t_flags *flags);
void ft_search_length(char *fmt, t_flags *flags);
void ft_search_specifier(char *fmt, t_flags *flags);

void work_cur_case(t_base *base, t_flags *flags);

int print_con_scp(t_base *base, t_flags *flags);
int print_con_oux(t_base *base, t_flags *fl);
int print_con_di(t_base *base, t_flags *flags);
int print_con_f(t_base *base, t_flags *flags);

char *print_padding(long long int di, t_flags *flags, int pad);
char *put_sign(long long int di, t_flags *flags);
void put_di_if_minus(long long int di, t_flags *flags, t_base *base);
void put_di_if_not_minus(long long int di, t_flags *flags, t_base *base);
void put_prec(long long int di, t_flags *flags, char *str);

char *join_all(char *s1, char *s2, char *s3);
int	ft_len_nb(long long int nb);
char	*ft_itoa_new(long long int n);
long long int cast_di(t_base *base, t_flags *flags);
char *ft_itoa_base(int value, int base);

int ft_printing_c(t_base *base, t_flags *fl);
int ft_printing_s(t_base *base, t_flags *fl);
int ft_printing_p(t_base *base, t_flags *fl);

#endif