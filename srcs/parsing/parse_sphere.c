/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widrye <widrye@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 22:54:45 by agiordan          #+#    #+#             */
/*   Updated: 2020/03/08 05:04:41 by widrye           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void		fill_sphere_pos(t_sphere *sphere, char **tab, int i)
{
	if (ft_strstr(tab[i], "posx ="))
		sphere->pos_rotz_only.x = ft_atoi(ft_strrchr(tab[i], '=') + 1);
	else if (ft_strstr(tab[i], "posy ="))
		sphere->pos_rotz_only.y = ft_atoi(ft_strrchr(tab[i], '=') + 1);
	else if (ft_strstr(tab[i], "posz ="))
		sphere->pos_rotz_only.z = ft_atoi(ft_strrchr(tab[i], '=') + 1);
}

static void		fill_sphere(t_sphere *sphere, char **tab, int i)
{
	char		*tmp;

	while ((ft_strchr(tab[i], '}') == NULL))
	{
		fill_sphere_pos(sphere, tab, i);
		if (ft_strstr(tab[i], "texture = "))
		{
			tmp = ft_strjoin("textures/", ft_strrchr(tab[i], '=') + 2);
			if (!(sphere->texture = IMG_Load(tmp)))
			{
				printf("Texture sphere of the file failed\n");
				exit(0);
				return ;
			}
			sphere->texture = SDL_ConvertSurfaceFormat(\
							sphere->texture, SDL_PIXELFORMAT_ARGB8888, 0);
			ft_strdel(&tmp);
		}
		else if (ft_strstr(tab[i], "radius = "))
			sphere->radius = ft_atoi(ft_strrchr(tab[i], '=') + 2);
		i++;
	}
}

void			new_sphere(t_sphere *sphere, char **tab, int i)
{
	sphere->pos_rotz_only = (t_fdot_3d){0, 0, 0};
	sphere->pos = (t_fdot_3d){0, 0, 0};
	sphere->radius = 1000;
	if (!(sphere->texture = IMG_Load("textures/fractale1.jpg")))
	{
		printf("Default texture sphere failed\n");
		exit(0);
		return ;
	}
	sphere->i_rotz_only = (t_fdot_3d){0, 0, -1};
	sphere->i = (t_fdot_3d){0, 0, -1};
	sphere->j_rotz_only = (t_fdot_3d){1, 0, 0};
	sphere->j = (t_fdot_3d){1, 0, 0};
	fill_sphere(sphere, tab, i);
}
