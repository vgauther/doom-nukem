/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmoreau <esmoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:01:29 by esmoreau          #+#    #+#             */
/*   Updated: 2019/11/18 12:08:07 by vgauther         ###   ########.fr       */
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
}				t_render;

typedef struct	s_sector
{
	int 		*pts;
	int 		floor;
	int 		ceilling;
}				t_sector;

typedef struct	s_ennemy
{
	int 		x;
	int 		y;
	int			type;
	int 		xp;
	int			hp;
}				t_ennemy;

typedef struct	s_weapon
{
	int 		x;
	int 		y;
	int			type;
	int 		capa;
}				t_weapon;

typedef struct	s_map
{
	int 		*sectors;
	int			nb_ennemies;
	t_ennemy	*ennemies;
	int 		nb_weapons;
	t_weapon 	*weapons;

}				t_map;

typedef struct	s_data_file
{
	int 		nb_sectors;
	int 		nb_textures;
	int	 		nb_points;
	int 		nb_maps;
	int 		nb_weapons;
	int 		nb_ennemies;
	int 		point_count;
	int 		map_count;
	int 		sector_count;
	int			weapon_count;
	int			ennemy_count;
	t_point  	*points;
	t_sector 	*sectors;
	t_ennemy 	*ennemies;
	t_map 		*maps;
	t_weapon 	*weapons;
}				t_data_file;

typedef struct	s_var
{
	t_data_file 	data;
	t_sdl			sdl;
	t_coor			map[13];
	t_player		player;
}				t_var;

void	display(t_var *var);
void	ft_error(int i);
void	ft_clean_quit(SDL_Renderer *render, SDL_Window *window);
void	sdl_clean_screen(SDL_Renderer *rend);
void	ft_init_sdl(t_var *var);
float 	clamp(int a, int b, int c);

/* math.c */
double 	pythagore(double a, double b);
double 	yaw(double a, double b, double c);
float 	max(float a, float b);
float 	min(float a, float b);

/* move.c */
void forward(t_var *var, double speed, double angle);
void backward(t_var *var, double speed, double angle);

/* parser func */
int parser_data_main(t_var *var);
void parser_data_messages(int id);

/* free_tab.c */
void free_tab_char(char **tab);
void free_2_tab_char(char **tab, char **tab1);
void free_3_tab_char(char **tab, char **tab1, char **tab2);
void free_4_tab_char(char **tab, char **tab1, char **tab2, char **tab3);
int free_tab_char_with_ret_1(char **tab);

/* free_str.c */
int free_ret_1(char *str);
int free_2_str(char *str);
int free_2_tab_char_ret_1(char **tab, char **tab1);
int free_3_tab_char_ret_1(char **tab, char **tab1, char **tab2);
int free_4_tab_char_ret_1(char **tab, char **tab1, char **tab2, char **tab3);

/* messages.c */
int malloc_error(char *str);

/* parser.c */
int recup_data_map(t_var *var, char *str);

#endif
