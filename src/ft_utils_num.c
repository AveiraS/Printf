/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:48:55 by asmall            #+#    #+#             */
/*   Updated: 2020/01/26 14:48:57 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi(const char *str)
{
	long		res;
	short int	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (res * 10 / 10 != res || res * 10 + (*str - '0') < 0)
		{
			if (sign < 0)
				return (0);
			return (-1);
		}
		res = res * 10 + (*str++ - '0');
	}
	return ((int)(res * sign));
}

int		ft_unumlen(unsigned long long num, int base)
{
	int		len;

	len = 0;
	while (num /= base)
		len++;
	return (len + 1);
}

int		ft_itoa_base(unsigned long long num, char *str, int base, char lower)
{
	char	*digits;
	int		len;

	digits = "0123456789ABCDEF";
	len = ft_unumlen(num, base);
	str += len;
	*str-- = '\0';
	while (num)
	{
		*str-- = (digits[num % base] | lower);
		num /= base;
	}
	return (len);
}

/*
** Возведение в степень
*/

int		ft_power(int base, int power)
{
	int		res;

	res = 1;
	while (power--)
		res *= base;
	return (res);
}

/*
** 1ULL - Эти буквы изменяют литерал 1 и делают его типа unsigned long long.
** & (Побитовое И (AND)), << (Побитовый сдвиг влево)
*/

int		ft_get_zero(unsigned long long num, int shift, char *fpoint)
{
	int		len;
	int		zero;
	int		power;

	len = ft_strnlen(fpoint, -1);
	zero = 0;
	power = 0;
	while (power < 64)
	{
		if (num & (1ULL << power))
		{
			zero = 64 - power + shift - len;
			break ;
		}
		power++;
	}
	return (zero);
}
