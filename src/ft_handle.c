/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:48:21 by asmall            #+#    #+#             */
/*   Updated: 2020/01/26 14:48:23 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Ищем необходимый спецификатор, подающийся на вход
** c, C - Вывод символа, соответстветсвующего числу
** указанному в аргументе функции.
** s - Вывод строки, на которую ссылается указатель
** в аргументе функции printf. Строка выводится пока
** не будет встречен символ конец строки (/0).
** S - Аналогичен преобразованию s с модификатором l (ls).
** f, F - Вывод числа с плавающей точкой. По умолчанию
** выводится число с точностью 6, если число по модулю меньше
** единицы, то пред десятично точкой выводится ноль.
** e, E - Вывод числа с плавающей точкой в экспоненциальной
** форме записи. По умолчанию выводится число с точностью 6,
** если число по модулю меньше еденицы, то пред десятично
** точкой выводится ноль.
** p - Вывод указателя. Результат ввода зависит от архитектуры
** и используемого компилятрора.
** r - вывод строки с непечатными символами.
** k - печать даты в любом формате ISO.
*/

int		ft_handle_other(t_options *f, t_buff *buf, va_list ap)
{
	if (f->spec == 'c' && f->length != LEN_L)
		ft_c_print(f, buf, (unsigned char)va_arg(ap, int));
	else if (f->spec == 'C' || (f->spec == 'c' && f->length == LEN_L))
		ft_lc_print(f, buf, (wchar_t)va_arg(ap, wint_t));
	else if (f->spec == 's' && f->length != LEN_L)
		ft_s_print(f, buf, va_arg(ap, char*));
	else if (f->spec == 'S' || (f->spec == 's' && f->length == LEN_L))
		ft_ls_print(f, buf, va_arg(ap, wchar_t*));
	else if (f->spec == 'f' && f->length == LEN_LL)
		ft_parse_lfnum(f, buf, va_arg(ap, long double), ft_f_print);
	else if (f->spec == 'f' || f->spec == 'F')
		ft_parse_fnum(f, buf, va_arg(ap, double), ft_f_print);
	else if (f->spec == 'e' && f->length == LEN_LL)
		ft_parse_lfnum(f, buf, va_arg(ap, long double), ft_e_print);
	else if (f->spec == 'e' || f->spec == 'E')
		ft_parse_fnum(f, buf, va_arg(ap, double), ft_e_print);
	else if (f->spec == 'p')
		ft_p_print(f, buf, va_arg(ap, void*));
	else if (f->spec == 'r')
		ft_r_print(f, buf, va_arg(ap, char*));
	else if (f->spec == 'k')
		ft_k_print(f, buf, va_arg(ap, unsigned long long));
	else
		return (0);
	return (1);
}

/*
** Ищем спецификатор, подающийся на вход
** d, i - Вывод целого числа со знаком в десятичной.
** u, U - Вывод целого числа без знака в десятичной.
** o, O - Вывод целого числа без знака в восьмеричной.
** x, X - Вывод целого числа без знака в шестнадцетеричной.
** b - он такой же, как спецификатор строки, но позволяет
** интерпретировать escape-последовательности с аргументом.
** f->base битовая платформа
*/

int		ft_handle_num(t_options *f, t_buff *buf, va_list ap)
{
	if (f->spec == 'd' || f->spec == 'i' || f->spec == 'D')
		ft_parse_num(f, buf, va_arg(ap, long long));
	else if (f->spec == 'u' || f->spec == 'U')
		ft_parse_unum(f, buf, va_arg(ap, unsigned long long));
	else if (f->spec == 'o' || f->spec == 'O')
	{
		f->base = 8;
		ft_parse_unum(f, buf, va_arg(ap, unsigned long long));
	}
	else if (f->spec == 'x' || f->spec == 'X')
	{
		f->base = 16;
		if (f->spec == 'x')
			f->flags |= F_LOWER;
		ft_parse_unum(f, buf, va_arg(ap, unsigned long long));
	}
	else if (f->spec == 'b')
	{
		f->base = 2;
		ft_parse_unum(f, buf, va_arg(ap, unsigned long long));
	}
	else
		return (0);
	return (1);
}

void	ft_handle_spec(t_options *f, t_buff *buf, va_list ap)
{
	if (ft_handle_num(f, buf, ap))
		return ;
	else if (ft_handle_other(f, buf, ap))
		return ;
	else if (f->spec)
		ft_r_printand(f, buf);
}
