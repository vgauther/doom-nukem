# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/18 20:24:21 by vgauther          #+#    #+#              #
#    Updated: 2018/03/28 16:00:44 by fde-souz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, $(NAME), clean, fclean, re

NAME = SDL

END=$'\x1b[0m
BOLD=$'\x1b[1m'
UNDER=$'\x1b[4m'
REV=$'\x1b[7m'

# Colors
GREY=$'\x1b[30m'
RED=$'\x1b[31m
GREEN=$'\x1b[32m
YELLOW=$'\x1b[33m'
BLUE=$'\x1b[34m'
PURPLE=$'\x1b[35m'
CYAN=$'\x1b[36m'
WHITE=$'\x1b[37m'

SDL_PATH = $(shell pwd)/SDL

ifneq ("$(wildcard $(SDL_PATH))","")
SDL = 1
else
SDL = 0
endif

all: $(NAME)

$(NAME):
	@if [ $(SDL) = 0 ]; then \
	make sdl_2 -j8; \
	fi
	@echo "$(GREEN)[✓] SDL 2 Done$(END)"

sdl_2:
	@rm -rf $(SDL_PATH)
	@mkdir $(SDL_PATH)
	@cd $(SDL_PATH) && $(SDL_PATH)/../SDL2-2.0.8/configure --prefix=$(SDL_PATH) && make && make install

sdl_clean:
	@rm -rf $(SDL_PATH)
	@echo "$(RED)[-] Wolf 3D Done$(END)"

clean:
	@make sdl_clean
