# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 19:39:45 by dgerguri          #+#    #+#              #
#    Updated: 2023/11/09 12:06:10 by dgerguri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# # Output binary name
# NAME		=	cub3D
# NAME_B		=	cub3D_bonus

# # Name, compiler, and flags
# CC = cc
# CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -ggdb3

# # Directories
# LIBFT_DIR	=	libft/
# MLX_DIR		=	MLX42/
# SRC_PATH	=	src/
# OBJ_PATH	=	obj/
# SRC_B_PATH	=	src_bonus/
# OBJ_B_PATH	=	obj_bonus/


# # Source files
# SRC			=	main.c error.c cleanup.c utils.c\
# 				init/data_init.c init/read_map.c init/split_line.c \
# 				init/mlx_init.c\
# 				parsing/split_elements_map.c parsing/validate_elements.c \
# 				parsing/parse_colors.c parsing/validate_map.c \
# 				parsing/validate_map_utils.c \
# 				raycasting/raycasting.c raycasting/raycasting_utils.c raycasting/moving.c raycasting/2d_drawing.c
# #Delete map_utils_two if not neccessay
# SRC_B		=	main_bonus.c

# # Object files
# OBJ			=	$(SRC:.c=.o)
# OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))
# OBJ_B		=	$(SRC_B:.c=.o)
# OBJS_B		=	$(addprefix $(OBJ_B_PATH), $(OBJ_B))

# # Include directories
# INCS		=	-I includes/ -I MLX42/include/MLX42/

# # Libraries
# LIBFT		=	libft.a
# MLX 		=	$(MLX_DIR)build/libmlx42.a
# GLFW		=	$(shell brew --prefix glfw)

# # Frameworks for macOs
# FRAMEWORK	=	-framework Cocoa -framework OpenGL -framework IOKit

# # Color codes for pretty output
# GREEN			=	\033[0;32m
# RED				=	\033[0;31m
# BLUE			=	\033[0;34m
# RESET			=	\033[0m

# # Default target: build the main program
# # all: $(NAME)

# #* this is my workaround to compile on linux
# # !!!REMOVE BEFORE SUBMISSION!!!
# all: $(MLX)
# 	$(MAKE) -C $(LIBFT_DIR)
# 	cc -Wall -Wextra -Werror src/*.c src/*/*.c -I includes/ -L libft/ -lft -L MLX42/build/ -lmlx42 -I libft/includes -I MLX42/include/ -ldl -lglfw -pthread -lm -o cub3d

# # Build the MLX library if needed
# $(MLX):
# 	#git submodule update --init --recursive $(MLX_DIR) //should try to make this work
# 	cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

# # Compile source files to object files
# $(OBJ_PATH)%.o: $(SRC_PATH)%.c
# 	@mkdir -p $(OBJ_PATH)
# 	@mkdir -p $(OBJ_PATH)/init
# 	@mkdir -p $(OBJ_PATH)/parsing
# 	@mkdir -p $(OBJ_PATH)/raycasting
# 	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# # Build the main program
# $(NAME): $(OBJS) $(MLX)
# 	@echo "$(BLUE)Compiling $(NAME)$(RESET)"
# 	@$(MAKE) -C $(LIBFT_DIR)
# 	@$(CC) $(CFLAGS) $(MLX) $(FRAMEWORK) -L $(GLFW)/lib -lglfw \
# 	-L $(LIBFT_DIR) -lft $(OBJS) -o $(NAME)
# 	@echo "$(GREEN)done$(RESET)"

# # Build the bonus program if needed
# bonus:  $(MLX) $(NAME_B)

# # Compile bonus source files to object files
# $(OBJ_B_PATH)%.o: $(SRC_B_PATH)%.c
# 	@mkdir -p $(OBJ_B_PATH)
# 	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# # Build the bonus program
# $(NAME_B): $(OBJS_B)
# 	@echo "$(BLUE)Compiling $(NAME_B)$(RESET)"
# 	@$(MAKE) -C $(LIBFT_DIR)
# 	@$(CC) $(CFLAGS) $(MLX) $(FRAMEWORK) -L $(GLFW)/lib -lglfw \
# 	-L $(LIBFT_DIR) -lft $(OBJS_B) -o $(NAME_B)
# 	@echo "$(GREEN)done$(RESET)"

