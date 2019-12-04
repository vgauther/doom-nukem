/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 23:54:46 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/04 17:13:54 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_xy
{
	float x;
	float y;
}				t_xy;

typedef struct		s_item
{
	int				sectorno;
	int				sx1;
	int				sx2;
}					t_item;

typedef struct		s_reader
{
	t_item			queue[32];
	t_item			*head;
	t_item			*tail;
	t_item			now;
}					t_reader;


typedef struct s_coor
{
	float 			x;
	float 			y;
	float 			z;
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
	float 			angle;
	float 			psin;
	float 			pcos;
	int				xp;
	int 			lvl;
	float 			yaw;
	int sector;
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
	float 	xscale1;
	float 	yscale1;
	float 	xscale2;
	float 	yscale2;
	float 	nearz;
	float 	farz;
	float 	nearside;
	float 	farside;
	float	wall_width;
	int 	x1;
	int 	x2;
	int		y1a;
	int		y1b;
	int		y2a;
	int		y2b;
	int 	cya;
	int 	cyb;
	int		ya;
	int		yb;
	int		ny1a;
	int		ny1b;
	int		ny2a;
	int		ny2b;
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
	int 			*sectors; // num des secteur sur la map
	int				nb_ennemies;
	int				*ennemies;
	int 			nb_weapons;
	int				*weapons;
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
	int				key[4];
	int				kind_of_screen;
}				t_var;

#endif
