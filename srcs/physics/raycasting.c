#include "doom_nukem.h"

/*
**	ATTENTION LE REPERE POUR LES CALCULS EST AUSSI INVERSE :
**	.---->
**	|
**	v
**
**	Trouver la collision :
**	(b1 - b2) / (a2 - a1)
*/

static void			print_wall(t_win *win, t_linedef *wall, t_player *player, int column)
{
	double			h;

	//printf("Adress : %p\t%p\t%f\t%d\n", win, wall, dist, column);
	h = (HEIGHT_WALL - 9 * ft_abs(win->h / 2 - player->orientation)) / player->lenRay;
	if (wall->flags & PORTAL)
		SDL_SetRenderDrawColor(win->rend, 0xDD, 0x40, 0x40, 255);
	else if (wall->flags & WALL)
		SDL_SetRenderDrawColor(win->rend, 0x40, 0xDD, 0x40, 255);
	else
		SDL_SetRenderDrawColor(win->rend, 0x40, 0x40, 0xDD, 255);
	draw_column(win, column, player->orientation - h, player->orientation + h);
}

static void			find_wall(t_win *win, t_player *player, t_calculs *calculs, int column)
{
	t_linedef	*line;
	t_linedef	*wall;
	t_fdot		collision;
	t_fdot		closest;

	calculs->dist = -1;
	wall = NULL;
	//printf("Ad : %p\n", player);
	//printf("Ad : %p\n\n", player->sector);
	line = player->sector->lines;
	while (line)
	{
		if (line->isequation)
		{
			collision.x = ((player->pos.y - calculs->ray.a * player->pos.x) - line->equation.b) /\
							(line->equation.a - calculs->ray.a);
			collision.y = line->equation.a * collision.x + line->equation.b;
			if (((calculs->newdist = fdist(player->pos, collision)) < calculs->dist ||\
				calculs->dist == -1) &&\
				sign(collision.x - player->pos.x) == sign(cos(calculs->alpha)) &&\
				((line->p1.x <= collision.x && collision.x <= line->p2.x) ||\
				(line->p2.x <= collision.x && collision.x <= line->p1.x)))
			{
				calculs->dist = calculs->newdist;
				closest = collision;
				wall = line;
			}
		}
		else
			printf("No equation wall\n");
		//printf("Test wall\n");
		line = line->next;
	}
	player->lenRay = calculs->dist * cos(ft_abs(calculs->alpha - player->dir));
	if (wall)
		print_wall(win, wall, player, column);
	// SDL_SetRenderDrawColor(win->rend, 0, 0, 0, 255);
	// draw_line(win, (t_dot){(int)player->pos.x, (int)player->pos.y}, (t_dot){(int)closest.x, (int)closest.y});
}

int				raycasting(t_win *win, t_player *player)
{
	t_calculs	calculs;
	int			column;
			
	calculs.dangle = player->fov / win->w;
	calculs.alpha = player->dir - player->fov / 2;
	column = -1;
	while (++column < win->w)
	{
		/*if (cos(calculs.alpha) > 0.00001 || cos(calculs.alpha) < -0.00001)
		{*/
			calculs.ray.a = tan(calculs.alpha);
			//calculs.ray.b = player->pos.y - calculs.ray.a * player->pos.x;
			find_wall(win, player, &calculs, column);
		/*}
		else
			;//printf("No equation ray\n");*/
		calculs.alpha += calculs.dangle;
	}
	//printf("Pos : %f\t%f\n", player->pos.x, player->pos.y);
	return (0);
}
