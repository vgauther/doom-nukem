/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_the_music_play.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:55:54 by vgauther          #+#    #+#             */
/*   Updated: 2019/12/07 21:03:52 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int let_the_music_play(void)
{
	Mix_Music 		*musique;

	if ((Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0))
	{
		ft_putstr("Mix_OpenAudio ERROR");
		return (1);
	}
	musique = Mix_LoadMUS("./music/mu.wav");
	Mix_PlayMusic(musique, -1);
	return (0);
}
