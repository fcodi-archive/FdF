/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tpoint_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 18:33:10 by fcodi             #+#    #+#             */
/*   Updated: 2019/10/16 21:29:28 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

extern void				destroy_tpoint_map(t_point **map);
extern void				destroy_tastr_holder(t_astr_holder *holder);
extern t_point			**new_tpoint_map(size_t x_max, size_t y_max);
extern t_astr_holder	*init_tastr_holder(const char *path);

_Bool					fill_tpoint_map(t_point **map, t_astr_holder *holder)
{
	char 		**astr;
	size_t		x;
	size_t		y;

	x = 0;
	y = 0;
	holder->current = holder->head;
	while (holder->current)
	{
		if (!(astr = ft_strsplit(holder->current->astr[x], ',')))
			return (FALSE);
		map[(holder->x_max * y) + x]->x = x;
		map[(holder->x_max * y) + x]->y = y;
		map[(holder->x_max * y) + x]->z = ft_atoi(astr[0]);
		astr[1] ? map[(holder->x_max * y) + x]->color =
				ft_atoi_base(astr[1] + 2, 16) : FALSE;
		x < holder->x_max - 1 ? ++x : ++y && (x = 0);
		holder->current = holder->current->next;
		ft_astr_del(astr);
	}
	return (TRUE);
}

t_point					**init_tpoint_map(const char *path, size_t *x_max,
		size_t *y_max)
{
	t_astr_holder		*holder;
	t_point				**map;

	holder = NULL;
	map = NULL;
	if (!path || !(holder = init_tastr_holder(path))
	|| !(map = new_tpoint_map(holder->x_max, holder->y_max))
	|| !fill_tpoint_map(map, holder))
	{
		destroy_tastr_holder(holder);
		destroy_tpoint_map(map);
		return (NULL);
	}
	*x_max = holder->x_max;
	*y_max = holder->y_max;
	destroy_tastr_holder(holder);
	return (map);
}