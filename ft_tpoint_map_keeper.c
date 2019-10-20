/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tpoint_map_keeper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:44:49 by fcodi             #+#    #+#             */
/*   Updated: 2019/10/16 19:25:28 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

void					destroy_tpoint_map_keeper(t_point_map_keeper *keeper)
{
	if (!keeper)
		return ;
	keeper->map ? destroy_tpoint_map(keeper->map) : FALSE;
	free(keeper);
	keeper = NULL;
}

t_point_map_keeper		*new_tpoint_map_keeper(void)
{
	t_point_map_keeper		*keeper;

	if (!(keeper = (t_point_map_keeper *)malloc(sizeof(t_point_map_keeper))))
		return (NULL);
	keeper->map = NULL;
	keeper->x_max = 0;
	keeper->y_max = 0;
	keeper->z_max = 0;
	return (keeper);
}