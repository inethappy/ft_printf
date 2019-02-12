 #include "ft_printf.h"

int	ft_len_nb(long long int nb)
{
	int len;

	len = 0;
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	else if (nb == 0)
		len = 1;
	while (nb > 0 && ++len)
		nb /= 10;
	return (len);
}

char *ft_itoa_base(int value, int base)
{
	char *str;
	int i;
	int value_tmp;
	int sign;

	value_tmp = value;
	sign = (value < 0 && base == 10) ? -1 : 0;
	i = (sign == -1) ? 2 : 1;
	while((value_tmp /= base) >= 1)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	str[i] = '\0';
	value_tmp = value;
	while (i-- + sign)
	{
		str[i] = (value_tmp % base < 10) ? value_tmp % base + '0' : value_tmp % base + 'A' - 10;
		value_tmp /= base;
	}
	(i == 0) ? str[i] = '-' : 0;
	return (str);
}

char	*ft_itoa_new(long long int n)
{
	char	*fresh;
	int		len;
	
    len = ft_len_nb(n);
	if (!(fresh = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (n == -9223372036854775808)
	 	return (ft_strdup("9223372036854775808"));
    if (n == 0)
		fresh[0] = '0';
	fresh[len] = '\0';
	while (n > 0 && len > 0)
	{
		fresh[--len] = n % 10 + '0';
		n /= 10;
	}
	return (fresh);
}

long long int cast_di(t_base *base, t_flags *fl)
{
    if (fl->j)
    	return (va_arg(base->ap, intmax_t));
	else if (fl->z)
        return (va_arg(base->ap, size_t));
	else if (fl->h)
        return ((short)va_arg(base->ap, int));
    else if (fl->hh)
        return ((signed char)va_arg(base->ap, int));
    else if (fl->l)
        return (va_arg(base->ap, long int));   
    else if (fl->ll)
        return (va_arg(base->ap, long long int));
    // else if (fl->L)
    //     di = va_arg(base->ap, );
    else
        return (va_arg(base->ap, int));
}

char	*join_all(char *s1, char *s2, char *s3)
{
	char	*fresh;
	int		i;
    int a;
    int b;
    int c;
    //a,b,c = 0;

    if (s1)
        a = ft_strlen(s1);
	if (s2)
        b = ft_strlen(s2);
    if (s3)
        c = ft_strlen(s3);
    if (!s1 && !s2 && !s3)
		return (NULL);
	i =  a + b + c + 1;
	if (!(fresh = (char *)malloc(sizeof(*fresh) * i)))
		return (NULL);
	if (fresh == NULL)
		return (NULL);

	if (s1)
        ft_strcpy(fresh, s1);
	if (s2)
        ft_strcat(fresh, s2);
    if (s3)
        ft_strcat(fresh, s3);
    // printf("1 = %p, 2 = %p, 3 = %p", s1, s2, s3);
	if (s1)
       free(s1);
	if (s2)
       free(s2);
    if (s3)
       free(s3);
	return (fresh);
}
