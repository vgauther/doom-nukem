/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamisdra <mamisdra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:08:36 by mamisdra          #+#    #+#             */
/*   Updated: 2019/10/13 18:18:35 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

t_rgb	set_color(int r, int g, int b, int a)
{
	t_rgb c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return (c);
}

Uint32	set_pixel_color(t_rgb c)
{
	return ((c.a << 24) + (c.r << 16) + (c.g << 8) + (c.b << 0));
}

t_rgb	get_color_from_surface(Uint32 x)
{
	t_rgb c;

	c.a = x >> 24 & 255;
	c.r = x >> 16 & 255;
	c.g = x >> 8 & 255;
	c.b = x >> 0 & 255;
	return (c);
}

void	open_wall_texture(t_var *var)
{
	int		i;
	void	*tmp;

	i = 0;
	var->wall_texture[0] = SDL_LoadBMP("./assets/t1.bmp");
	var->wall_texture[1] = SDL_LoadBMP("./assets/t2.bmp");
	var->wall_texture[2] = SDL_LoadBMP("./assets/t3.bmp");
	var->wall_texture[3] = SDL_LoadBMP("./assets/t4.bmp");
	while (i < 4)
	{
		tmp = var->wall_texture[i]->pixels;
		var->wall_uint[i] = (Uint32 *)tmp;
		i++;
	}
}
