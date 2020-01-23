/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_decimal_padding.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:31:56 by asmall            #+#    #+#             */
/*   Updated: 2020/01/21 16:58:22 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_padding_left_align(int nbrlen, t_struct *f)
{
	while (f->width >= nbrlen)
	{
		f->len += write(f->fd, " ", 1);
		f->width--;
	}
}

/*
** 
*/

void	ft_padding_right_align(int nbrlen, int n, t_struct *f)
{
	if (!f->precision_specified)
		while (f->width-- > nbrlen)
		{
			if (f->zero)
				f->len += write(f->fd, "0", 1);
			else
				f->len += write(f->fd, " ", 1);
		}
	else
	{
		if ((f->plus && n == 0)||(f->precision > nbrlen && n == 1))
			f->width--;
		(f->precision < nbrlen && !f->zero && n == 0) ? (f->precision = nbrlen) : (f->precision);
		while (f->width > f->precision && f->width > nbrlen)
		{	
			f->width--;
			if (f->zero && f->width != f->precision && f->width < nbrlen)
				f->len += write(f->fd, "0", 1);
			else
				f->len += write(f->fd, " ", 1);
		}
	}
}
