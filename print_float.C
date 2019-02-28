/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.C                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:53:48 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/02/28 18:53:49 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	del_str(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

void	ft_ftoa(double nb, t_base *base, t_flags *fl)
{
	char	*fresh;
	double	tmp;
	double	del;
	int		i;

	i = 1;
	del = 1;
	base->sign = put_sign((long long int)nb, fl);
	nb = (nb < 0) ? -nb : nb;
	tmp = nb;
	while (tmp > 10 && ++i && (tmp /= 10))
		del *= 10;
	fresh = (fl->dot || fl->hash) ? ft_strnew(i + 1) : ft_strnew(i);
	i = 0;
	while (nb >= 1 && (tmp = nb) && (tmp /= del))
	{
		tmp = (long long int)tmp;
		fresh[i++] = (long long int)tmp % 10 + '0';
		tmp *= del;
		nb -= tmp;
		del /= 10;
		if (nb < 10 && fl->dot)
			nb += ((long long int)(nb + 0.5) % 2 == 0) ? (0.5) : (0.49);
	}
	base->str = ft_prec_f(fresh, base, fl, nb);
}

char	*ft_make_str_f(t_base *base, t_flags *fl, char *str, char *fresh)
{
	char *new;
	char *buf;

	buf = print_padding(ft_atoi(fresh), fl, fl->pad);
	if (fl->width)
	{
		if (fl->minus)
			new = join_all(base->sign, str, buf);
		else
			new = (fl->null) ? join_all(base->sign, buf, str)
				: join_all(buf, base->sign, str);
	}
	else
	{
		new = ft_strjoin(base->sign, str);
		del_str(str, base->sign);
	}
	if (fl->dot && fl->hash)
		new[ft_strlen(new)] = '.';
	return (new);
}

char	*ft_prec_f(char *fresh, t_base *base, t_flags *fl, double nb)
{
	char	pad;
	char	*new;
	char	*buf;
	int		i;
	double	j;

	fl->len = ft_strlen(fresh);
	fl->pad = (fl->null && !fl->minus) ? (48) : (32);
	if (fl->dot)
		return (ft_make_str_f(base, fl, fresh, fresh));
	j = 5;
	fresh[fl->len] = '.';
	fl->prec = fl->prec ? fl->prec : 6;
	i = -1;
	while (++i <= fl->prec)
		j /= 10;
	nb += j;
	while (--i)
		nb *= 10;
	new = ft_itoa_unsigned((unsigned long long int)nb);
	buf = ft_strjoin(fresh, new);
	fl->len = ft_strlen(buf);
	del_str(fresh, new);
	fl->prec = 0;
	return (ft_make_str_f(base, fl, buf, fresh));
}
