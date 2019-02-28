#include "ft_printf.h"

int print_con_scpf(t_base *base, t_flags *fl)
{
	double f;

	if (fl->con == 'f' || fl->con == 'F')
	{
	   f = va_arg(base->ap, double);
		ft_ftoa(f, base, fl);
		ft_putstr(base->str);
		return (ft_strlen(base->str));
	}
	if (fl->con == 's' || fl->con == 'S')
		return (ft_printing_s(base, fl));
	if (fl->con == 'c' || fl->con == 'C')
		return (ft_printing_c(base, fl));
	else
		return (ft_printing_p(base, fl));
	return 0;
}

int print_con_di(t_base *base, t_flags *fl)
{
	long long int di;

	di = cast_di(base, fl);
	fl->plus = (di < 0) ? 0 : fl->plus;
	base->str = (di < 0) ? ft_itoa_signed(-di) : ft_itoa_signed(di);
	fl->len = (di < 0) ? (ft_strlen(base->str) + 1) : (ft_strlen(base->str));
	base->sign = put_sign(di, fl);
	if (di == 0 && fl->dot && !fl->width)
	{
		free(base->sign);
		return (0);
	}
	if (!fl->minus)
		put_dio_if_not_minus(di, fl, base);
	else
		put_dio_if_minus(di, fl, base);
	ft_putstr(base->str);
	return (ft_strlen(base->str));
}

int print_con_o(t_base *base, t_flags *fl)
{
	unsigned long long int o;

	o = cast_ou(base, fl);
	base->str = ft_itoa_base(o, 8, fl);
	base->sign = NULL;
	fl->len = (ft_strlen(base->str));
	if (o == 0 && fl->dot && !fl->width && !fl->hash)
		return 0;
	if (fl->hash)
	{
		if (!fl->prec && !fl->null)
			fl->prec = (o == 0) ? (fl->len) : (fl->len + 1);
	}
	if (!fl->minus)
		put_dio_if_not_minus(o, fl, base);
	else
		put_dio_if_minus(o, fl, base);
	ft_putstr(base->str);
	return (ft_strlen(base->str));
}

int print_con_u(t_base *base, t_flags *fl)
{
	unsigned long long int u;

	u = cast_ou(base, fl);
	base->str = ft_itoa_unsigned(u);
	base->sign = NULL;
	fl->len = (ft_strlen(base->str));
	if (u == 0 && fl->dot && !fl->width)
		return 0;
	if (!fl->minus)
		put_dio_if_not_minus(u, fl, base);
	else
		put_dio_if_minus(u, fl, base);
	ft_putstr(base->str);
	return (ft_strlen(base->str));
}

int print_con_xX(t_base *base, t_flags *fl)
{
	unsigned long long int x;

	x = cast_ou(base, fl);
	base->str = ft_itoa_base(x, 16, fl);
	base->sign = NULL;
	fl->len = (ft_strlen(base->str));
	if (x == 0 && fl->dot && !fl->width)
		return 0;
	if (fl->hash && fl->width)
		fl->width -= 2;

	if (x != 0 && fl->hash && (!fl->null || fl->minus) && !fl->prec)
		base->str = hash_x_func(fl, base->str, x);

	if (!fl->minus)
		put_dio_if_not_minus(x, fl, base);
	else
		put_dio_if_minus(x, fl, base);
	if (x != 0 && fl->hash && fl->prec && (!fl->null || fl->minus))
		base->str = hash_x_func(fl, base->str, x);
	ft_putstr(base->str);
	return (ft_strlen(base->str));
}
