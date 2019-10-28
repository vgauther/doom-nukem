/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamisdra <mamisdra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:08:36 by mamisdra          #+#    #+#             */
/*   Updated: 2019/10/28 15:25:53 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# define WALL '1'
# define COUL '0'
# define SPAWN '7'
# define BS_INT 128
# define BLOCK_SIZE 128.00
# define BS 128
# define BSD 128.00
# define SIZE_X 960
# define SIZE_Y 600
# define SIZE_X_2 480
# define SIZE_Y_2 300
# define SIZE_X_D 960.00
# define SIZE_Y_D 600.00
# define SIZE_X_D2 480.00
# define SIZE_Y_D2 300.00
# define ANGLE_BEGIN 30.00
# define RAD 3.14159265 / 180
# define DIV_60_SIZE 0.0625
# include "../libft/includes/libft.h"
# include "SDL2/SDL.h"
# include "math.h"
# include <math.h>

typedef struct	s_key
{
	int			forw;
	int			back;
	int			right;
	int			left;
}				t_key;

typedef struct	s_sdl
{
	SDL_Window		*window;
	SDL_Event		event;
	SDL_Renderer	*render;
}				t_sdl;

typedef struct	s_rgb
{
	int			r;
	int			g;
	int			b;
	int			a;
}				t_rgb;

typedef struct	s_pos
{
	double		x;
	double		y;
}				t_pos;

typedef struct	s_inter
{
	double		alpha;
	double		beta;
	int			hei;
	int			dist;
	int			y_img;
	int			plw;
	int			phw;

}				t_inter;

typedef struct	s_var
{
	int			x_max;
	int			y_max;
	char		**map;
	t_pos		spawn;
	int			menu_is_act;
	t_rgb		color;
	SDL_Surface	*wall_texture[4];
	Uint32		*wall_uint[4];
	int			i;
	int			texture_id;
	int			on;
	t_sdl		sdl;
	t_key		key;
	int			**m;
	int			select_key;
	SDL_Surface	*key_texture[41];
	int 		key_id[4];

}				t_var;

typedef struct	s_weapon
{
	int type;
	int	capa_bullet;
	int bullet;
}				t_weapon;

typedef struct		s_item
{
	int type;
	int pos_in_inventory;
}				t_item;


typedef struct	s_player
{
	t_pos		pos;
	double		fov;
	int			height;
	double		angle;
	int			coin;
}				t_player;

void			parsing_map(int fd, t_var *var);
void			buttons_menu_options(t_var *var, int i);
void			buttons_menu_play(t_var *var, int i);
void			check_map(t_var *var, int ret, size_t nb_char, char *str);
void			print_screen(t_var *var, t_player *player);
void			ft_sdl(t_var *var, SDL_Renderer *render, t_player *player);
void			ft_move(int key, t_player *pla, SDL_Renderer *ren, t_var *var);
void			ft_menu(t_var *v, t_player *p);
void			ft_error(int i);
t_rgb			set_color(int r, int g, int b, int a);
Uint32			set_pixel_color(t_rgb c);
t_rgb			get_color_from_surface(Uint32 x);
void			open_wall_texture(t_var *var);
void			sdl_clean_screen(SDL_Renderer *rend);
SDL_Rect		create_sdl_rect(int x, int y, int w, int h);
void			ft_clean_quit(SDL_Renderer *render, SDL_Window *window);
int				launch_ray(t_player *pl, t_var *var, double al, double beta);
void			init_a_b_alpha(t_pos *a, t_pos *b, double *alpha);
void			display(t_var *var, t_player *pl);
void			option_menu(int *x_y, t_var *var, t_player *player);
void			print_button(int *x_y, t_var *var, t_player *player);
void			put_image(t_var *var, char *name, SDL_Rect dimensions);
double			dist_0_1(t_var *var, double alpha, double beta, t_pos b);
double			dist_1_0(t_var *var, double alpha, double beta, t_pos a);
void			choose_key(t_var *var, t_player *player);
void			init_key_move(t_var *var);
void			change_key(t_var *var, t_player *player);
void			open_img_opt_button(t_var *var);

#endif
