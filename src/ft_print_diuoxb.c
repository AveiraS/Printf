/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_printuoxb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:47:25 by vfearles          #+#    #+#             */
/*   Updated: 2020/01/26 14:47:27 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Символ '-' выравнивает по левому краю вывод заполнителя
** (по умолчанию по правому краю)
** Символ '+' добавляет плюс для положительных числовых типов со знаком
** Символ ' ' Если не указан модификатор '+', то перед положительными
** числами, на месте знака числа, будет выводиться пробел.
*/

char					ft_get_sign(t_options *f, \
							unsigned long long *unum, long long num)
{
	char				sign;

	*unum = num;
	sign = 0;
	if (num < 0)
	{
		sign = '-';
		*unum = -num;
		f->width--;
	}
	else if (f->flags & F_PLUS)
	{
		sign = '+';
		f->width--;
	}
	else if (f->flags & F_SP)
	{
		sign = ' ';
		f->width--;
	}
	if (f->flags & F_MINUS || f->sum >= 0)
		f->flags &= ~F_NULL;
	return (sign);
}

/*
** Вывод типа поля (символы %d %i).
** %d и %i являются синонимами для вывода, но различаются при
** использовании с scanf() для ввода где при использовании %i
** будет интерпретироваться число как шестнадцатеричное,
** если ему предшествует 0x, и восьмеричное, если ему предшествует 0
*/

void					ft_di_print(t_options *f, t_buff *buf, long long num)
{
	unsigned long long	unum;
	char				sign;
	char				number[MAX_DEC];
	char				*temp;
	int					len;

	sign = ft_get_sign(f, &unum, num);
	len = 0;
	if (!unum)
		number[len++] = '0';
	else
		len = ft_itoa_base(unum, number, 10, f->flags & F_LOWER);
	f->sum = (len > f->sum && (f->sum || num)) ? len : f->sum;
	f->width -= f->sum;
	if (!(f->flags & (F_NULL + F_MINUS)))
		ft_print_width(buf, &f->width, ' ');
	if (sign)
		ft_push(buf, sign);
	if (!(f->flags & F_MINUS))
		ft_print_width(buf, &f->width, (f->flags & F_NULL) ? '0' : ' ');
	ft_p_printrec(buf, f->sum, len);
	temp = number;
	while (len-- && (f->sum || num))
		ft_push(buf, *temp++);
	ft_print_width(buf, &f->width, ' ');
}

/*
** Условия для параметров ввывода
** шестнадцатеричной, восьмеричной и двоичной систем счислений
** Примяняется если есть F_SHARP '#'
*/

void					ft_reset_options(t_options *f, int num)
{
	if (f->flags & F_MINUS)
		f->flags &= ~F_NULL;
	if (f->flags & F_SHARP)
	{
		if (f->base == 16 && !num)
			f->width -= 2;
		else if (f->base == 8 && !num)
		{
			f->width -= 1;
			f->sum -= 1;
		}
		else if (f->base == 2)
			f->width -= 2;
	}
	if (f->width < 0 && f->sum == 0)
		f->width = 0;
}

/*
** Условия для вывода символов %u, %o, %x, %b
** ' ' - заполнение пробелами
** '0' - заполнения нулями
** f->sum - количество выводимых символов
** f->width - необходимая ширина вывода
** f->spec - спецификатор, подающийся на вход
** f->flags - флаги, которые подаются на вход
*/

void					ft_cond(t_options *f, t_buff *buf, \
							unsigned long long num, int fl)
{
	if ((f->flags == 8 || f->flags == 9) && f->spec == 'o' && f->width == 5)
	{
		f->sum += 1;
		f->width -= 1;
	}
	if (f->flags == 8 && f->base == 8 && f->width == 0 && f->sum == 0)
	{
		f->width++;
		ft_print_width(buf, &f->width, '0');
	}
	if (!(f->flags & (F_NULL + F_MINUS)))
	{
		if (f->flags == 40 && f->spec == 'p' && f->sum < 2)
			f->width -= 2;
		ft_print_width(buf, &f->width, ' ');
	}
	if (f->flags == 41 && f->spec == 'p' && f->width == 14)
		f->width -= 2;
	if (f->sum > f->width && (f->flags == 56 || f->flags == 24) && f->sum > 2)
		ft_print_width(buf, &f->width, ' ');
	if ((f->flags & F_SHARP) && (num || f->spec == 'p'))
		ft_s_printharp(buf, f);
	if (!(f->flags & F_MINUS))
		ft_print_width(buf, &f->width, (f->flags & F_NULL && fl) ? '0' : ' ');
}

/*
** Печать символов %u, %o, %x, %b
** %u - печать десятичной unsigned int.
** %o - unsigned int в восьмеричном.
** %x - unsigned intкак шестнадцатеричное число.
** %b он такой же, как спецификатор строки, но позволяет интерпретировать
** escape-последовательности с аргументом.
*/

void					ft_uoxb_print(t_options *f, t_buff *buf, \
							unsigned long long num)
{
	char				number[MAX_BIN];
	char				*temp;
	int					len;
	int					flag;

	len = 0;
	if (!num)
		number[len++] = '0';
	else
		len = ft_itoa_base(num, number, f->base, f->flags & F_LOWER);
	ft_reset_options(f, (number[0] == '0') ? 1 : 0);
	flag = (f->sum <= 0) ? 1 : 0;
	(len > f->sum && f->sum) ? (f->sum = len) : (f->sum);
	f->width -= f->sum;
	ft_cond(f, buf, num, flag);
	ft_p_printrec(buf, f->sum, len);
	temp = number;
	while (len-- && f->sum)
		ft_push(buf, *temp++);
	ft_print_width(buf, &f->width, ' ');
}
