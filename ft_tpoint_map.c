/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tpoint_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:04:55 by fcodi             #+#    #+#             */
/*   Updated: 2019/10/16 17:09:37 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

void			destroy_tpoint_map(t_point **map)
{
	size_t		i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i++] = NULL;
	}
}

t_point			**new_tpoint_map(size_t x_max, size_t y_max)
{
	t_point		**map;
	unsigned	i;

	if (x_max == 0 || !(map = (t_point **)
			malloc(sizeof(t_point *) * ((x_max * y_max) + 1))))
		return (NULL);
	map[x_max * y_max] = NULL;
	i = 0;
	while (i < (x_max * y_max) && (map[i] = (t_point *)malloc(sizeof(t_point))))
	{
		map[i]->x = 0;
		map[i]->y = 0;
		map[i]->z = 0;
		map[i++]->color = 0;
	}
	if (i < (x_max * y_max) - 1)
	{
		destroy_tpoint_map(map);
		return (NULL);
	}
	return (map);
}