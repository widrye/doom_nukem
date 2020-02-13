#include "doom_nukem.h"

// void    set_poly_dots_rotz_only(t_object *object)
static void    set_poly_dots_rotz_only(t_poly *poly, t_fdot_3d pos, float width_2, float height_2)
{
    poly->dots_rotz_only[0].x = pos.x - width_2;
    poly->dots_rotz_only[0].y = pos.y;
    poly->dots_rotz_only[0].z = pos.z - height_2;
    poly->dots_rotz_only[1].x = pos.x + width_2;
    poly->dots_rotz_only[1].y = pos.y;
    poly->dots_rotz_only[1].z = pos.z - height_2;
    poly->dots_rotz_only[2].x = pos.x + width_2;
    poly->dots_rotz_only[2].y = pos.y;
    poly->dots_rotz_only[2].z = pos.z + height_2;
    poly->dots_rotz_only[3].x = pos.x - width_2;
    poly->dots_rotz_only[3].y = pos.y;
    poly->dots_rotz_only[3].z = pos.z + height_2;
	print_poly(poly, 1);
	printf("pos %f %f %f\n", pos.x, pos.y, pos.z);
}

void		add_object(t_object **object)
{	
	t_object *new_object;
	
	new_object = (t_object *)ft_memalloc(sizeof(t_object));
	new_object->next = *object;
	new_object->collide = 1;
	new_object->visible = 1;
	*object = new_object;
}

int			add_poly_object(t_object *object, char *type_str)
{
	// t_enum_object	type;

	if (!ft_strcmp(type_str, "HEAL"))
		object->type = HEAL;
	else if (!ft_strcmp(type_str, "ARMOR"))
		object->type = ARMOR;
	else if (!ft_strcmp(type_str, "TP"))
		object->type = TP;
	else if (!ft_strcmp(type_str, "GUN"))
		object->type = GUN;
	else if (!ft_strcmp(type_str, "BULLET"))
		object->type = BULLET;
	else if (!ft_strcmp(type_str, "GRAVITY_INV"))
	{
		object->type = GRAVITY_INV;
		// printf("Parse gravity_inv\n");
	}
	else if (!ft_strcmp(type_str, "BOX"))
	{
		object->type = BOX;
		set_box_object(object, object->pos_rotz_only, object->width_2, object->height_2);
		return (0);
	}
	else if (!ft_strcmp(type_str, "LIGHT"))
		object->type = LIGHT;
	else
	{
		ft_putendl("Error: Type of object is wrong !");
		return (1);
	}

    if (!(object->poly = (t_poly *)ft_memalloc(sizeof(t_poly))))
		return (1);
	object->poly->object = object;
	object->poly->next = NULL;
	set_poly_dots_rotz_only(object->poly, object->pos_rotz_only, object->width_2, object->height_2);
	return (0);
}

int			object_data(char **tab, t_object **object, int i)
{
	char	*type;

	type = NULL;
	add_object(object);
    (*object)->width = 50;
    (*object)->height = 50;
	while (ft_strchr(tab[i], '}') == NULL)
	{
        if (ft_strstr(tab[i], "type = "))
            type = ft_strdup(ft_strrchr(tab[i], '=') + 2);
        if (ft_strstr(tab[i], "data = "))
        	(*object)->data = ft_atoi(ft_strrchr(tab[i], '=') + 1) / 100.0;
        if (ft_strstr(tab[i], "texture = "))
            (*object)->texture = ft_strdup(ft_strrchr(tab[i], '=') + 2);
        if (ft_strstr(tab[i], "posx = "))
        	(*object)->pos_rotz_only.x = ft_atoi(ft_strrchr(tab[i], '=') + 1);
        if (ft_strstr(tab[i], "posy = "))
            (*object)->pos_rotz_only.y = ft_atoi(ft_strrchr(tab[i], '=') + 1);
        if (ft_strstr(tab[i], "posz = "))
            (*object)->pos_rotz_only.z = ft_atoi(ft_strrchr(tab[i], '=') + 1);
        if (ft_strstr(tab[i], "width = "))
            (*object)->width = ft_atoi(ft_strrchr(tab[i], '=') + 1);
        if (ft_strstr(tab[i], "height = "))
            (*object)->height = ft_atoi(ft_strrchr(tab[i], '=') + 1);
		i++;
	}
    (*object)->width_2 = (*object)->width / 2;
    (*object)->height_2 = (*object)->height / 2;
	if (add_poly_object(*object, type))
		return (1);
	return (0);
	//printf("O |posx = %f\n", object->pos.x);
	// printf("O |posy = %f\n", object->pos.y);
	// printf("\n");
}