# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asmall <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/03 07:33:44 by asmall            #+#    #+#              #
#    Updated: 2018/04/24 12:13:54 by asmall           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FT_PRINTF_SRC = ft_printf.c \
				process_string.c parse_modifiers.c \
				print_decimal.c print_decimal_padding.c \
				print_unsigned_decimal.c \
				print_octal.c print_hexadecimal.c print_pointer.c \
				print_binary.c \
				print_char.c print_control_char.c print_string.c \
				print_percent_sign.c \
				ft_itoa_base_pf.c \
				ft_signed_nbr_len.c \
				ft_putwchar_pf.c ft_putwstr_pf.c ft_wstrsize_pf.c

LIBFT_PATH = libft/
LIBFT_SRC = ft_bzero.c ft_memalloc.c \
			ft_strlen.c ft_strdup.c ft_strcpy.c ft_strchr.c ft_strcmp.c \
			ft_atoi.c ft_isdigit.c ft_isspace.c \

OBJ += $(FT_PRINTF_SRC:.c=.o)
OBJ += $(addprefix $(LIBFT_PATH),$(LIBFT_SRC:.c=.o))

CC = gcc
CFLAGS = -Wall -Werror -Wextra

CLEAR_LINE = \033[2K\c

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\nCreating $@"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@echo "$(CLEAR_LINE)"
	@echo "Compiling $<\r\c"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
