# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/18 20:24:21 by vgauther          #+#    #+#              #
#    Updated: 2019/11/18 11:53:10 by vgauther         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, $(NAME), clean, fclean, re

NAME = doom-nukem

END=$'\x1b[0m
BOLD=$'\x1b[1m'
UNDER=$'\x1b[4m'
REV=$'\x1b[7m'

# Colors
GREY=$'\x1b[30m
RED=$'\x1b[31m
GREEN=$'\x1b[32m
YELLOW=$'\x1b[33m
BLUE=$'\x1b[34m
PURPLE=$'\x1b[35m
CYAN=$'\x1b[36m
WHITE=$'\x1b[37m

CC = gcc
CC_FLAGS = -g3 -Wall -Wextra -Werror

SDL_PATH = $(shell pwd)/lib/SDL
SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./obj/
LFT_PATH = ./libft/
LIBSDL_ROOT = ./libSDL2/
LIBSDL_PATH = ./libSDL2/lib/
SDL_PATHO = ./SDL2-2.0.9/


SDL_FLG = -L$(LIBSDL_PATH) -lSDL2
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
CURL_SDL = `curl https://www.libsdl.org/release/SDL2-2.0.9.zip -o sdl2.zip`

OBJ_NAME = $(SRC_NAME:.c=.o)

INC_NAME = doom.h

SRC_NAME =	main.c \
			error.c \
			display.c \
			sdl_tools.c \
			math.c \
			parser_data_messages.c \
			parser_data_main.c \
			free_tab.c \
			free_str.c \
			move.c \
			messages.c \
			parser_recup_data_map.c

ifneq ("$(wildcard $(SDL_PATHO))","")
	SDL = 1
else
	SDL = 0
endif

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LFT_PATH)
	@if [ $(SDL) = 0 ]; then \
	make sdl; \
	fi
	@echo "$(YELLOW)[...] DOOM compilation$(END)"
	@$(CC) -o $(NAME) $(OBJ) -lm -L $(LFT_PATH) -lft $(SDL_FLG)
	@make draw
	@echo "$(GREEN)[✓] DOOM Done$(END)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) $(INC) -o $@ -c $<

clean:
	@make -C $(LFT_PATH) clean
	@rm -rf $(OBJ_PATH)
	@echo "$(RED)[-] DOOM .o cleaned$(END)"

sdl:
	$(CURL_SDL)
	@echo "$(GREEN)------------------------------$(END)"
	@echo "$(GREEN)--SDL ZIP SOURCES DOWNLOADED--$(END)"
	@echo "$(GREEN)------------------------------$(END)"
	unzip sdl2.zip
	rm sdl2.zip
	mkdir -p $(LIBSDL_ROOT)
	cd $(SDL_PATHO) && ./configure --prefix=$(PWD)/$(LIBSDL_ROOT)
	make -C $(SDL_PATHO)
	make install -C $(SDL_PATHO)
	@echo "$(GREEN)------------------------------$(END)"
	@echo "$(GREEN)---------SDL COMPILED---------$(END)"
	@echo "$(GREEN)------------------------------$(END)"

fclean:
	@make clean
	@make -C $(LFT_PATH) fclean
	@rm -rf SDL2-2.0.9
	@rm -f $(NAME)
	@echo "$(RED)[-] DOOM executable cleaned$(END)"


fcleanr:
	@make clean
	@make -C $(LFT_PATH) fclean
	@rm -f $(NAME)
	@echo "$(RED)[-] DOOM executable cleaned$(END)"

fclean_all:
	@make fclean
	@make cllib

clean_o:
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)

re:
	@make fclean
	@make all

rr:
	@make fcleanr
	@make all

clsdl:
	@make -C ./lib sdl_clean

draw:
	cd makefile_sources && gcc drawing.c && ./a.out
