# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/30 11:49:44 by lbrianna          #+#    #+#              #
#    Updated: 2022/10/18 16:09:38 by cpollito         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

OBJS_DIR = ./obj/
SRCS_DIR = ./srcs/
LIBFT_DIR = libft

#SRCS = srcs/main.c srcs/parser.c srcs/make_data.c srcs/init.c\
# OBJS = $(SRCS:%.c=%.o)

SRCS_LIST = main.c\
			parser/parser.c\
			parser/make_data.c\
			parser/init.c\
			parser/data_to_map.c\
			parser/process_colors.c\
			parser/process_texture.c\
			init_mlx.c\
			ray_cast.c\
			key_hook.c\
			color_define.c\
			minimap.c\
			draw_textures.c\
			draw.c\
			utils.c\
			
#SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_LIST:.c=.o))

INCLUDES = includes/
HEADER = cub3d.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -g 
# -fsanitize=address
LIBFT = libft/libft.a
MLX = minilibx/libmlx.a

all:	$(NAME)

$(NAME):	$(LIBFT) $(OBJS) $(MLX)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -Lminilibx -lmlx -framework OpenGL -framework AppKit -lz

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c $(INCLUDES)$(HEADER) Makefile
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

# $(OBJS_DIR):
# 		@mkdir $@

# $(OBJS): | $(OBJS_DIR)

$(LIBFT):
		@make -C libft

$(MLX):
		@$(MAKE) -C minilibx/ CFLAGS=-DSTRINGPUTX11\ -Ofast\ -g\ -Wno-deprecated
		@cp $(MLX) .


clean:
				@rm -rf $(OBJS_DIR) libmlx.a
				@rm -rf libmlx.a
				@make -C minilibx clean
				@make -C libft clean
	
fclean	:	clean
				@rm -f cub3D  
				@rm -f libft/libft.a 
				@rm -f libmlx.dylib 

re:	fclean all

.PHONY: all clean fclean re libft