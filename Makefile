# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flo <flo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 14:13:59 by fkeitel           #+#    #+#              #
#    Updated: 2024/10/16 06:31:45 by flo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##
##		Makefile for compiling all c files into the executable "fdf"
##

# Project name
NAME    := fdf

# Compiler and Flags
CC      := gcc
CFLAGS  := -Wunreachable-code -Ofast -Wall -Werror -Wextra -g
MLX_FLAGS := -L./MLX42/build -lmlx42 -I../MLX42/include -lglfw -framework Cocoa -framework OpenGL -framework IOKit

# Flag for memory leak detection, adjust the path to your own path
#LEAKFLAG := -L/Users/flo/LeakSanitizer  -llsan

# Directories
SRC_DIR := src
OBJ_DIR := obj
INC_DIR := include  # Include directory

# Source files, Libraries targets
SRCS    := $(shell find $(SRC_DIR) -name '*.c')
LIBFT   := libft/
LIBFTTARGET := $(LIBFT)/libft.a
OBJS    := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Header file
HEADER  := $(INC_DIR)/fdf.h

# Rule to build the project
all: $(OBJ_DIR) $(NAME)
	@echo "$(NAME) successfully built!"

# Rule to fetch and build the MLX library
mlx:
	@if [ ! -d "MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git MLX42; \
		cd MLX42 && cmake -B build && cmake --build build -j4; \
	fi

# Rule to build the project using MLX library
$(NAME): mlx $(OBJS) $(LIBFTTARGET)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(LEAKFLAG) -o $@ $(LIBFTTARGET)

$(LIBFTTARGET):
	@$(MAKE) -C $(LIBFT)

# Rule to compile source files into object files in a separate obj folder
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(info Compiling $<)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@  # Include directory

# Create the objects directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Rule to clean object files
clean:
	@$(MAKE) -C $(LIBFT) fclean
	@rm -rf $(OBJ_DIR)

# Rule to clean project and object files
fclean: clean
	@rm -rf $(NAME)

# Rule to clean and rebuild the project
re: fclean all

# Phony targets
.PHONY: all clean fclean re mlx
