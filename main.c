/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:38:51 by fcodi             #+#    #+#             */
/*   Updated: 2019/10/16 23:32:38 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> //TODO DEL

extern void					destroy_tmlx(t_mlx *tmlx);
extern t_mlx				*init_tmlx(void);
extern void					destroy_tpoint_map_keeper(t_point_map_keeper
*keeper);
extern t_point_map_keeper	*init_tpoint_map_keeper(const char *path);

int 						main(int argc, char **argv)
{
	t_point_map_keeper		*keeper;
	t_mlx					*tmlx;

	if (argc != 2)
	{
		ft_putstr("usage: fdf map_file[.fdf]\n");
		return (ERROR);
	}
	if (!(keeper = init_tpoint_map_keeper(argv[1]))
	|| !(tmlx = init_tmlx()))
	{
		destroy_tpoint_map_keeper(keeper);
		return (ERROR);
	}
	tmlx->data[0] = 0xFFFFFF;
	mlx_put_image_to_window(tmlx->mlx, tmlx->win, tmlx->img, 0,0);
	mlx_loop(tmlx->mlx);
	destroy_tmlx(tmlx);
	destroy_tpoint_map_keeper(keeper);
	return (OK);
}
