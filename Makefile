# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 14:13:59 by fkeitel           #+#    #+#              #
#    Updated: 2024/10/21 10:24:23 by fkeitel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##
##		Makefile for compiling all c files into the executable "fdf"
##

# Project name
NAME    := fdf

# Compiler and Flags
CC      := gcc
CFLAGS  := -Wunreachable-code -Ofast -Wall -Werror -Wextra -g -fsanitize=address
MLX_FLAGS := -L./MLX42/build -lmlx42 -I../MLX42/include -lglfw -framework Cocoa -framework OpenGL -framework IOKit

# Flag for memory leak detection, adjust the path to your own path
#LEAKFLAG := -L/Users/fkeitel/Documents/LeakSanitizer  -llsan

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
	fi
	@cd MLX42 && git checkout f87c401e495dcf56e9162a2241d7761238bb189f && cmake -B build && cmake --build build -j4 \

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
	@rm -rf MLX42/build

# Rule to clean project and object files
fclean: clean
	@rm -rf $(NAME)

# Rule to clean and rebuild the project
re: fclean all

# Phony targets
.PHONY: all clean fclean re mlx
