/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_nums.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:47:05 by vfearles          #+#    #+#             */
/*   Updated: 2020/01/26 14:47:07 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Парсуем спецификатор 'D' по длине f->length с модификатром
** D - вывод целого числа со знаком в десятичной систем счисления.
** По умолчанию выводится число размером sizeof( int ),
** с правым выравниванием, указанием знака только для отрицательных чисел.
*/

void	ft_parse_num(t_options *f, t_buff *buf, long long num)
{
	if (f->spec == 'D')
		ft_di_print(f, buf, (long)num);
	else if (f->length == 0)
		ft_di_print(f, buf, (int)num);
	else if (f->length == LEN_HH)
		ft_di_print(f, buf, (char)num);
	else if (f->length == LEN_H)
		ft_di_print(f, buf, (short)num);
	else if (f->length == LEN_L)
		ft_di_print(f, buf, (long)num);
	else if (f->length == LEN_LL)
		ft_di_print(f, buf, (long long)num);
	else if (f->length == LEN_J)
		ft_di_print(f, buf, (intmax_t)num);
	else if (f->length == LEN_Z)
		ft_di_print(f, buf, (ssize_t)num);
}

/*
** Парсуем спецификатор 'U' и 'O' по длине f->length с модификатором
** U - Вывод целого числа без знака в десятичной систем счисления.
** По умолчанию выводится число размером sizeof( int ), с правым выравниванием.
** O - Вывод целого числа без знака в восьмеричной систем счисления.
** По умолчанию выводится число размером sizeof( int ), с правым выравниванием.
*/

void	ft_parse_unum(t_options *f, t_buff *buf, unsigned long long unum)
{
	if (f->spec == 'U' || f->spec == 'O')
		ft_uoxb_print(f, buf, (unsigned long)unum);
	else if (f->length == 0)
		ft_uoxb_print(f, buf, (unsigned int)unum);
	else if (f->length == LEN_HH)
		ft_uoxb_print(f, buf, (unsigned char)unum);
	else if (f->length == LEN_H)
		ft_uoxb_print(f, buf, (unsigned short)unum);
	else if (f->length == LEN_L)
		ft_uoxb_print(f, buf, (unsigned long)unum);
	else if (f->length == LEN_LL)
		ft_uoxb_print(f, buf, (unsigned long long)unum);
	else if (f->length == LEN_J)
		ft_uoxb_print(f, buf, (uintmax_t)unum);
	else if (f->length == LEN_Z)
		ft_uoxb_print(f, buf, (size_t)unum);
}

/*
** Парсуем флоты
** 0x1FFFFFFFFFFFFF - для точного представления цифр с плавающей точкой
** 1ULL - эти буквы изменяют литерал 1 и делают его типа unsigned long long.
** | (Побитовое ИЛИ (OR)), << (Побитовый сдвиг влево),
** >> (Побитовый сдвиг вправо).
** %f - Вывод числа с плавающей точкой в виде [-]dddd.ddd.
** По умолчанию выводится число с точностью 6,
** если число по модулю меньше единицы, то пред десятично
** точкой выводится ноль, знак указывается только для отрицательных
** чисел, с правым выравниванием. Размер по умолчанию sizeof(double).
** sign - знак, если число положительное - 0, отрицательное - 1.
** man - мантисса — это, по сути, число, записанное без точки.
** Для двойной точности мы используем больше битов: 1 бит под знак,
** 11 бит экспоненты, 52 бита мантиссы
** Мантисса записывается в двоичном виде,
** и отбрасывается целая часть, заведомо равная 1,
** поэтому мантисса на один бит длиннее, чем в она хранится в двоичном виде.
** exp - экспонента — это степень, в которую нужно возвести некое число N (как
** правило, N = 2), чтобы при перемножении на мантиссу получить искомое число.
** Это обычное бинарное представление целого числа, в которое нужно возвести 10,
** чтобы при перемножении на мантиссу в нормализованном виде получить исходное
** число. Только ввели смещение, которое нужно вычитать из бинарного
** представления, чтобы получить искомую степень десятки.
** Экспонента смещается для упрощения операции сравнения, то есть для одинарной
** точности берется значение 127, а для двойной 1023.
** ipoint - числа до точки, fpoint - числа после точки
*/

