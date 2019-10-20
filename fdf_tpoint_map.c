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

_Bool					fill_tpoint_map(t_point **map, t_astr_holder *holder,
		size_t *z_max)
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
		map[(holder->strlen_max * y) + x]->x = x;
		map[(holder->strlen_max * y) + x]->y = y;
		map[(holder->strlen_max * y) + x]->z = ft_atoi(astr[0]);
		map[(holder->strlen_max * y) + x]->z > *z_max ?
		(*z_max = map[(holder->strlen_max * y) + x]->z) : FALSE;
		astr[1] ? map[(holder->strlen_max * y) + x]->color =
				ft_atoi_base(astr[1] + 2, 16) : FALSE;
		x < holder->strlen_max - 1 ? ++x : ++y && (x = 0);
		holder->current = holder->current->next;
		ft_astr_del(astr);
	}
	return (TRUE);
}

t_point					**init_tpoint_map(const char *path, size_t *x_max,
		size_t *y_max, size_t *z_max)
{
	t_astr_holder		*holder;
	t_point				**map;

	holder = NULL;
	map = NULL;
	if (!path || !(holder = init_tastr_holder(path))
	|| !(map = new_tpoint_map(holder->strlen_max, holder->line_count))
	|| !fill_tpoint_map(map, holder, z_max))
	{
		destroy_tastr_holder(holder);
		destroy_tpoint_map(map);
		return (NULL);
	}
	*x_max = holder->strlen_max;
	*y_max = holder->line_count;
	destroy_tastr_holder(holder);
	return (map);
}