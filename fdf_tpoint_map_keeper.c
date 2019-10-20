/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tpoint_map_keeper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:25:04 by fcodi             #+#    #+#             */
/*   Updated: 2019/10/16 19:51:25 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point_map_keeper				*init_tpoint_map_keeper(const char *path)
{
	t_point_map_keeper			*keeper;

	keeper = NULL;
	if (!path || !(keeper = new_tpoint_map_keeper())
	|| !(keeper->map = init_tpoint_map(path, &keeper->x_max, &keeper->y_max,
			&keeper->z_max)))
	{
		destroy_tpoint_map_keeper(keeper);
		return (NULL);
	}
	return (keeper);
}