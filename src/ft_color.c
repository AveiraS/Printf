/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 13:01:28 by asmall            #+#    #+#             */
/*   Updated: 2020/02/01 13:01:55 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int			ft_color(t_buff *buf, const char **form, t_options *f)
{
	int		len;

	f->color = 0;
	if (**form == '{')
	{
		if (!ft_strncmp(*form, "{red}", (len = 5)))
			f->color = PF_RED;
		else if (!ft_strncmp(*form, "{green}", (len = 7)))
			f->color = PF_GREEN;
		else if (!ft_strncmp(*form, "{yellow}", (len = 8)))
			f->color = PF_YELLOW;
		else if (!ft_strncmp(*form, "{blue}", (len = 6)))
			f->color = PF_BLUE;
		else if (!ft_strncmp(*form, "{cyan}", (len = 6)))
			f->color = PF_CYAN;
		else if (!ft_strncmp(*form, "{eoc}", (len = 5)))
		{
			f->color = PF_EOC;
			ft_put_color(buf, f);
		}
		else if (!(len = 0))
			f->color = 0;
		*form += len;
	}
	return ((f->color) ? 1 : 0);
}

void		ft_put_color(t_buff *buf, t_options *f)
{
	char	*str;

	str = "\0";
	if (f->color == 11)
		str = "\033[31m";
	else if (f->color == 22)
		str = "\033[32m";
	else if (f->color == 33)
		str = "\033[33m";
	else if (f->color == 44)
		str = "\033[34m";
	else if (f->color == 55)
		str = "\033[35m";
	else if (f->color == 66)
		str = "\033[36m";
	else if (f->color == 77)
		str = "\033[0m";
	while (*str)
	{
		ft_push(buf, *str);
		str++;
	}
}
