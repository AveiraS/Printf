/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:46:31 by vfearles          #+#    #+#             */
/*   Updated: 2020/01/26 14:46:35 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_reset_bigint(t_bigint *bigint)
{
	int		i;

	i = 0;
	while (i < MAX_BIGINT)
		bigint->num[i++] = 0;
	bigint->size = 0;
}

/*
** Функция заполняет массив и запоминает значения до точки.
*/

void		ft_set_bigint(t_bigint *bigint, int power, int base)
{
	int		num;
	int		count;
	int		last_pow;
	int		temp;

	count = 0;
	num = ft_power(base, MAX_POWER);
	if (power >= MAX_POWER)
		count = power / MAX_POWER;
	last_pow = power % MAX_POWER;
	temp = count;
	if (count)
	{
		bigint->num[0] += num;
		count--;
	}
	else
		bigint->num[0] += ft_power(base, last_pow);
	bigint->size = 1;
	while (count--)
		ft_big_int_multi(bigint, num);
	if (temp)
		ft_big_int_multi(bigint, ft_power(base, last_pow));
}

t_bigint	ft_get_fp(unsigned long long num, int shift)
{
	t_bigint	res_bigint;
	t_bigint	temp_bigint;
	t_bigint	exp_bigint;
	int			power;

	power = 0;
	ft_reset_bigint(&res_bigint);
	ft_reset_bigint(&temp_bigint);
	ft_reset_bigint(&exp_bigint);
	exp_bigint.num[exp_bigint.size++] = 1;
	while (power < 64)
	{
		if (num & (1ULL << power))
		{
			ft_set_bigint(&temp_bigint, 64 - power + shift, 5);
			temp_bigint = ft_bigint_multi(&temp_bigint, &exp_bigint);
			ft_big_int_multi(&exp_bigint, 10);
			ft_bigint_sum(&res_bigint, &temp_bigint);
			ft_reset_bigint(&temp_bigint);
		}
		else if (!(exp_bigint.num[0] % 10))
			ft_big_int_multi(&exp_bigint, 10);
		power++;
	}
	return (res_bigint);
}

/*
** функция заполняет массив до точки
** ft_reset_bigint(&res_bigint): заполнение массивов '0'
*/

t_bigint	ft_get_ip(unsigned long long num, int shift)
{
	t_bigint	res_bigint;
	t_bigint	temp_bigint;
	int			power;

	power = 0;
	ft_reset_bigint(&res_bigint);
	ft_reset_bigint(&temp_bigint);
	while (power < 64)
	{
		if (num & (1ULL << power))
		{
			ft_set_bigint(&temp_bigint, shift + power, 2);
			ft_bigint_sum(&res_bigint, &temp_bigint);
			ft_reset_bigint(&temp_bigint);
		}
		power++;
	}
	return (res_bigint);
}

/*
** ft_get_bigint: возвращает массив, заполненный '0'
*/

char		*ft_get_part(unsigned long long num, int shift, \
					t_bigint (*ft_get_bigint)(unsigned long long, int))
{
	t_bigint	bigint;
	char		*res;
	int			numlen;
	int			size;
	int			len;

	bigint = ft_get_bigint(num, shift);
	if (!num)
		bigint.size++;
	size = bigint.size - 1;
	res = (char*)malloc(size * NUM_LEN + ft_unumlen(bigint.num[size], 10) + 1);
	len = ft_itoa_base(bigint.num[size], res, 10, 0);
	while (size--)
	{
		numlen = ft_unumlen(bigint.num[size], 10);
		while (numlen++ < NUM_LEN - 1)
			res[len++] = '0';
		if (!bigint.num[size])
			res[len++] = '0';
		else
			len += ft_itoa_base(bigint.num[size], res + len, 10, 0);
	}
	res[len] = '\0';
	return (res);
}
