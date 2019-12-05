/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 22:37:34 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/05 10:52:37 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		put_surface(SDL_Renderer *r, SDL_Surface *s, SDL_Rect dimensions)
{
	SDL_Texture	*mon_image;

	mon_image = SDL_CreateTextureFromSurface(r, s);
	SDL_QueryTexture(mon_image, NULL, NULL, &dimensions.w, &dimensions.h);
	SDL_SetRenderTarget(r, mon_image);
	SDL_RenderCopy(r, mon_image, NULL, &dimensions);
	SDL_DestroyTexture(mon_image);
}

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
