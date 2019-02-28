/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func_nb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:31:00 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/02/28 18:31:41 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int						ft_len_nb(long long int nb)
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

long long int			cast_di(t_base *base, t_flags *fl)
{
	if (fl->j)
		return (va_arg(base->ap, intmax_t));
	else if (fl->z)
		return (va_arg(base->ap, size_t));
	else if (fl->ll || fl->con == 'D')
		return (va_arg(base->ap, long long int));
	else if (fl->h)
		return ((short)va_arg(base->ap, int));
	else if (fl->hh)
		return ((signed char)va_arg(base->ap, int));
	else if (fl->l)
		return (va_arg(base->ap, long int));
	// else if (fl->L)
	//   di = va_arg(base->ap, );
	else
		return (va_arg(base->ap, int));
}

unsigned long long int	cast_ou(t_base *base, t_flags *fl)
{
	if (fl->j)
		return (va_arg(base->ap, intmax_t));
	else if (fl->l)
		return (va_arg(base->ap, unsigned long int));
	else if (fl->z)
		return (va_arg(base->ap, size_t));
	else if (fl->ll|| fl->con == 'O' || fl->con == 'U')
		return (va_arg(base->ap, unsigned long long int));
	else if (fl->h)
		return ((unsigned short)va_arg(base->ap, unsigned int));
	else if (fl->hh)
		return ((unsigned char)va_arg(base->ap, unsigned int));

	// else if (fl->L)
	//   di = va_arg(base->ap, );
	else
		return (va_arg(base->ap, unsigned int));
}

char					*join_all(char *s1, char *s2, char *s3)
{
	char	*fresh;
	int		i;
	int a;
	int b;
	int c;
	a = 0;
	b = 0;
	c = 0;
	fresh = NULL;
   if (s1)
	   a = ft_strlen(s1);
	if (s2)
		b = ft_strlen(s2);
	if (s3)
		c = ft_strlen(s3);
	if (!s1 && !s2 && !s3)
		return (NULL);
	i =  a + b + c + 1;
	if (!(fresh = (char *)malloc(sizeof(char) * i)))
		return (NULL);
	if (fresh == NULL)
		return (NULL);

	if (s1)
		ft_strcpy(fresh, s1);
	if (s2)
		(s1) ? ft_strcat(fresh, s2) : ft_strcpy(fresh, s2);
   if (s3)
		(s1 || s2) ? ft_strcat(fresh, s3) : ft_strcpy(fresh, s3);
	if (s1)
	  free(s1);
	if (s2)
	   	free(s2);
	if (s3)
		ft_strdel(&s3);
	return (fresh);
}

char					*hash_x_func(t_flags *fl, char *str, long long int x)
{
	char *buff;

	if (fl->con == 'x')
		buff = (x == 0 && fl->dot) ? ft_strdup("0x") : ft_strjoin("0x", str);
	else if (fl->con == 'X')
		buff = (x == 0 && fl->dot) ? ft_strdup("0X") : ft_strjoin("0X", str);
	free(str);
	return (buff);
}
