#include "doom_nukem.h"

static int		find_portal_id(t_map *map, t_linedef *line1, int id)
{
	t_sector	*sector;
	t_linedef	*line;

	sector = map->sectors;
	while (sector)
	{
		line = sector->lines;
		while (line)
		{
			if (id == line->id && line1 != line)
			{
				line1->destline = line;
				return (0);
			}
			line = line->next;
		}
		sector = sector->next;
	}
	return (1);
}

// static int	set_clockwise(t_map *map, t_sector *sector, t_linedef *line)
// {
// 	if (line->next && line->next->side == line->side)
// 	{
// 		if (line->next->p1.x == line->p2.x && line->next->p1.y == line->p2.y)
// 			return (0);
// 		else
// 			ft_swap(&(line->next->p1), &(line->next->p2));
// 	}
// 	else
// 	{

// 	}
// }

static void	check_lines(t_map *map)
{
	t_sector	*sector;
	t_linedef	*line;
	t_linedef	*last;
	t_linedef	*tmp;

	sector = map->sectors;
	while (sector)
	{
		last = NULL;
		line = sector->lines;
		while (line)
		{
			if (line->p1.x == line->p2.x && line->p1.y == line->p2.y)
			{
				if (last)
					last->next = line->next;
				else
					sector->lines = line->next;
				ft_strdel(&(line->name));
				tmp = line;
				line = line->next;
				free(tmp);
			}
			else
			{
				last = line;
				line = line->next;
			}
		}
		sector = sector->next;
	}
}

int		init_lines(t_map *map)
{
	t_sector	*sector;
	t_linedef	*line;

	sector = map->sectors;
	while (sector)
	{
		line = sector->lines;
		while (line)
		{
			line->texture = map->textures.tortue;
			line->sector = sector;
			line->side = SIDE_RIGHT;
			if (line->flags & PORTAL && find_portal_id(map, line, line->id))
				return (1);
			line = line->next;
			check_lines(map);
			// if (set_clockwise(map, sector, line))
			// 	return ();
		}
		sector = sector->next;
	}
	return (0);
}

// static void		set_center(t_map *map)
// {
// 	t_sector	*sector;
// 	t_linedef	*line;
// 	int			ndot;

// 	ndot = 0;
// 	sector = map->sectors;
// 	while (sector)
// 	{
// 		ndot = 0;
// 		line = sector->lines;
// 		while (line)
// 		{
// 			sector->center.x += line->p1.x;
// 			sector->center.y += line->p1.y;
// 			ndot++;
// 			line = line->next;
// 		}
// 		if (ndot)
// 		{
// 			sector->center.x /= ndot;
// 			sector->center.y /= ndot;
// 		}
// 		printf("Center : %d\t%d\tndot : %d\n", sector->center.x, sector->center.y, ndot);
// 		sector = sector->next;
// 	}
// }

int		init_sectors(t_map *map, t_player *player)
{
	t_sector	*sector;
	int			i;

	//set_center(map);
	sector = map->sectors;
	while (sector)
	{
		if (sector->floor_height >= sector->ceil_height)
			return (1);
		sector->height = sector->ceil_height - sector->floor_height;
		sector = sector->next;
	}
	player->sector = map->sectors;
	i = -1;
	while (++i < player->numsector)
		player->sector = player->sector->next;
	return (0);
}

void	init_player(t_win *win, t_player *player)
{
	player->dir = M_PI_2;
	player->orientation = win->h / 2;
	player->fov = M_PI / 2;
	player->maxHp = 50;
	player->currentHp = player->maxHp;
	player->maxArmor = 50;
	player->currentArmor = player->maxArmor;
	player->ammo = 30;
	player->magazine = 120;
	player->demipetitaxe = player->width / 10;
}

int		init_textures(t_textures *textures)
{
	if (!(textures->elephantride = IMG_Load("textures/walls/elephantride.png")) ||
		!(textures->tortue = IMG_Load("textures/walls/tortue.png")))
	{
		ft_putendl(SDL_GetError());
		return (1);
	}
	return (0);
}
