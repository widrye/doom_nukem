#include "doom_nukem.h"

/*
**	A faire :
**
**	Mobs
**	Objects
**	Gravity mobs, objects
**	Fixer la gestion des menus
**	Norme all
**	Clean code/fichier inutiles
**
**	Multi threading moteurs
**	Seg fault sur certaines text att !
*/

static int		init(t_win *win, t_map *map, t_player *player)
{
	printf("Debut init\n");
	// if (init_textures(win, &(map->textures)))
	// {
	// 	ft_putendl("init_textures failed");
	// 	return (1);
	// }
	if (!init_music(&win->music))
	{
		ft_putendl("init_music failed");
		return (4);
	}
	init_player(win, player);
	init_polygone(map->polys);
	create_poly_save(map);
	return (0);
}

int			main(int argc, char **argv)
{
	int			fd;
	int			fd1;
	int			ret;
	t_win		win;
	t_map		map;
	// SDL_Event	event;

	if (argc == 1 || argc == 2)
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1 || TTF_Init() == -1)
			return (ret_error(SDL_GetError()));
		if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
			return (ret_error(SDL_GetError()));
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
			return (ret_error(SDL_GetError()));
		if ((Mix_Init(MIX_INIT_MP3) & MIX_INIT_MP3) != MIX_INIT_MP3)
			return (ret_error(SDL_GetError()));
		win.w = WIDTH;
		win.h = HEIGHT;
		win.map = &map;
		map.gravity = 4;
		// if (!(create_window(&win, "doom_nukem", (SDL_Rect){0, 0, win.w, win.h}, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)))
		if (!create_window(&win, "doom_nukem", (SDL_Rect){400, 400, win.w, win.h}, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE))
			return (0);
		if (argc == 1)
		{
			init_music(&win.music);
			editor_loop(&win, NULL);
		}
		else
		{
			// if (!(map.polys = polys_a_la_mano(&(map.player))))
			// 	return (1);
			if ((((fd = open(argv[1], O_RDONLY)) <= 0) ||\
				((fd1 = open(argv[1], O_RDONLY)) <= 0)))
				return (ret_error("open error"));
			win.map->polys = ft_data_storing(fd, fd1, &map, &win);
			if ((ret = init(&win, &map, &(map.player))))
				return (ret_num_error("Init error", ret));
			main_menu(&win, &map);
		}
		SDL_DestroyWindow(win.ptr);
		SDL_DestroyRenderer(win.rend);
		SDL_Quit();
	}
	return (0);
}
