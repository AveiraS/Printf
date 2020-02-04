/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_e_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:47:36 by asmall            #+#    #+#             */
/*   Updated: 2020/01/26 14:47:38 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_set_exp(char *number, t_fnum *fnum, char spec)
{
	int		numlen;

	*number++ = spec;
	*number++ = (fnum->fpoint && !fnum->ipoint) ? '-' : '+';
	if (fnum->fpoint && !fnum->ipoint)
	{
		if ((numlen = ft_unumlen(fnum->zero, 10)) < 2)
			*number++ = '0';
		number += ft_itoa_base(fnum->zero + 1, number, 10, 0);
	}
	else
	{
		if (!fnum->ipoint || ((numlen = ft_strnlen(fnum->ipoint, -1)) < 11))
			*number++ = '0';
		if (!fnum->ipoint || numlen == 1)
			*number++ = '0';
		else
			number += ft_itoa_base(numlen - 1, number, 10, 0);
	}
	*number = '\0';
}

int		ft_get_first_enum(char *number, char **ipoint, char **fpoint)
{
	int		i;

	i = 0;
	if (!*ipoint && !*fpoint)
		number[i++] = '0';
	else
		number[i++] = *ipoint ? *(*ipoint)++ : *(*fpoint)++;
	number[i++] = '.';
	return (i);
}

char	*ft_get_enum(t_fnum *fnum, int sum, int ilen, char spec)
{
	int		i;
	int		zero;
	char	*ipoint;
	char	*fpoint;
	char	*number;

	number = (char*)malloc(ilen + sum + 2);
	ipoint = fnum->ipoint;
	fpoint = fnum->fpoint;
	zero = fnum->zero;
	i = ft_get_first_enum(number, &ipoint, &fpoint);
	while (ipoint && *ipoint && (i < sum + 1))
		number[i++] = *ipoint++;
	while (ipoint && zero-- && (i < sum + 1))
		number[i++] = '0';
	while (fpoint && *fpoint && (i < sum + 1))
		number[i++] = *fpoint++;
	while (i < sum + 1)
		number[i++] = '0';
	ft_round(number, --i);
	i = sum == 2 ? --i : i;
	ft_set_exp(&number[i], fnum, spec);
	return (number);
}

/*
** Печать спецификатора 'e' для бонусной части заданий
** Вывод числа с плавающей точкой в экспоненциальной форме записи
** По умолчанию выводится число с точностью 6, если число по
** модулю меньше еденицы, то пред десятично точкой выводится ноль,
** знак указывается только для отрицательных чисел, с правым выравниванием.
** После символа "e" (или "E") всегда выводится две цифры
** (они равны 0, если аргумент равен 0).
*/

void	ft_e_print(t_options *f, t_buff *buf, t_fnum *fnum)
{
	char	sign;
	char	*number;
	char	*temp;
	int		len;
	int		numlen;

	sign = ft_get_sign_f(f, fnum->sign);
	numlen = ft_unumlen(fnum->zero + 1, 10);
	len = numlen < 2 ? 5 : numlen + 3;
	f->width -= f->sum ? f->sum + len + 1 : len;
	if (!(f->flags & (F_NULL + F_MINUS)))
		ft_print_width(buf, &f->width, ' ');
	if (sign)
		ft_push(buf, sign);
	if (!(f->flags & F_MINUS))
		ft_print_width(buf, &f->width, (f->flags & F_NULL) ? '0' : ' ');
	number = ft_get_enum(fnum, f->sum + 2, len, f->spec);
	temp = number;
	while (*temp)
		ft_push(buf, *temp++);
	ft_strdel(&number);
	ft_print_width(buf, &f->width, ' ');
}
