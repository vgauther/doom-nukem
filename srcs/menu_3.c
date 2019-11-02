/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmoreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:54:25 by esmoreau          #+#    #+#             */
/*   Updated: 2019/10/14 14:54:28 by esmoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

double	dist_0_1(t_var *var, double alpha, double beta, t_pos b)
{
	var->texture_id = cos(alpha) > 0 ? 0 : 1;
	var->i = (int)b.y % BS_INT;
	return (cos(beta * RAD));
}

double	dist_1_0(t_var *var, double alpha, double beta, t_pos a)
{
	var->texture_id = sin(alpha) > 0 ? 2 : 3;
	var->i = (int)a.x % BS_INT;
	return (cos(beta * RAD));
}

int		change_texture_key(int nk)
{
	if (nk >= 'a' && nk <= 'z')
		return (nk - 'a');
	else if (nk >= '0' && nk <= '9')
		return (nk - '0' + 27);
	else if (nk == 1073741906)
		return (37);
	else if (nk == 1073741905)
		return (38);
	else if (nk == 1073741904)
		return (40);
	else if (nk == 1073741903)
		return (39);
	return (26);
}

void	put_image(t_var *var, char *name, SDL_Rect dimensions)
{
	SDL_Surface	*image;
	SDL_Texture	*mon_image;

	image = SDL_LoadBMP(name);
	mon_image = SDL_CreateTextureFromSurface(var->sdl.render, image);
	SDL_QueryTexture(mon_image, NULL, NULL, &dimensions.w, &dimensions.h);
	SDL_SetRenderTarget(var->sdl.render, mon_image);
	SDL_RenderCopy(var->sdl.render, mon_image, NULL, &dimensions);
	SDL_FreeSurface(image);
	SDL_DestroyTexture(mon_image);
}

void	put_image_opt(t_var *var, int id, SDL_Rect dimensions)
{
	SDL_Texture	*image;

	image = SDL_CreateTextureFromSurface(var->sdl.render, var->key_texture[id]);
	SDL_QueryTexture(image, NULL, NULL, &dimensions.w, &dimensions.h);
	SDL_SetRenderTarget(var->sdl.render, image);
	SDL_RenderCopy(var->sdl.render, image, NULL, &dimensions);
	SDL_DestroyTexture(image);
}
