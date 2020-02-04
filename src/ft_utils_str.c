/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:49:09 by vfearles          #+#    #+#             */
/*   Updated: 2020/01/26 14:49:11 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_strdel(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*new_dst;
	unsigned char	*new_src;

	if (dst <= src)
	{
		new_dst = (unsigned char*)dst;
		new_src = (unsigned char*)src;
		while (len--)
			*new_dst++ = *new_src++;
	}
	else
	{
		new_dst = (unsigned char*)dst + len - 1;
		new_src = (unsigned char*)src + len - 1;
		while (len--)
			*new_dst-- = *new_src--;
	}
	return (dst);
}

int		ft_strnlen(char *str, int n)
{
	int		len;

	len = 0;
	while (n--)
	{
		if (!*str)
			break ;
		len++;
		str++;
	}
	return (len);
}

int		ft_wstrnlen(wchar_t *str, int n)
{
	int		len;
	int		bytes;

	len = 0;
	while (*str && n)
	{
		bytes = 0;
		if (*str <= 0x7F)
			bytes = 1;
		else if (*str <= 0x7FF)
			bytes = 2;
		else if (*str <= 0xFFFF)
			bytes = 3;
		else if (*str <= 0x10FFFF)
			bytes = 4;
		if (n >= bytes || n < 0)
		{
			len += bytes;
			n -= bytes;
			str++;
		}
		else
			break ;
	}
	return (len);
}

int		ft_rstrnlen(char *str, int n)
{
	int		len;

	len = 0;
	while (n--)
	{
		if (!*str)
			break ;
		if ((*str >= 7 && *str <= 13) || *str == '\e')
			len++;
		len++;
		str++;
	}
	return (len);
}
