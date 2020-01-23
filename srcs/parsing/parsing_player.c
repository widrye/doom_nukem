#include "doom_nukem.h"

void	player_data(char **tab, t_player *player, int i)
{
    int nb;

    nb = 0;
    while (ft_strrchr(tab[i], '}') == NULL)
    {   

        if (ft_strstr(tab[i], "posx ="))
        {
            player->pos_up.x = ft_atoi(ft_strrchr(tab[i], '=') + 1);
            nb++;
        }
        else if (ft_strstr(tab[i], "posy ="))
        {
            player->pos_up.y = ft_atoi(ft_strrchr(tab[i], '=') + 1);
            nb++;
        }
        else if (ft_strstr(tab[i], "posz ="))
        {
            player->pos_up.z = ft_atoi(ft_strrchr(tab[i], '=') + 1);
            nb++;
        }
        else if (ft_strstr(tab[i], "width ="))
        {
            player->width = ft_atoi(ft_strrchr(tab[i], '=') + 1);
            nb++;
        }
        else if (ft_strstr(tab[i], "height ="))
        {
            player->height = ft_atoi(ft_strrchr(tab[i], '=') + 1);
            nb++;
        }
        else if (ft_strstr(tab[i], "sector ="))
        {
            player->numsector = ft_atoi(ft_strrchr(tab[i], '=') + 1);
            nb++;
        }
        else if (ft_strstr(tab[i], "dir ="))
        {
            player->dir_init = _2_PI * (double)ft_atoi(ft_strrchr(tab[i], '=') + 1) / 360;
            nb++;
        }
        else if (ft_strstr(tab[i], "velocity ="))
        {
            player->const_vel = ft_atoi(ft_strrchr(tab[i], '=') + 1);
            nb++;
        }
        i++;
    }
    printf("NB = %d\n", nb);
    if (nb != 7)
    {
        ft_putendl("Error parsing Value player");
        free(tab);
        //free(player);
        exit(0);
    }
    // printf("player | x = %f\ty = %f\tz= %f\n", player->pos_up.x, player->pos_up.y, player->pos_up.y);
	// printf("width = %d\theight = %d\n", player->width, player->height);
	printf("dir = %f\n", player->dir_init);
    //printf("\n");
}
