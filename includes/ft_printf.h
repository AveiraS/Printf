/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_f_print.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:47:47 by vfearles          #+#    #+#             */
/*   Updated: 2020/01/26 14:47:49 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <wchar.h>
# include <inttypes.h>
# include <stdlib.h>

# define MAX_LEN 512

# define F_MINUS 1
# define F_PLUS 2
# define F_SP 4
# define F_SHARP 8
# define F_NULL 16
# define F_LOWER 32

# define LEN_HH 1
# define LEN_H 2
# define LEN_L 4
# define LEN_LL 8
# define LEN_J 16
# define LEN_Z 32
# define LEN_TIME 64

# define MAX_DEC 20
# define MAX_BIN 65

# define MAX_POWER 5
# define MAX_NUM 100000000UL
# define NUM_LEN 9
# define MAX_BIGINT 1536

# define PF_RED			11
# define PF_GREEN		22
# define PF_YELLOW		33
# define PF_BLUE		44
# define PF_PURPLE		55
# define PF_CYAN		66
# define PF_EOC			77

typedef struct			s_options
{
	int					flags;
	int					width;
	int					sum;
	int					length;
	int					base;
	char				spec;
	int					color;
}						t_options;

typedef struct			s_buff
{
	char				buff[MAX_LEN];
	int					i;
	int					len;
	int					fd;
}						t_buff;

/*
** union (объединения) - объект, позволяющий нескольким переменным
** различных типов занимать один участок памяти.
*/

union					u_f
{
	double				f;
	long double			lf;
	unsigned long long	ll;
};

typedef struct			s_fnum
{
	union u_f			num;
	char				sign;
	int					exp;
	unsigned long long	man;
	char				*ipoint;
	char				*fpoint;
	int					zero;
}						t_fnum;

typedef struct			s_bigint
{
	unsigned long long	num[MAX_BIGINT];
	int					size;
}						t_bigint;

int						ft_printf(const char *form, ...);
int						ft_dprintf(int fd, const char *form, ...);

void					ft_fd_write(int fd, t_buff *buf);
void					ft_init_buff(t_buff *buf, int fd);
void					ft_push(t_buff *buf, unsigned char c);

void					ft_strdel(char **str);
void					*ft_memmove(void *dst, const void *src, size_t len);
int						ft_strnlen(char *str, int n);
int						ft_wstrnlen(wchar_t *str, int n);
int						ft_rstrnlen(char *str, int n);

int						ft_power(int base, int power);
int						ft_atoi(const char *str);
int						ft_unumlen(unsigned long long num, int base);
int						ft_itoa_base(unsigned long long num, char *str, \
							int base, char lower);

void					ft_set_options(t_options *f, const char **form, \
							va_list ap);
void					ft_set_flags(const char **form, t_options *f);
void					ft_set_width(const char **form, t_options *f, \
							va_list ap);
void					ft_set_accur(const char **form, t_options *f, \
							va_list ap);
void					ft_set_modif(const char **form, t_options *f);
int						ft_set_spec(char c, t_options *f);

void					ft_handle_spec(t_options *f, t_buff *buf, \
							va_list ap);
int						ft_handle_num(t_options *f, t_buff *buf, \
							va_list ap);
int						ft_handle_other(t_options *f, t_buff *buf, \
							va_list ap);

void					ft_parse_num(t_options *f, t_buff *buf, \
							long long num);
void					ft_parse_unum(t_options *f, t_buff *buf, \
							unsigned long long unum);
void					ft_parse_fnum(t_options *f, t_buff *buf, \
							double num, \
							void (*ft_print)(t_options*, t_buff*, t_fnum*));
void					ft_parse_lfnum(t_options *f, t_buff *buf, \
							long double num, \
							void (*ft_print)(t_options*, t_buff*, t_fnum*));

void					ft_di_print(t_options *f, t_buff *buf, \
							long long num);
void					ft_uoxb_print(t_options *f, t_buff *buf, \
							unsigned long long unum);
void					ft_c_print(t_options *f, t_buff *buf, \
							unsigned char c);
void					ft_lc_print(t_options *f, t_buff *buf, wchar_t c);
void					ft_s_print(t_options *f, t_buff *buf, char *str);
void					ft_ls_print(t_options *f, t_buff *buf, \
							wchar_t *str);
void					ft_p_print(t_options *f, t_buff *buf, \
							void *pointer);
void					ft_r_print(t_options *f, t_buff *buf, char *str);
void					ft_f_print(t_options *f, t_buff *buf, \
							t_fnum *fnum);
void					ft_e_print(t_options *f, t_buff *buf, \
							t_fnum *fnum);
void					ft_k_print(t_options *f, t_buff *buf, \
							unsigned long long unum);
void					ft_r_printand(t_options *f, t_buff *buf);

char					ft_get_sign_f(t_options *f, char sign);
void					ft_round(char *number, int len);
int						ft_get_zero(unsigned long long num, \
							int shift, char *fpoint);
char					*ft_get_part(unsigned long long num, int shift, \
							t_bigint (*ft_get_bigint)(unsigned long long, int));
t_bigint				ft_get_fp(unsigned long long num, int shift);
t_bigint				ft_get_ip(unsigned long long num, int shift);

void					ft_reset_bigint(t_bigint *bigint);
void					ft_set_bigint(t_bigint *bigint, int power, int base);

void					ft_bigint_sum(t_bigint *bigint1, \
							t_bigint *bigint2);
t_bigint				ft_bigint_multi(t_bigint *bigint1, \
							t_bigint *bigint2);
void					ft_big_int_multi(t_bigint *bigint, int num);

void					ft_print_width(t_buff *buf, int *width, char c);
void					ft_p_printrec(t_buff *buf, int sum, int len);
void					ft_s_printharp(t_buff *buf, t_options *f);

int						ft_color(t_buff *buf, const char **form, t_options *f);
void					ft_put_color(t_buff *buf, t_options *f);

#endif
