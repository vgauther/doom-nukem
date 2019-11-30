/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 22:37:34 by vgauther          #+#    #+#             */
/*   Updated: 2019/11/30 23:17:33 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** put a black screen
*/

void		sdl_clean_screen(SDL_Renderer *rend)
{
	SDL_SetRenderDrawColor(rend, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(rend);
}

/*
** destroy/free render + destroy/free window
*/

void		ft_clean_quit(SDL_Renderer *render, SDL_Window *window)
{
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
