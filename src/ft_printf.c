/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:48:21 by asmall            #+#    #+#             */
/*   Updated: 2020/01/26 14:48:23 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** %[флаги][ширина][точность][модификаторы][тип преобразования]
** ft_set_flags - проверка на флаги
** ft_set_width - вычисление ширины
** ft_set_accur - проверка на точность
** ft_set_modif - проверка модификаторов
** ft_set_spec - проверка спецификаторов
*/

void	ft_set_options(t_options *f, const char **form, va_list ap)
{
	char	*temp;

	f->flags = 0;
	f->width = -1;
	f->sum = -1;
	f->length = 0;
	f->base = 10;
	f->spec = 0;
	while (**form)
	{
		temp = (char*)*form;
		ft_set_flags(form, f);
		ft_set_width(form, f, ap);
		ft_set_accur(form, f, ap);
		ft_set_modif(form, f);
		if (ft_set_spec(**form, f) || temp == *form)
		{
			if (**form)
				(*form)++;
			break ;
		}
	}
}

/*
** Главная управляющая функция
** ft_init_buff: инициализация структуры, buff: массив(512 символов)
** ft_push: заполнение массива buff, если есть символы до "%"
*/

int		ft_printf(const char *form, ...)
{
	va_list		ap;
	t_options	f;
	t_buff		buf;

	va_start(ap, form);
	ft_init_buff(&buf, 1);
	while (*form)
	{
		if (*form != '%')
			(ft_color(&buf, &form, &f)) ? 1 : (ft_push(&buf, *form++));
		else
		{
			form++;
			ft_set_options(&f, &form, ap);
			(f.color) ? (ft_put_color(&buf, &f)) : 1;
			ft_handle_spec(&f, &buf, ap);
		}
	}
	va_end(ap);
	if (buf.i)
		ft_fd_write(1, &buf);
	return (buf.len);
}

/*
** Главная управляющая функция с fd
*/

int		ft_dprintf(int fd, const char *form, ...)
{
	va_list		ap;
	t_options	f;
	t_buff		buf;

	va_start(ap, form);
	ft_init_buff(&buf, fd);
	while (*form)
	{
		if (*form != '%')
			(ft_color(&buf, &form, &f)) ? 1 : (ft_push(&buf, *form++));
		else
		{
			form++;
			ft_set_options(&f, &form, ap);
			(f.color) ? (ft_put_color(&buf, &f)) : 1;
			ft_handle_spec(&f, &buf, ap);
		}
	}
	va_end(ap);
	if (buf.i)
		ft_fd_write(fd, &buf);
	return (buf.len);
}
