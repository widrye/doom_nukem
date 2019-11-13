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
				return (1);
			}
			line = line->next;
		}
		sector = sector->next;
	}
	return (0);
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
			line->destline = NULL;
			line->sector = sector;
			line->side = SIDE_RIGHT;
			if (line->flags & PORTAL && !find_portal_id(map, line, line->id))
				return (1);
			if (line->flags & PORTAL)
			{
				if (!(line->texture = IMG_Load("textures/sol.png")))
				{
					ft_putendl(SDL_GetError());
					return (1);
				}
			}
			else
				line->texture = map->textures.tortue;
			printf("Line : %p %p\n", line, line->destline);
			line = line->next;
			// if (set_clockwise(map, sector, line))
			// 	return ();
		}
		sector = sector->next;
	}
	check_lines(map);
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
		if (!(sector->ceil_texture = IMG_Load("textures/mur_pierre.png")) ||
			!(sector->floor_texture = IMG_Load("textures/sol.png")))
		{
			ft_putendl(SDL_GetError());
			return (1);
		}
		if (sector->floor_height >= sector->ceil_height)
			return (1);
		sector->height = sector->ceil_height - sector->floor_height;
		// printf("Ceil height = %d\n", sector->ceil_height);
		sector->ceil_equation =		(t_plan){0, 0, 1, -sector->ceil_height};
		sector->floor_equation =	(t_plan){0, 0, 1, -sector->floor_height};
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
	player->win_w = win->w;
	player->win_h = win->h;
	player->pos_up = (t_fdot_3d){	player->pos.x,\
									player->pos.y,\
									player->sector->floor_height + player->height};
	player->inventory = define_inventory();
	player->dir = 0;
	player->fov = _PI_4;
	player->dir_up = 0;
	player->fov_up = _PI_4;
	player->ddir = 0.1;
	if (init_rays(win, player))
		return (ft_putendl("Erreur malloc rays"));
	player->maxHp = 50;
	player->currentHp = player->maxHp;
	player->maxArmor = 50;
	player->currentArmor = player->maxArmor;
	player->inventory->ammo = 15;
	player->inventory->magazine = 120;
	player->width_2 = player->width / 2;
	player->width_10 = player->width / 10;
	start_cooldown(&(player->timers.bullet_cd), 130);
	start_cooldown(&(player->timers.item_cd), 200);
	start_cooldown(&(player->timers.text_cd), 600);
	start_cooldown(&(player->timers.reload_cd), 600);
	start_cooldown(&(player->timers.animation_cd), 1000);
	start_cooldown(&(player->timers.shot_cd), 50);
	start_cooldown(&(player->timers.animation_shot_cd), 10);
    start_cooldown(&(player->timers.mouse), 10);
    player->timers.reload_cd.index = 5;
    player->timers.bullet_cd.index = 5;
    player->timers.bullet_cd.index = 0;
	define_line_shot(win, player);



	// t_cartesienne	ray = (t_cartesienne){0, 0, 0, 1, 1, 1, 0, 0, NULL};
	// t_fdot_3d		collision = (t_fdot_3d){0, 0, 0};
	// printf("Sence %d\n", sence(ray, collision));
	// printf("V %f %f %f / %f %f %f\n", line.ox, line.oy, line.oz, line.vx, line.vy, line.vz);
	// exit(0);
}

int		init_textures(t_textures *textures)
{
	if (!(textures->elephantride = IMG_Load("textures/walls/elephantride.png")) ||
		!(textures->tortue = IMG_Load("textures/walls/randomPNG/Brick.png")))
		// !(textures->tortue = IMG_Load("textures/walls/moine.png")))
		// !(textures->tortue = IMG_Load("textures/walls/tortue.png")))
	{
		ft_putendl(SDL_GetError());
		return (1);
	}
	return (0);
}


int		init_music(t_doom_music	*music)
{
	if (music)
	{
		if (!(music->editor_music = Mix_LoadMUS("sounds/map_editor.wav")))
			return (ret_error(SDL_GetError()));
		if (!(music->credit_music = Mix_LoadMUS("sounds/Remember_chill.mp3")))
			return (ret_error(SDL_GetError()));
		if (!(music->menu_music = Mix_LoadMUS("sounds/doomMenu.wav")))
			return (ret_error(SDL_GetError()));
	}
	return (1);
}