/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 10:02:15 by asmall            #+#    #+#             */
/*   Updated: 2019/12/14 09:46:54 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_percent_sign_left_align(t_struct *f)
{
	f->len += write(f->fd, "%", 1);
	while (f->width > 1)
	{
		f->len += write(f->fd, " ", 1);
		f->width--;
	}
}

static void	ft_print_percent_sign_right_align(t_struct *f)
{
	while (f->width > 1)
	{
		if (f->zero)
			f->len += write(f->fd, "0", 1);
		else
			f->len += write(f->fd, " ", 1);
		f->width--;
	}
	f->len += write(f->fd, "%", 1);
}

void		ft_print_percent_sign(char type, t_struct *f)
{
	if (type == '%')
	{
		if (f->minus)
			ft_print_percent_sign_left_align(f);
		else
			ft_print_percent_sign_right_align(f);
	}
}
