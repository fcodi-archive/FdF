/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tmlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 21:44:31 by fcodi             #+#    #+#             */
/*   Updated: 2019/10/16 23:28:17 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

void	clear_tmlx_data(t_mlx *tmlx)
{
	int 	i;

	if (!tmlx)
		return ;
	i = 0;
	while (tmlx->data[i])
		tmlx->data[i++] = 0;
}

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
	return (tmlx);
}

t_mlx	*init_tmlx(int win_x, int win_y, char *title)
{
	t_mlx	*tmlx;
	int 	phony;

	if ((win_x <= 0 || win_y <= 0))
	{
		win_x = WINDOW_X;
		win_y = WINDOW_Y;
	}
	if (!title)
		title = TITLE;
	if (!(tmlx = new_tmlx())
	|| !(tmlx->mlx = mlx_init())
	|| !(tmlx->win = mlx_new_window(tmlx->mlx, win_x, win_y, title))
	|| !(tmlx->img = mlx_new_image(tmlx->mlx, win_x, win_y))
	|| !(tmlx->data = (int *)mlx_get_data_addr(tmlx->img, &phony, &phony,
			&phony)))
	{
		destroy_tmlx(tmlx);
		return (NULL);
	}
	return (tmlx);
}