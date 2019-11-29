/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 23:54:27 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/29 23:54:29 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_mixer.h"
# include "libft.h"
# include "defines.h"
# include "structs.h"
# include <pthread.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define SIZE_X 608
# define SIZE_Y 480

# define hfov (0.73f * SIZE_Y)
# define vfov (.2f * SIZE_Y)

# define RAD 3.14159265 / 180

typedef struct s_coor
{
	double 			x;
	double 			y;
	double 			z;
}				t_coor;

typedef struct 	s_point
{
	int x;
	int y;
}				t_point;

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
	int				xp;
	int 			lvl;
}				t_player;

typedef struct	s_color
{
	int 			r;
	int 			v;
	int 			b;
}				t_color;

typedef struct	s_render
{
	t_coor 	v1;
	t_coor 	v2;
	t_coor 	t1;
	t_coor 	t2;
	t_coor	i1;
	t_coor	i2;
	double 	xscale1;
	double 	yscale1;
	double 	xscale2;
	double 	yscale2;
	double 	nearz;
	double 	farz;
	double 	nearside;
	double 	farside;
	int 	x1;
	int 	x2;
	int		y1a;
	int		y1b;
	int		y2a;
	int		y2b;
}				t_render;

typedef struct	s_ennemy
{
	int 		x;
	int 		y;
	char 		name[5];
	int			hp;
	int 		xp;
}				t_ennemy;

typedef struct	s_weapon
{
	int 		x;
	int 		y;
	char 		name[5];
	int 		maga;
	int 		ammo;
}				t_weapon;

typedef struct	s_sector
{
	int 			*pts; // num points du secteur
	unsigned int	nb_pts; // nombre de point du secteur
	int 			floor;
	int 			ceilling;
	int				*neighbors;	// num des secteurs voisins
}				t_sector;

typedef struct	s_map
{
	int 		*sectors; // num des secteur sur la map
	int			nb_ennemies;
	int			*ennemies;
	int 		nb_weapons;
	int			*weapons;
}				t_map;

typedef struct	s_var
{
	t_sdl			sdl;
	t_point  		*points; // liste de tous les points
	t_sector 		*sectors; // liste de tous les secteurs
	t_ennemy 		*ennemies;
	t_map 			*maps; // liste de toutes les maps
	t_weapon 		*weapons;
	t_player		player;
	int 			p_count;
	int 			m_count;
	int 			s_count;
	int				w_count;
	int				e_count;
}				t_var;

#endif
