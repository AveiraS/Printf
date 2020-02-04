/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_f_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:47:47 by vfearles          #+#    #+#             */
/*   Updated: 2020/01/26 14:47:49 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Условия для конвертации флатов с его длиной
*/

void		ft_round(char *number, int len)
{
	int		count;

	count = len;
	if (number[len] >= '5')
	{
		number[len--] = '\0';
		while (len >= 0)
		{
			if (number[len] == '9')
				number[len] = '0';
			else if (number[len] != '.')
				break ;
			len--;
		}
		if (len >= 0)
			number[len] += 1;
		else
		{
			ft_memmove(number + 1, number, count);
			number[0] = '1';
		}
	}
	else
		number[len] = '\0';
}

/*
** Заполнение нулями флатов и плавающей точки
*/

char		*ft_get_fnum(t_fnum *fnum, int sum, int ilen, t_options *f)
{
	char	*number;
	int		i;
	char	*ipoint;
	char	*fpoint;

	sum += 2;
	number = (char*)malloc(ilen + sum + 1);
	ipoint = fnum->ipoint ? fnum->ipoint : "0";
	fpoint = fnum->fpoint ? fnum->fpoint : "0";
	i = 0;
	while (i < ilen)
		number[i++] = *ipoint++;
	number[i++] = '.';
	while (fnum->zero-- && (i < ilen + sum))
		number[i++] = '0';
	while (*fpoint && (i < ilen + sum))
		number[i++] = *fpoint++;
	while (i < ilen + sum)
		number[i++] = '0';
	ft_round(number, i - 1);
	number[i - 2] = (sum == 2 && f->flags != 8 && f->flags != 9
		&& f->flags != 11 && f->flags != 13) ? '\0' : number[i - 2];
	return (number);
}

/*
** Запоминание флагов на вывод и вычисление ширины
*/

char		ft_get_sign_f(t_options *f, char sign)
{
	char	res;

	res = 0;
	if (sign)
	{
		res = '-';
		f->width--;
	}
	else if (f->flags & F_PLUS)
	{
		res = '+';
		f->width--;
	}
	else if (f->flags & F_SP)
	{
		res = ' ';
		f->width--;
	}
	(f->flags & F_MINUS) ? (f->flags &= ~F_NULL) : 1;
	(f->sum == -1) ? (f->sum = 6) : 1;
	return (res);
}

/*
** Печать спецификатора 'f'
** Заполнение нулями и/или пробелами ширины.
** f - вывод числа с плавающей точкой
** По умолчанию выводится число с точностью 6,
** если число по модулю меньше единицы, то пред десятично
** точкой выводится ноль, знак указывается только для
** отрицательных чисел, с правым выравниванием.
** Размер по умолчанию sizeof( double ).
*/

void		ft_f_print(t_options *f, t_buff *buf, t_fnum *fnum)
{
	int		len;
	char	sign;
	char	*number;
	char	*temp;

	sign = ft_get_sign_f(f, fnum->sign);
	len = 0;
	(!fnum->ipoint) ? (len++) : (len = ft_strnlen(fnum->ipoint, -1));
	if (f->flags == 9 || f->flags == 11 || f->flags == 13)
		f->width -= f->sum ? f->sum + len + 1 : len + 1;
	else
		f->width -= f->sum ? f->sum + len + 1 : len;
	if (!(f->flags & (F_NULL + F_MINUS)))
		ft_print_width(buf, &f->width, ' ');
	(sign) ? ft_push(buf, sign) : 1;
	if (!(f->flags & F_MINUS))
		ft_print_width(buf, &f->width, (f->flags & F_NULL) ? '0' : ' ');
	number = ft_get_fnum(fnum, f->sum, len, f);
	temp = number;
	while (*temp)
		ft_push(buf, *temp++);
	ft_strdel(&number);
	ft_print_width(buf, &f->width, ' ');
}