# # Clean the project by removing object files
# clean:
# 	@echo "$(RED)removing object files$(RESET)"
# 	@/bin/rm -rf $(OBJ_PATH) $(OBJ_B_PATH)
# 	@$(MAKE) clean -C $(LIBFT_DIR)
# 	@/bin/rm -rf $(MLX_DIR)build

# # Clean the project and remove executables
# #? should fclean also clean mlx?
# fclean: clean
# 	@echo "$(RED)cleaning all compiled stuff.. :)$(RESET)"
# 	@/bin/rm -rf $(NAME) $(NAME_B)
# 	@$(MAKE) fclean -C $(LIBFT_DIR)
# 	@echo "$(RED)done$(RESET)"

# # Clean and rebuild the project
# re: fclean all

# # Declare phony targets (targets that don't create files with these names)
# .PHONY: all bonus clean fclean re
# Output binary name
NAME		=	cub3D
NAME_B		=	cub3D_bonus

# Name, compiler, and flags
CC = cc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -ggdb3

# Directories
LIBFT_DIR	=	libft/
MLX_DIR		=	MLX42/
SRC_PATH	=	src/
OBJ_PATH	=	obj/
SRC_B_PATH	=	src_bonus/
OBJ_B_PATH	=	obj_bonus/


# Source files
SRC			=	main.c error.c cleanup.c utils.c\
				init/data_init.c init/read_map.c init/split_line.c \
				init/mlx_init.c\
				parsing/split_elements_map.c parsing/validate_elements.c \
				parsing/parse_colors.c parsing/validate_map.c \
				parsing/validate_map_utils.c \
				raycasting/raycasting.c raycasting/raycasting_utils.c \
				raycasting/moving.c raycasting/2d_drawing.c raycasting/3d_drawing.c
#Delete map_utils_two if not neccessay
SRC_B		=	main_bonus.c

# Object files
OBJ			=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))
OBJ_B		=	$(SRC_B:.c=.o)
OBJS_B		=	$(addprefix $(OBJ_B_PATH), $(OBJ_B))

# Include directories
INCS		=	-I includes/ -I MLX42/include/MLX42/

# Libraries
LIBFT		=	libft.a
MLX 		=	$(MLX_DIR)build/libmlx42.a
GLFW		=	$(shell brew --prefix glfw)

# Frameworks for macOs
FRAMEWORK	=	-framework Cocoa -framework OpenGL -framework IOKit

# Color codes for pretty output
GREEN			=	\033[0;32m
RED				=	\033[0;31m
BLUE			=	\033[0;34m
RESET			=	\033[0m

# Default target: build the main program
all: $(NAME)

# Build the MLX library if needed
$(MLX):
	#git submodule update --init --recursive $(MLX_DIR) //should try to make this work
	cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

# Compile source files to object files
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/init
	@mkdir -p $(OBJ_PATH)/parsing
	@mkdir -p $(OBJ_PATH)/raycasting
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# Build the main program
$(NAME): $(OBJS) $(MLX)
	@echo "$(BLUE)Compiling $(NAME)$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(MLX) $(FRAMEWORK) -L $(GLFW)/lib -lglfw \
	-L $(LIBFT_DIR) -lft $(OBJS) -o $(NAME)
	@echo "$(GREEN)done$(RESET)"

# Build the bonus program if needed
bonus:  $(MLX) $(NAME_B)

# Compile bonus source files to object files
$(OBJ_B_PATH)%.o: $(SRC_B_PATH)%.c
	@mkdir -p $(OBJ_B_PATH)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# Build the bonus program
$(NAME_B): $(OBJS_B)
	@echo "$(BLUE)Compiling $(NAME_B)$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(MLX) $(FRAMEWORK) -L $(GLFW)/lib -lglfw \
	-L $(LIBFT_DIR) -lft $(OBJS_B) -o $(NAME_B)
	@echo "$(GREEN)done$(RESET)"

# Clean the project by removing object files
clean:
	@echo "$(RED)removing object files$(RESET)"
	@/bin/rm -rf $(OBJ_PATH) $(OBJ_B_PATH)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@/bin/rm -rf $(MLX_DIR)build

# Clean the project and remove executables
fclean: clean
	@echo "$(RED)cleaning all compiled stuff.. :)$(RESET)"
	@/bin/rm -rf $(NAME) $(NAME_B)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)done$(RESET)"

# Clean and rebuild the project
re: fclean all

# Declare phony targets (targets that don't create files with these names)
.PHONY: all bonus clean fclean re
