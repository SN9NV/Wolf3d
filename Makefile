# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adippena <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/05 13:18:57 by adippena          #+#    #+#              #
#    Updated: 2016/07/30 12:13:22 by adippena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	wolf3d

SRC			=	src/main.c				\
				src/game_loop.c			\
				src/draw.c				\
				src/env_init.c			\
				src/key_events.c		\
				src/dda.c				\
				src/use.c				\
				src/minimap.c			\
				src/fill_map.c			\
				src/load_texture.c		\
				src/get_time.c			\
				src/draw_floor.c		\
				src/draw_vscan.c

CFLAGS		=	-Wall -Wextra -Werror
INCLUDES	=	-I includes
LIBFT		=	-I libft/includes -L libft -lft
SDL2		=	$(shell sdl2-config --cflags --libs)

all: $(NAME)

$(NAME):
	cd libft; make all
	gcc $(CFLAGS) $(INCLUDES) $(SDL2) $(SRC) $(LIBFT) -o $(NAME) -lm

clean:
	cd libft; make clean
	rm -rf assembley

fclean: clean
	cd libft; make fclean
	rm -f $(NAME)

re: fclean all

run:
	rm -f $(NAME)
	gcc $(CFLAGS) $(INCLUDES) $(SRC) $(SDL2) $(LIBFT) -o $(NAME) -lm
	./$(NAME)

assembley:
	rm -f $(NAME)
	cd libft; make all
	gcc $(CFLAGS) $(INCLUDES) $(SRC) $(SDL_LINUX) $(LIBFT) -S -lm
	mkdir -p assembley
	mv *.s assembley
