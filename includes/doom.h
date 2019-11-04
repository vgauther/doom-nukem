/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmoreau <esmoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:01:29 by esmoreau          #+#    #+#             */
/*   Updated: 2019/11/02 23:36:29 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# define SIZE_X 960
# define SIZE_Y 600
# define RAD 3.14159265 / 180
# define THREAD 2
# include "../libft/includes/libft.h"
# include "SDL2/SDL.h"
# include "math.h"
# include <math.h>
# include <pthread.h>

typedef struct	s_sdl
{
	SDL_Window		*window;
	SDL_Event		event;
	SDL_Renderer	*render;
}				t_sdl;

typedef struct	s_var
{
	int			x_max;
	int			y_max;
	char		**map;
	int			menu_is_act;
	SDL_Surface	*wall_texture[4];
	Uint32		*wall_uint[4];
	int			i;
	int			texture_id;
	int			on;
	t_sdl		sdl;
	int			**m;
	int			select_key;
	SDL_Surface	*key_texture[41];
	int			key_id[4];
}				t_var;

void	display(t_var *var);
void	ft_error(int i);
void	ft_clean_quit(SDL_Renderer *render, SDL_Window *window);
void	sdl_clean_screen(SDL_Renderer *rend);
void	ft_init_sdl(t_var *var);

#endif
