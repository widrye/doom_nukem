#include "doom_nukem.h"

void    add_mob(t_mob **mob)
{
    t_mob   *new_mob;

    if (!(new_mob = (t_mob *)ft_memalloc(sizeof(t_mob))))
        ft_putendl("error malloc in parsing_mob.c l.8");
    new_mob->next = *mob;
    *mob = new_mob;
    
}
void    add_poly_mob(t_mob **mob)
{
    (*mob)->poly = (t_poly *)ft_memalloc(sizeof(t_poly));
    if ((*mob)->poly != NULL)
    {
        (*mob)->poly->dots[0].x = (*mob)->pos.x - ((*mob)->width / 2);
        (*mob)->poly->dots[0].y = (*mob)->pos.y;
        (*mob)->poly->dots[0].z = (*mob)->pos.z - ((*mob)->height / 2);
        (*mob)->poly->dots[1].x = (*mob)->pos.x + ((*mob)->width / 2);
        (*mob)->poly->dots[1].y = (*mob)->pos.y;
        (*mob)->poly->dots[1].z = (*mob)->pos.z - ((*mob)->height / 2);
        (*mob)->poly->dots[2].x = (*mob)->pos.x + ((*mob)->width / 2);
        (*mob)->poly->dots[2].y = (*mob)->pos.y;
        (*mob)->poly->dots[2].z = (*mob)->pos.z + ((*mob)->height / 2);
        (*mob)->poly->dots[3].x = (*mob)->pos.x - ((*mob)->width / 2);
        (*mob)->poly->dots[3].y = (*mob)->pos.y;
        (*mob)->poly->dots[3].z = (*mob)->pos.z + ((*mob)->height / 2);
    }
}

void    fill_mob_data(t_mob **mob, char **tab, int i)
{   
    add_mob(mob);
    while (ft_strchr(tab[i], '}') == NULL)
    {   
        if (ft_strstr(tab[i], "mob = "))
            (*mob)->name = ft_strdup(ft_strrchr(tab[i], '=') + 1);

        if (ft_strstr(tab[i], "type = "))
            (*mob)->type = ft_atoi(ft_strrchr(tab[i], '=') + 1);
        if (ft_strstr(tab[i], "posx = "))
            (*mob)->pos.x = ft_atoi(ft_strrchr(tab[i], '=') + 1);
        if (ft_strstr(tab[i], "posy = "))
            (*mob)->pos.y = ft_atoi(ft_strrchr(tab[i], '=') + 1);
        if (ft_strstr(tab[i], "posz = "))
            (*mob)->pos.z = ft_atoi(ft_strrchr(tab[i], '=') + 1);
        if (ft_strstr(tab[i], "dir = "))
            (*mob)->dir = ft_atoi(ft_strrchr(tab[i], '=') + 1);
        if (ft_strstr(tab[i], "width = "))
        {
            (*mob)->width = ft_atoi(ft_strrchr(tab[i], '=') + 1);
            (*mob)->width_2 = (*mob)->width / 2;
        }
        if (ft_strstr(tab[i], "height = "))
            (*mob)->height = ft_atoi(ft_strrchr(tab[i], '=') + 1);
        if (ft_strstr(tab[i], "velocity = "))
            (*mob)->vel = ft_atoi(ft_strrchr(tab[i], '=') + 1);
        if (ft_strstr(tab[i], "health = "))
            (*mob)->health = ft_atoi(ft_strrchr(tab[i], '=') + 1);
        i++;
        printf("health = %d", (*mob)->health);
    }
    add_poly_mob(mob);
}