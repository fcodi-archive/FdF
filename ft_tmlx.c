/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tmlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 21:44:31 by fcodi             #+#    #+#             */
/*   Updated: 2019/10/16 21:55:51 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

void	destroy_tmlx(t_mlx *tmlx)
{
	if (!tmlx)
		return ;
	if (tmlx->img)
	{
		if (tmlx->data)
		{
			free(tmlx->data);
			tmlx->data = NULL;
		}
		mlx_destroy_image(tmlx->mlx, tmlx->img);
		tmlx->img = NULL;
	}
	if (tmlx->win)
	{
		mlx_destroy_window(tmlx->mlx, tmlx->win);
		tmlx->win = NULL;
	}
	free(tmlx->mlx);
	tmlx->mlx = NULL;
	free(tmlx);
	tmlx = NULL;
}

t_mlx	*new_tmlx(void)
{
	t_mlx	*tmlx;

	if (!(tmlx = (t_mlx *)malloc(sizeof(t_mlx))))
		return (NULL);
	tmlx->mlx = NULL;
	tmlx->win = NULL;
	tmlx->img = NULL;
	tmlx->data = NULL;
	tmlx->bpp = 0;
	tmlx->lsize = 0;
	tmlx->endian = 0;
	return (tmlx);
}

t_mlx	*init_tmlx(void)
{
	t_mlx	*tmlx;

	if (!(tmlx = new_tmlx())
	|| !(tmlx->mlx = mlx_init())
	|| !(tmlx->win = mlx_new_window(tmlx->mlx, WINDOW_X, WINDOW_Y, TITLE))
	|| !(tmlx->img = mlx_new_image(tmlx->mlx, WINDOW_X, WINDOW_Y))
	|| !(tmlx->data = mlx_get_data_addr(tmlx->img, &tmlx->bpp, &tmlx->lsize,
			&tmlx->endian)))
	{
		destroy_tmlx(tmlx);
		return (NULL);
	}
	return (tmlx);
}