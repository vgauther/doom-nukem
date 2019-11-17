/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmoreau <esmoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:01:29 by esmoreau          #+#    #+#             */
/*   Updated: 2019/11/17 10:59:34 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# define SIZE_X 608
# define SIZE_Y 480

# define hfov (0.73f * SIZE_Y)  // Affects the horizontal field of vision
# define vfov (.2f * SIZE_Y)
# define RAD 3.14159265 / 180
# define THREAD 2
# include "../libft/includes/libft.h"
# include "SDL2/SDL.h"
# include <math.h>
# include <pthread.h>


typedef struct s_coor
{
	double 			x;
	double 			y;
	double 			z;
}				t_coor;

typedef struct	s_sdl
{
	SDL_Window		*window;
	SDL_Event		event;
	SDL_Renderer	*render;
}				t_sdl;

typedef struct	s_player
{
	t_coor 			pos;
	double 			angle;
	double 			psin;
	double 			pcos;
}				t_player;

typedef struct	s_color
{
	int 			r;
	int 			v;
	int 			b;
}				t_color;

typedef struct	s_var
{
	t_sdl			sdl;
	t_coor			map[6];
	t_player		player;
}				t_var;

void	display(t_var *var);
void	ft_error(int i);
void	ft_clean_quit(SDL_Renderer *render, SDL_Window *window);
void	sdl_clean_screen(SDL_Renderer *rend);
void	ft_init_sdl(t_var *var);
double 	pythagore(double a, double b);
float 	max(float a, float b);
float 	min(float a, float b);
float 	clamp(int a, int b, int c);

#endif
