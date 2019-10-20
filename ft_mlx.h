/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:55:49 by fcodi             #+#    #+#             */
/*   Updated: 2019/10/16 23:27:44 by fcodi            ###   ########.fr       */
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
		struct
		{
			unsigned char	b: 8;
			unsigned char	g: 8;
			unsigned char	r: 8;
			unsigned char	a: 8;
		};
	};
}						t_point;

typedef struct			s_point_map_keeper
{
	t_point				**map;
	size_t				x_max;
	size_t				y_max;
	size_t				z_max;
}						t_point_map_keeper;

typedef struct			s_tmlx
{
	void				*mlx;
	void				*win;
	void				*img;
	int 				*data;
/*	int 				bpp;
	int 				lsize; //TODO А нужны ли они?
	int 				endian;*/ // TODO Временно заместо них int phony
}						t_mlx;

typedef struct s_astr	t_astr;

typedef struct			s_astr_holder
{
	size_t				strlen_max;
	size_t 				line_count;
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
size_t					tastr_length(t_astr *tastr);

t_astr_holder			*new_tastr_holder(void);
t_astr_holder			*init_tastr_holder(const char *path);
void					*destroy_tastr_all(t_astr_holder *holder);
void					destroy_tastr_holder(t_astr_holder *holder);

t_point					**new_tpoint_map(size_t x_max, size_t y_max);
t_point					**init_tpoint_map(const char *path, size_t *x_max,
		size_t *y_max, size_t *z_max);
void					destroy_tpoint_map(t_point **map);

t_point_map_keeper		*new_tpoint_map_keeper(void);
t_point_map_keeper		*init_tpoint_map_keeper(const char *path);
void					destroy_tpoint_map_keeper(t_point_map_keeper *keeper);

t_mlx					*init_tmlx(int win_x, int win_y, char *title);
void					clear_tmlx_data(t_mlx *tmlx);
void					destroy_tmlx(t_mlx *tmlx);

#endif
