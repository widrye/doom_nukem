#include "ui_win.h"
#include "libft.h"

t_text_area		*ui_get_text_area_button(t_winui *win, const char *id)
{
	t_frame		*f;
	t_button	*b;

	f = win->ui.frames;
	while (f)
	{
		b = f->buttons;
		while (b)
		{
			if (b->type == UI_BUTTON_TEXT_AREA && ft_strcmp(id, b->id) == 0)
				return (b->data);
			b = b->next;
		}
		f = f->next;
	}
	return (NULL);
}