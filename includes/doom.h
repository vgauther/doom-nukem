/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmoreau <esmoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:01:29 by esmoreau          #+#    #+#             */
/*   Updated: 2019/11/21 21:56:19 by mamisdra         ###   ########.fr       */
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

/* filler_funct.c */
void	fill_points(t_var *var, char *buff);
void	fill_weapons(t_var *var, char *buff);
void	fill_ennemies(t_var *var, char *buff);
void	fill_sectors(t_var *var, char *buff);
void	fill_data_struct(t_var *var);

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
