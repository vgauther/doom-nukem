/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 23:54:27 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/07 18:59:41 by vgauther         ###   ########.fr       */
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

/*
** display.c
*/

void DrawScreen(t_var *var, SDL_Renderer *ren, Uint32 **wt);

/*
** free_tab.c
*/

void		free_tab_char(char **tab);

/*
** let_the_music_play.c
*/

int			let_the_music_play(void);

/*
** min_max_clamp.c
*/

double		max(double a, double b);
double		min(double a, double b);
int			clamp(int a, int b, int c);

/*
** move.c
*/

void		move_right(t_var *var);
void		move_left(t_var *var);
void		move_forward(t_var *var, double i);
void		move_backward(t_var *var);

/*
** parsing functions
*/

void	fill_data_struct(t_var *var);
void	fill_points(t_var *var, char *buff);
void	fill_weapons(t_var *var, char *buff);
void	fill_ennemies(t_var *var, char *buff);
void	fill_sectors(t_var *var, char *buff);


/*
** pythagore.c
*/

double		pythagore(double a, double b);

/*
** sdl_tools.c
*/
SDL_Rect	create_sdl_rect(int x, int y, int w, int h);
void		sdl_clean_screen(SDL_Renderer *rend);
void		ft_clean_quit(SDL_Renderer *render, SDL_Window *window);
void		put_surface(SDL_Renderer *r, SDL_Surface *s, SDL_Rect dimensions);

#endif
