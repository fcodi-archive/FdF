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

int				key_hook(int keycode)
{
	if (keycode == 53)
	{
		exit(OK);
	}
	return (OK);
}

int				win_cross_pressed(void)
{
	exit(OK);
}

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
	|| !(tmlx = init_tmlx(0, 0, NULL)))
	{
		destroy_tpoint_map_keeper(keeper);
		return (ERROR);
	}
	tmlx->data[0] = 0xFFFFFF;
	mlx_put_image_to_window(tmlx->mlx, tmlx->win, tmlx->img, WINDOW_X / 2,
			WINDOW_Y / 2);
	mlx_key_hook(tmlx->win, key_hook, NULL);
	mlx_hook(tmlx->win, 17, 0, win_cross_pressed, NULL);
	mlx_loop(tmlx->mlx);
	destroy_tmlx(tmlx);
	destroy_tpoint_map_keeper(keeper);
	return (OK);
}
