#ifndef STRUCT_2D_H
# define STRUCT_2D_H

# include "stdlib.h"

typedef struct		s_dot
{
	int				x;
	int				y;
}					t_dot;

typedef struct		s_line
{
	t_dot			p1;
	t_dot			p2;
}					t_line;

typedef struct		s_affine
{
	double			a;
	double			b;
}					t_affine;

typedef struct		s_fdot
{
	double			x;
	double			y;
}					t_fdot;

typedef struct		s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct		s_len
{
	unsigned int	x;
	unsigned int	y;
}					t_len;

typedef struct		s_interval
{
	int				start;
	int				end;
}					t_interval;

typedef struct		s_index
{
	unsigned int	i;
	unsigned int	j;
}					t_index;

#endif