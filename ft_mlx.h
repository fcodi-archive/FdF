/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:55:49 by fcodi             #+#    #+#             */
/*   Updated: 2019/10/16 18:55:50 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_H
# define FT_MLX_H
# ifndef RESOLUTION
#  define RESOLUTION
#  define WINDOW_X 640
#  define WINDOW_Y 480
# endif
# ifndef TITLE
#  define TITLE "SampleText"
# endif
# define DEBUG //TODO DEL

# include <mlx.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct			s_point
{
	long double			x;
	long double 		y;
	long double 		z;
	union
	{
		int				color;
		unsigned char	b: 8;
		unsigned char	g: 8;
		unsigned char	r: 8;
		unsigned char	a: 8;
	};
}						t_point;

typedef struct			s_point_map_keeper
{
	t_point				**map;
	size_t				x_max;
	size_t				y_max;
}						t_point_map_keeper;

typedef struct			s_tmlx
{
	void				*mlx;
	void				*win;
	void				*img;
	void				*data;
	int 				bpp;
	int 				lsize;
	int 				endian;
}						t_mlx;

typedef struct s_astr	t_astr;

typedef struct			s_astr_holder
{
	size_t				x_max;
	size_t 				y_max;
	t_astr				*head;
	t_astr				*tail;
	t_astr				*current;
}						t_astr_holder;

struct					s_astr
{
	char 				**astr;
	t_astr				*next;
	t_astr				*prev;
};

_Bool					add_tastr(t_astr_holder *holder, char **astr);

#endif
