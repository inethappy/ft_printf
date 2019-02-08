 #include "ft_printf.h"

int	ft_len_numb_n(long long int nb)
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

char	*ft_itoa_new(long long int n)
{
	char	*fresh;
	int		len;
	
    len = ft_len_numb_n(n);
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

char	*ft_join_all(char *s1, char *s2, char *s3)
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

void put_prec(long long int di, t_flags *flags, char *str)
{
    int i;
    (di < 0) ? ft_memset((str + (flags->width - flags->prec)), 48, (flags->prec - ft_len_numb(di) + 1)) 
            : ft_memset((str + (flags->width - flags->prec)), 48, (flags->prec - ft_len_numb(di)));
    i = 0;
    while (str[i + 1] != '0')
        i++;
    if (flags->plus && di > 0 && (flags->width > flags->prec))
        str[i] = '+';
    if (di < 0 && (flags->width > flags->prec))
        str[i] = '-';
}

char *ft_print_padding(long long int di, t_flags *flags, int pad)
{
    int var = 0;
    char *str = NULL;
    int fl = 0;

    if ((flags->width > flags->prec && flags->width <= ft_len_numb(di)) 
        || (!flags->width && flags->prec <= ft_len_numb(di)))
        return NULL;
    if (flags->width >= flags->prec)
        fl = flags->width;
    else
        fl = (di < 0 || flags->plus) ? flags->prec + 1 : flags->prec;
    if (fl > ft_len_numb(di))
        var = (di < 0) ? (fl - ft_len_numb(di)) : (fl - ft_len_numb(di) - flags->plus);
    str = ft_strnew(var + 1);
    ft_memset(str, pad, var);
    if (flags->prec >= ft_len_numb(di) && flags->width)
        put_prec(di, flags, str);
    else if (flags->prec < ft_len_numb(di) && flags->width > ft_len_numb(di))
    {
        if (flags->space && flags->null && (!flags->plus && di > 0))
            str[0] = 32;
    }
    return (str);
}

long long int cast_di(t_base *base, t_flags *flags)
{
    if (flags->h)
        return ((signed short int)va_arg(base->ap, int));
    else if (flags->hh)
        return ((signed char)va_arg(base->ap, int));
    else if (flags->l)
        return (va_arg(base->ap, long int));   
    else if (flags->ll)
        return (va_arg(base->ap, long long int));
    // else if (flags->L)
    //     di = va_arg(base->ap, );
    else
        return (va_arg(base->ap, int));
}

int ft_printing_di(t_base *base, t_flags *flags)
{
    long long int di;
    di = cast_di(base, flags);
    base->str = (di < 0) ? ft_itoa_new(-di) : ft_itoa_new(di);
    base->sign = put_sign(di, flags);

    if (!flags->minus)
    {
        if (di == 0 && flags->prec == 0 && !flags->width && !flags->null && !flags->plus)
            return 0;
        // else if (di == 0 && flags->prec == 0)

        else if (!flags->width && !flags->prec && !flags->null)
            base->str = ft_join_all(base->sign, ft_print_padding(di, flags, 48), base->str);
        else if ((flags->null && flags->width && !flags->prec) || (flags->width <= flags->prec)
            || (flags->prec && !flags->width))
            base->str = ft_join_all(base->sign, ft_print_padding(di, flags, 48), base->str);
        else if (((!flags->null && ((flags->width && !flags->prec) || (flags->width > flags->prec))) 
            || (flags->null && flags->prec && flags->width > flags->prec)))
        {
            if (flags->width > flags->prec && flags->prec >= ft_len_numb(di))
                ft_strdel(&base->sign);
            base->str = ft_join_all(ft_print_padding(di, flags, 32), base->sign, base->str);
        }
    }
    else
        put_d_if_minus(di, flags, base);
    ft_putstr(base->str);
    return (ft_strlen(base->str));
 }

void put_d_if_minus(long long int di, t_flags *flags, t_base *base)
{
    int i;
    char *s;

    if (!flags->width && !flags->prec /*&& flags->plus */&& !flags->null)
            base->str = ft_join_all(base->sign, base->str, ft_print_padding(di, flags, 32));
    else if ((flags->width && !flags->prec) || flags->width > flags->prec)
    {
        if (flags->width > flags->prec && flags->width > ft_len_numb(di) && flags->prec > ft_len_numb(di))
        {
            
            i = flags->width;
            flags->width = 0;
            s = ft_strjoin(base->sign, ft_print_padding(di, flags, 48));//ft_join_all(base->sign, ft_print_padding(di, flags, 48), base->str);
            s = ft_strjoin(s, base->str);//ft_join_all(base->sign, ft_print_padding(di, flags, 48), base->str);
            flags->width = i - (flags->prec - ft_len_numb(di));
            flags->prec = 0;  
            ft_strdel(&base->sign);              
            base->str = ft_join_all(base->sign, s, ft_print_padding(di, flags, 32));
        }
        else
            base->str = ft_join_all(base->sign, base->str, ft_print_padding(di, flags, 32));
    }
    else if ((flags->prec && !flags->width) || (flags->prec >= flags->width))
        base->str = ft_join_all(base->sign, ft_print_padding(di, flags, 48), base->str);
}
            

char *put_sign(long long di, t_flags *flags)
{
    char *sign;

    sign = ft_strnew(1);

    if (flags->plus && di >= 0)
        sign[0] = '+';
    else if (di < 0 || ((di < 0) && (flags->width > flags->prec || flags->width < flags->prec)))
        sign[0] = '-';
    else if (flags->space && di > 0 && !flags->width && !flags->prec)
        sign[0] = ' ';
    else if (/*flags->minus && */flags->space && di > 0 && !flags->plus && (!flags->width || flags->width <= flags->prec))//
    {
        sign[0] = ' ';
        if (flags->width > flags->prec)
            flags->width--;
    }
    if (!sign)
        {
            free(sign);
            return NULL;
        }
    return (sign);
}