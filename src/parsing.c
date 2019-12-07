/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamisdra <mamisdra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 11:51:53 by mamisdra          #+#    #+#             */
/*   Updated: 2019/12/07 14:55:59 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

// Besoin de crée fonction d'erreur pour les malloc etc.. en attendant exit 1

void	init_count(t_var *var)
{
	var->p_count = 0;
	var->w_count = 0;
	var->e_count = 0;
	var->s_count = 0;
	var->m_count = 0;
}

void  fill_resume(t_var *var, char *buff)
{
  int i;

  i = 3;
  if (!(var->points = malloc(sizeof(t_point * ft_atoi(buff + i) + 1))))
    exit(1);
  while (buff[i] != '\0' && buff[i] != ',')
    i++;
  i++;
  if (!(var->sectors = malloc(sizeof(t_sector * ft_atoi(buff + i) + 1))))
    exit(1);
  while (buff[i] != '\0' && buff[i] != ',')
    i++;
  i++;
  if (!(var->maps = malloc(sizeof(t_map * ft_atoi(buff + i) + 1))))
    exit(1);
  while (buff[i] != '\0' && buff[i] != ',')
    i++;
  i++;
  if (!(var->weapons = malloc(sizeof(t_weapon * ft_atoi(buff + i) + 1))))
    exit(1);
  while (buff[i] != '\0' && buff[i] != ',')
    i++;
  i++;
  if (!(var->ennemies = malloc(sizeof(t_ennemy * ft_atoi(buff + i) + 1))))
    exit(1);

}

void  fill_points(t_var *var, char *buff)
{
  int i;

  i = 3;
  var->points[var->p_count].x = ft_atoi(buff + i);
  while (buff[i] != '\0' && buff[i] != ',')
    i++;
  i++;
  var->points[var->p_count].y = ft_atoi(buff + i);
  var->p_count++;
}

void  fill_weapons(t_var *var, char *buff)
{
  int i;
  int x;

  i = 3;
  x = 0;
  while (buff[i] != '\0' && buff[i] != ',')
  {
    var->weapons[var->w_count].name[x] = buff[i];
    i++;
    x++;
  }
  var->weapons[var->w_count].name[x] = '\0';
  i++;
  var->weapons[var->w_count].maga = ft_atoi(buff + i);
  while (buff[i] != '\0' && buff[i] != ',')
    i++;
  i++;
  var->weapons[var->w_count].ammo = ft_atoi(buff + i);
  var->w_count++;
}

void  fill_ennemies(t_var *var, char *buff)
{
  int i;
  int x;

  i = 3;
  x = 0;
  while (buff[i] != '\0' && buff[i] != ',')
  {
    var->ennemies[var->e_count].name[x] = buff[i];
    i++;
    x++;
  }
  var->ennemies[var->e_count].name[x] = '\0';
  i++;
  var->ennemies[var->e_count].hp = ft_atoi(buff + i);
  while (buff[i] != '\0' && buff[i] != ',')
    i++;
  i++;
  var->ennemies[var->e_count].xp = ft_atoi(buff + i);
  var->e_count++;
}

void fill_sectors(t_var *var, char *buff)
{
  int i;
  int x;

  i = 3;
  x = 0;
  var->sectors[var->s_count].nb_pts = (unsigned int)ft_atoi(buff + i);
  var->sectors[var->s_count].pts = malloc(sizeof(int * ft_atoi(buff + i) + 1));
  var->sectors[var->s_count].neighbors = malloc(sizeof(int * ft_atoi(buff + i) + 1));
  var->sectors[var->s_count].textures = malloc(sizeof(int * ft_atoi(buff + i) + 1))
  while (buff[i] != '\0' && buff[i] != ',')
    i++;
  i++;
  while (buff[i] != '\0' && x < var->sectors[var->s_count].nb_pts)
  {
    var->sectors[var->s_count].pts[x] = ft_atoi(buff + i);
    while (buff[i] != '\0' && buff[i] != ',' && buff[i] != '|')
      i++;
    i++;
    x++;
  }
  var->sectors[var->s_count].floor = ft_atoi(buff + i);
  while (buff[i] != '\0' && buff[i] != ',')
    i++;
  i++;
  var->sectors[var->s_count].ceilling = ft_atoi(buff + i);
  while (buff[i] != '\0' && buff[i] != '|')
    i++;
  i++;
  x = 0;
  while (buff[i] != '\0' && x < var->sectors[var->s_count].nb_pts)
  {
    var->sectors[var->s_count].neighbors[x] = ft_atoi(buff + i);
    while (buff[i] != '\0' && buff[i] != ',' && buff[i] != '|')
      i++;
    i++;
    x++;
  }
  x = 0;
  while (buff[i] != '\0' && x < var->sectors[var->s_count].nb_pts)
  {
    var->sectors[var->s_count].textures[x] = ft_atoi(buff + i);
    while (buff[i] != '\0' && buff[i] != ',' && buff[i] != ']')
      i++;
    i++;
    x++;
  }
  var->s_count++;
}

void  fill_maps(t_var *var, char *buff)
{
  int i;
  int x;

  i = 3;
  x = 0;
  var->maps[var->m_count].nb_sectors = (unsigned int)ft_atoi(buff + i);
  if (!(var->maps[var->m_count].sectors = malloc(sizeof(int * ft_atoi(buff + i) + 1))))
    exit(1);
  while (buff[i] != '\0' && x < var->maps[var->m_count].nb_sectors)
  {
    var->maps[var->m_count].sectors[x] = ft_atoi(buff + i);
    while (buff[i] != '\0' && buff[i] != ',' && buff[i] != '|')
      i++;
    i++;
    x++;
  }
  x = 0;
  var->maps[var->m_count].nb_weapons = (unsigned int)ft_atoi(buff + i);
  if (var->maps[var->m_count].nb_weapons == 0)
    i += 4;
  else
  {
    if (!(var->maps[var->m_count].weapons = malloc(sizeof(int * ft_atoi(buff + i) + 1))))
      exit(1);
    while (buff[i] != '\0' && x < var->map[var->m_count].nb_weapons)
    {
      var->maps[var->m_count].weapons[x] = ft_atoi(buff + i);
      while (buff[i] != '\0' && buff[i] != ',')
        i++;
      i++;
      var->weapons[var->maps[var->m_count].weapons[x]].x = ft_atoi(buff + i);
      while (buff[i] != '\0' && buff[i] != ',')
        i++;
      i++;
      var->weapons[var->maps[var->m_count].weapons[x]].y = ft_atoi(buff + i);
      while (buff[i] != '\0' && buff[i] != ',' && buff[i] != '|')
        i++;
      i++;
      x++;
    }
  }
  x = 0;
  var->maps[var->m_count].nb_ennemies = (unsigned int)ft_atoi(buff + i);
  if (var->maps[var->m_count].nb_ennemies != 0)
  {
    if (!(var->maps[var->m_count].ennemies = malloc(sizeof(int * ft_atoi(buff + i) + 1))))
      exit(1);
    while (buff[i] != '\0' && x < var->maps[var->m_count].nb_ennemies)
    {
      var->maps[var->m_count].ennemies[x] = ft_atoi(buff + i);
      while (buff[i] != '\0' && buff[i] != ',')
        i++;
      i++;
      var->ennemies[var->maps[var->m_count].ennemies[x]].x = ft_atoi(buff + i);
      while (buff[i] != '\0' && buff[i] != ',')
        i++;
      i++;
      var->ennemies[var->maps[var->m_count].ennemies[x]].y = ft_atoi(buff + i);
      while (buff[i] != '\0' && buff[i] != ',' && buff[i] != ']')
        i++;
      i++;
      x++;
    }
  }
  var->m_count;
}

void	fill_data_struct(t_var *var)
{
	char	*buff;
	int		fd;
	int		ret;

	init_count(var);
	if ((fd = open("data.emrv", O_RDONLY)) < 0)
	 		exit(1);
	while ((ret = get_next_line(fd, &buff)))
	{
		if (buff[0] != '\0' && (buff[0] != '#')
		{
			if (buff[0] == '[' && buff[1] == 'r')
				fill_resume(var, buff);
			else if (buff[0] == '[' && buff[1] == 'p')
				fill_points(var, buff);
			else if (buff[0] == '[' && buff[1] == 'w')
				fill_weapons(var, buff);
			else if (buff[0] == '[' && buff[1] == 'e')
				fill_ennemies(var, buff);
			else if (buff[0] == '[' && buff[1] == 's')
				fill_sectors(var, buff);
			else if (buff[0] == '[' && buff[1] == 'm')
				fill_maps(var, buff);
		}
    free(buff);
	}
	close(fd);
}
