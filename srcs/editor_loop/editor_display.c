#include "doom_nukem.h"

static void			display_linedefs(t_win *win, const t_map_editor *map, t_sector *s)
{
	t_dot		p1;
	t_dot		p2;
	t_linedef	*l;

	l = s->lines;
	while (l)
	{
		if (l->flags & LINEDEF_SELECTED)
			SDL_SetRenderDrawColor(win->rend, 0, 175, 175, 255);
		else if (l->flags & LINEDEF_MOUSE_POINTED)
			SDL_SetRenderDrawColor(win->rend, 50, 150, 150, 255);
		else
		{
			if (l->gflags & WALL)
				SDL_SetRenderDrawColor(win->rend, 200, 200, 200, 255);
			else if (l->gflags & PORTAL)
				SDL_SetRenderDrawColor(win->rend, 200, 0, 200, 255);
		// 	SDL_SetRenderDrawColor(win->rend, s->color.selected_color.r,
		// 										s->color.selected_color.g,
		// 										s->color.selected_color.b,
		// 										s->color.selected_color.a);
		}
		p1 = (t_dot){l->p1.x * map->unit + map->x, l->p1.y * map->unit + map->y};
		p2 = (t_dot){l->p2.x * map->unit + map->x, l->p2.y * map->unit + map->y};
		if (is_in_screen(win, p1) || is_in_screen(win, p2))
			draw_line(win, p1, p2);
		l = l->next;
	}
}

static void			display_buttons(t_win *win, t_frame *f)
{
	t_button	*b;

	b = f->buttons;
	while (b)
	{
		if (b->texture)
			SDL_RenderCopy(win->rend, b->texture, NULL, &b->rect);
		else
			draw_ratio_rect(win, &f->rect, &b->ratio);
		b = b->next;
	}
}

static void			display_frames(t_win *win)
{
	t_frame		*f;

	SDL_SetRenderDrawColor(win->rend, 200, 200, 200, 255);
	f = win->frames;
	while (f)
	{
		if (!(f->flags & FRAME_HIDE))
		{
			if (f->texture)
				SDL_RenderCopy(win->rend, f->texture, NULL, &f->rect);
			else
				draw_ratio_rect(win, &(SDL_Rect){0, 0, win->w, win->h}, &f->ratio);
			display_buttons(win, f);
		}
		f = f->next;
	}
}

void			editor_display(t_win *win, const t_map_editor *map)
{
	t_sector	*s;

	SDL_SetRenderDrawColor(win->rend, 100, 100, 100, 255);
	draw_rect(win, (SDL_Rect){map->x, map->y, map->w * map->unit, map->h * map->unit});
	if (map->selected_sector)
	{
		s = map->selected_sector;
		display_linedefs(win, map, s);
	}
	display_frames(win);
	SDL_SetRenderDrawColor(win->rend, 150, 150, 150, 200);
	if (map->flags & MAP_SELECTING)
		draw_rect(win, map->rect_util);
	// draw_fps();
}