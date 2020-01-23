/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrsize_pf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:01:46 by asmall            #+#    #+#             */
/*   Updated: 2019/12/11 13:08:48 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_wstrsize_pf(wchar_t *wstr)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (wstr[i])
	{
		if (wstr[i] <= 127)
			size += 1;
		else if (wstr[i] >= 128 && wstr[i] <= 2047)
			size += 2;
		else if (wstr[i] >= 2048 && wstr[i] <= 65535)
			size += 3;
		else if (wstr[i] >= 65536 && wstr[i] <= 1114111)
			size += 4;
		i++;
	}
	return (size);
}
