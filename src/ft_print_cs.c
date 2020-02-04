/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c_prints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:47:16 by asmall            #+#    #+#             */
/*   Updated: 2020/01/26 14:47:17 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Печать спецификатора 'c'
** F_MINUS - флаг '-', F_NULL - флаг '0'
** c - Вывод символа, соответстветсвующего числу указанному в
** аргументе функции. По умолчанию число приводится к типу unsigned char.
*/

void	ft_c_print(t_options *f, t_buff *buf, unsigned char c)
{
	f->width--;
	if (!(f->flags & F_MINUS))
		ft_print_width(buf, &f->width, (f->flags & F_NULL) ? '0' : ' ');
	ft_push(buf, c);
	if (f->flags & F_MINUS)
		ft_print_width(buf, &f->width, ' ');
}

/*
** Условия для побитовой конвертации типа 'c'
*/

int		ft_convert_to_utf8(wchar_t c, char *lc)
{
	int		bytes;

	bytes = 0;
	if (++bytes && c <= 0x7F)
		lc[0] = c;
	else if (++bytes && c <= 0x7FF)
	{
		lc[0] = 0xC0 | (c >> 6);
		lc[1] = 0x80 | (c & 0x3F);
	}
	else if (++bytes && c <= 0xFFFF)
	{
		lc[0] = 0xE0 | (c >> 12);
		lc[1] = 0x80 | ((c >> 6) & 0x3F);
		lc[2] = 0x80 | (c & 0x3F);
	}
	else if (++bytes && c <= 0x10FFFF)
	{
		lc[0] = 0xF0 | (c >> 18);
		lc[1] = 0x80 | ((c >> 12) & 0x3F);
		lc[2] = 0x80 | ((c >> 6) & 0x3F);
		lc[3] = 0x80 | (c & 0x3F);
	}
	return (c <= 0x10FFFF ? bytes : 0);
}

/*
** Печать спецификатора 'c' с модификатором 'l'
** l - Для вывода числа типа long int или unsigned long int.
** c — вывод символа с кодом, соответствующим переданному аргументу;
** переданное число приводится к типу unsigned char (или wchar t,
** если был указан модификатор длины l)
*/

void	ft_lc_print(t_options *f, t_buff *buf, wchar_t c)
{
	int		bytes;
	char	lc[4];
	char	*temp;

	bytes = ft_convert_to_utf8(c, lc);
	f->width -= bytes;
	if (!(f->flags & F_MINUS))
		ft_print_width(buf, &f->width, (f->flags & F_NULL) ? '0' : ' ');
	temp = lc;
	while (bytes--)
		ft_push(buf, *temp++);
	if (f->flags & F_MINUS)
		ft_print_width(buf, &f->width, ' ');
}

/*
** Печать спецификатора 's'
** Вывод строки, на которую ссылается указатель в аргументе функции.
** Строка выводится пока не будет встречен символ конец строки (/0).
*/

void	ft_s_print(t_options *f, t_buff *buf, char *str)
{
	int		len;

	if (!str)
		str = "(null)";
	len = ft_strnlen(str, f->sum);
	f->width -= len;
	if (!(f->flags & F_MINUS))
		ft_print_width(buf, &f->width, (f->flags & F_NULL) ? '0' : ' ');
	while (len--)
		ft_push(buf, *str++);
	if (f->flags & F_MINUS)
		ft_print_width(buf, &f->width, ' ');
}

/*
** Печать спецификатора 's' с модификатором 'l'
** Модификатор l интерпитирует строку как wchar_t*.
** Для функции wprintf строка по умолчанию обрабатывается как wchar_t*.
*/

void	ft_ls_print(t_options *f, t_buff *buf, wchar_t *str)
{
	int		len;
	int		bytes;
	char	lc[4];
	char	*temp;

	if (!str)
		str = L"(null)";
	len = ft_wstrnlen(str, f->sum);
	f->width -= len;
	if (!(f->flags & F_MINUS))
		ft_print_width(buf, &f->width, (f->flags & F_NULL) ? '0' : ' ');
	bytes = 0;
	while (len)
	{
		bytes = ft_convert_to_utf8(*str++, lc);
		len -= bytes;
		temp = lc;
		while (bytes--)
			ft_push(buf, *temp++);
	}
	if (f->flags & F_MINUS)
		ft_print_width(buf, &f->width, ' ');
}
