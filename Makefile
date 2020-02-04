# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asmall <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/27 13:53:20 by asmall            #+#    #+#              #
#    Updated: 2020/01/31 19:51:24 by asmall           ###   ########.fr        #
#                                                                              #
# **************************************************************************** # 

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror

SRCDIR = src/
SRC = 	ft_bigint_operations.c \
		ft_bigint.c \
		ft_buff_manage.c \
		ft_handle.c \
		ft_parse_nums.c \
		ft_print_cs.c \
		ft_print_diuoxb.c \
		ft_print_e.c \
		ft_print_f.c \
		ft_print_options.c \
		ft_print_prk.c \
		ft_printf.c \
		ft_set_options.c \
		ft_utils_num.c \
		ft_utils_str.c \
		ft_color.c \

OBJDIR = obj/
OBJ = $(addprefix $(OBJDIR), $(SRC:%.c=%.o))

INCLUDES = includes/
HEADER = $(addprefix $(INCLUDES), ft_printf.h)

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@ -I $(INCLUDES)

$(OBJDIR):
	mkdir obj/

clean:
	rm -rf $(OBJ) main.o
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
