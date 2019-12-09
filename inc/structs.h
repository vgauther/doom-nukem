/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 23:54:46 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/09 14:45:07 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct		s_xy
{
	double			x;
	double			y;
}					t_xy;

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
	double 			yaw;
	int 			sector;
	int				map;
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
	int						nb_pts; // nombre de point du secteur
	int 					*pts; // num points du secteur
	int						*neighbors;	// num des secteurs voisins
	int 					*textures; // num des textures
	int 					floor;
	int 					ceilling;
}				t_sector;

typedef struct	s_map
{
	int 	nb_sectors;
	int		nb_ennemies;
	int 	nb_weapons;
	int 	*sectors; // num des secteur sur la map
	int		*ennemies;
	int		*weapons;
	int 	spawn_x;
	int 	spawn_y;
	int 	end_lv_x;
	int 	end_lv_y;
}				t_map;

typedef struct	s_img
{
	int			h;
	int			w;
	Uint32		*pixels;
}				t_img;

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
	int 			number_of_sector;
	double			nearz;
	double			farz;
	double			nearside;
	double			farside;
	t_img			wall_texture[4];
}				t_var;

typedef struct s_draw_walls
{
	int			ya;
	int			cya;
	int			yb;
	int			cyb;
	int			nya;
	int			cnya;
	int			nyb;
	int			cnyb;
}				t_draw_walls;

typedef struct s_draw
{
	double		vx1;
	double		vy1;
	double		vx2;
	double		vy2;
	double		tx1;
	double		tz1;
	double		tx2;
	double		tz2;
	double		ttx1;
	double		ttz1;
	double		ttx2;
	double		ttz2;
	double		xscale1;
	double		yscale1;
	double		xscale2;
	double		yscale2;
	double		nyceil;
	double		nyfloor;
	double		yceil;
	double		yfloor;
	double 		wall_width;
	int			y1a;
	int			y1b;
	int			y2a;
	int			y2b;
	int			ny1a;
	int			ny1b;
	int			ny2a;
	int			ny2b;
	int			x1;
	int			x2;
	int			beginx;
	int			endx;
}				t_draw;
#endif
