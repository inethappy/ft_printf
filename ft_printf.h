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
    int len;

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

    char con;
 }                   t_flags;

int ft_printf(const char *format, ...);
void ft_parsing(t_base *base);
void con_not_found(t_base *base, t_flags *fl);

void ft_search_fl(char *fmt, t_flags *fl);
void ft_search_prec(t_base *base, t_flags *fl);
void ft_search_width(t_base *base, t_flags *fl);
void ft_search_length(char *fmt, t_flags *fl);
void ft_search_specifier(char *fmt, t_flags *fl);

void work_cur_case(t_base *base, t_flags *fl);

int print_con_scp(t_base *base, t_flags *fl);
int print_con_o(t_base *base, t_flags *fl);
int print_con_di(t_base *base, t_flags *fl);
int print_con_fF(t_base *base, t_flags *fl);
int print_con_u(t_base *base, t_flags *fl);
int print_con_xX(t_base *base, t_flags *fl);

char *print_padding(long long int di, t_flags *fl, int pad);
char *put_sign(long long int di, t_flags *fl);
void put_dio_if_minus(long long int di, t_flags *fl, t_base *base);
void put_dio_if_not_minus(long long int di, t_flags *fl, t_base *base);
void put_prec(long long int di, t_flags *fl, char *str);

char *join_all(char *s1, char *s2, char *s3);
int	ft_len_nb(long long int nb);
char	*ft_itoa_signed(long long int n);
long long int cast_di(t_base *base, t_flags *fl);
unsigned long long int cast_ou(t_base *base, t_flags *fl);
char *ft_itoa_base(unsigned long long int value, int base, t_flags *fl);
char *hash_x_func(t_flags *fl, char *str, int x);
char	*ft_itoa_unsigned(unsigned long long int n);
void ft_ftoa(double nb, t_base *base, t_flags *fl);
char *ft_prec_f(char *fresh, t_base *base, t_flags *fl, double nb);

int ft_printing_c(t_base *base, t_flags *fl);
int ft_printing_s(t_base *base, t_flags *fl);
int ft_printing_p(t_base *base, t_flags *fl);

#endif