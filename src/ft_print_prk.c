/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_printrk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:48:08 by vfearles          #+#    #+#             */
/*   Updated: 2020/01/26 14:48:10 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Печать спецификатора 'p'
** p - Вывод указателя.
** Результат ввода зависит от архитектуры и используемого компилятрора.
** На основе 16 битной платформы
*/

void	ft_p_print(t_options *f, t_buff *buf, void *pointer)
{
	unsigned long long	addr;

	addr = (unsigned long long)pointer;
	f->base = 16;
	f->flags |= F_LOWER;
	f->flags |= F_SHARP;
	ft_uoxb_print(f, buf, addr);
}

void	ft_r_printand(t_options *f, t_buff *buf)
{
	f->width--;
	if (!(f->flags & F_MINUS))
		ft_print_width(buf, &f->width, (f->flags & F_NULL) ? '0' : ' ');
	ft_push(buf, f->spec);
	if (f->flags & F_MINUS)
		ft_print_width(buf, &f->width, ' ');
}

/*
** Печать спецификатора 'r' для бонусной части заданий
** r - вывод строки с непечатными символами
*/

void	ft_r_print(t_options *f, t_buff *buf, char *str)
{
	int		len;

	if (!str)
		str = "(null)";
	len = ft_rstrnlen(str, f->sum);
	f->width -= len;
	if (!(f->flags & F_MINUS))
		ft_print_width(buf, &f->width, (f->flags & F_NULL) ? '0' : ' ');
	while (len--)
	{
		if ((*str >= 7 && *str <= 13) || *str == '\e')
			ft_push(buf, '\\');
		ft_push(buf, *str++);
	}
	if (f->flags & F_MINUS)
		ft_print_width(buf, &f->width, ' ');
}

/*
** Инициализация структуры для печати спецификатора 'k'.
** k - печать даты в любом формате ISO.
** Для бонусной части заданий.
*/

void	ft_reset_opt_k(t_options *f)
{
	f->flags = 0;
	f->width = -1;
	f->sum = 2;
	f->base = 10;
}

/*
** Печать спецификатора 'k'
** k - печать даты в любом формате ISO.
** Деление на 60 необходимо для перевода int при вводе в вывод
*/

void	ft_k_print(t_options *f, t_buff *buf, unsigned long long unum)
{
	int		sec;
	int		minutes;
	int		hours;

	sec = unum % 60;
	unum /= 60;
	minutes = unum % 60;
	unum /= 60;
	hours = unum;
	ft_reset_opt_k(f);
	if (hours)
		ft_di_print(f, buf, hours);
	if (minutes || hours)
	{
		if (hours)
			ft_push(buf, ':');
		ft_di_print(f, buf, minutes);
	}
	if (sec || minutes || hours)
	{
		if (minutes || hours)
			ft_push(buf, ':');
		ft_di_print(f, buf, sec);
	}
}
