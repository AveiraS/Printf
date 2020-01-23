/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signed_nbr_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 09:38:26 by asmall            #+#    #+#             */
/*   Updated: 2019/12/14 08:34:56 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_signed_nbr_len(intmax_t value, int base)
{
	int		i;

	i = 0;
	if (value == 0)
		return (1);
	if (value < -9223372036854775807)
		return (20);
	if (value < 0)
	{
		i++;
		value *= -1;
	}
	while (value > 0)
	{
		value /= base;
		i++;
	}
	return (i);
}

int		ft_unsigned_nbr_len(uintmax_t value, int base)
{
	int		i;

	i = 0;
	if (value == 0)
		return (1);
	while (value > 0)
	{
		value /= base;
		i++;
	}
	return (i);
}
