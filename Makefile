# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drafe <drafe@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/12 20:00:16 by drafe             #+#    #+#              #
#    Updated: 2019/08/31 21:12:56 by nshelly          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -I./mlx_linux

NAME = fdf

HEADERS = fdf.h

LIBS = -L./libft/ -lft\
	-L./mlx_linux -lmlx -lXext -lX11 -lm

OBJS = $(SRCS:.c=.o)

SRCS = src/main.c\
	src/fdf_draw.c\
	src/fdf_ui.c\
	src/fdf_reform.c\
	src/fdf_new_win.c\
	src/fdf_colors.c\
	src/fdf_color_change.c\
	src/fdf_keys.c\
	src/fdf_points.c

all: $(NAME)

$(NAME):$(OBJS) | lib
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -I . -o $@ -c $<

lib: ./mlx_linux/libmlx.a
	make -C ./libft

./mlx_linux/libmlx.a:
	@if [ ! -f ./mlx_linux/Makefile.gen ]; then \
		cd ./mlx_linux && ./configure; \
	fi
	@cd ./mlx_linux && make -f Makefile.gen

clean:
	make clean -C ./libft
	make clean -C ./mlx_linux 2>/dev/null || true
	rm -rf $(OBJS)

fclean: clean
	make fclean -C ./libft
	make clean -C ./mlx_linux 2>/dev/null || true
	rm -f $(NAME)

re: fclean all