void	ft_parse_fnum(t_options *f, t_buff *buf, double num, \
				void (*ft_print)(t_options*, t_buff*, t_fnum*))
{
	t_fnum	fnum;

	fnum.num.f = num;
	fnum.sign = (fnum.num.ll & (1ULL << 63)) ? 1 : 0;
	fnum.exp = ((fnum.num.ll >> 52) & 0x7FF) - 1023;
	fnum.man = (fnum.num.ll & 0x1FFFFFFFFFFFFF) | 0x10000000000000;
	fnum.ipoint = NULL;
	fnum.fpoint = NULL;
	fnum.zero = 0;
	if (fnum.exp >= 52)
		fnum.ipoint = ft_get_part(fnum.man, fnum.exp - 52, ft_get_ip);
	else if (fnum.exp >= 0)
	{
		fnum.ipoint = ft_get_part(fnum.man >> (52 - fnum.exp), 0, ft_get_ip);
		fnum.fpoint = ft_get_part(fnum.man << (fnum.exp + 12), 0, ft_get_fp);
		fnum.zero = ft_get_zero(fnum.man << (fnum.exp + 12), 0, fnum.fpoint);
	}
	else if (fnum.exp >= -1022)
	{
		fnum.fpoint = ft_get_part(fnum.man << 11, -(fnum.exp + 1), ft_get_fp);
		fnum.zero = ft_get_zero(fnum.man << 11, -(fnum.exp + 1), fnum.fpoint);
	}
	ft_print(f, buf, &fnum);
	ft_strdel(&fnum.ipoint);
	ft_strdel(&fnum.fpoint);
}

/*
** Парсуем флоты %f с модификатором l и ll
** l - Для вывода числа типа long int или unsigned long int.
** Или для явного преобразования при выводе целочисленного
** числа к типу long int или unsigned long int.
** ll - Для вывода числа типа long long int или unsigned
** long long int. Или для явного преобразования при выводе
** целочисленного числа к типу long long int или unsigned long long int
** & (Побитовое И (AND))
** 1ULL - эти буквы изменяют литерал 1 и делают его типа unsigned long long.
** Маска 0x7FFF - если значения шириной 16 бит, при добавлении
** битового значения & результатом будет сохранение неизменными
** всех битов соответствующих биту «1» в маске
*/

void	ft_parse_lfnum(t_options *f, t_buff *buf, long double num, \
				void (*ft_print)(t_options*, t_buff*, t_fnum*))
{
	t_fnum	fnum;

	fnum.num.lf = num;
	fnum.sign = (*(&fnum.num.ll + 1) & (1ULL << 15)) ? 1 : 0;
	fnum.exp = (*(&fnum.num.ll + 1) & 0x7FFF) - 16383;
	fnum.man = fnum.num.ll;
	fnum.ipoint = NULL;
	fnum.fpoint = NULL;
	fnum.zero = 0;
	if (fnum.exp >= 64)
		fnum.ipoint = ft_get_part(fnum.man, fnum.exp - 63, ft_get_ip);
	else if (fnum.exp >= 0)
	{
		fnum.ipoint = ft_get_part(fnum.man >> (63 - fnum.exp), 0, ft_get_ip);
		fnum.fpoint = ft_get_part(fnum.man << (fnum.exp + 1), 0, ft_get_fp);
		fnum.zero = ft_get_zero(fnum.man << (fnum.exp + 1), 0, fnum.fpoint);
	}
	else if (fnum.exp >= -16382)
	{
		fnum.fpoint = ft_get_part(fnum.man, -(fnum.exp + 1), ft_get_fp);
		fnum.zero = ft_get_zero(fnum.man, -(fnum.exp + 1), fnum.fpoint);
	}
	ft_print(f, buf, &fnum);
	ft_strdel(&fnum.ipoint);
	ft_strdel(&fnum.fpoint);
}
