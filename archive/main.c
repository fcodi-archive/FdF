/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:38:51 by fcodi             #+#    #+#             */
/*   Updated: 2019/10/16 16:49:33 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fdf.h"

int 			ft_tastr_get_x_max(char **astr)
{
	int 		count;

	if (!astr)
		return (ERROR);
	count = 0;
	while (astr[count])
		++count;
	return (count ? count : ERROR);
}

_Bool			init_tastr_holder(t_astr_holder *holder, const char *path)
{
	int 		fd;
	int 		gnl_result;
	_Bool		add_result;
	_Bool		is_first_line;
	char 		*line;

	if ((fd = open(path, O_RDONLY)) <= STDERR)
		return (FALSE);
	add_result = FALSE;
	is_first_line = TRUE;
	while ((gnl_result = get_next_line(fd, &line)) > 0)
		if ((add_result = add_tastr(holder, ft_strsplit(line, ' '))))
		{
			if (is_first_line
				&& (holder->x_max = ft_tastr_get_x_max(holder->tail->astr)))
				is_first_line = FALSE;
			holder->y_max++;
			ft_strdel(&line);
		}
		else
			break ;
	!add_result || gnl_result <= ERROR ? delete_tastr_holder(holder) : FALSE;
	line ? ft_strdel(&line) : FALSE;
	close(fd);
	return (!gnl_result && add_result ? TRUE : FALSE);
}

void			**delete_map(t_point **map)
{
	int 		i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
	}
	free(map);
	map = NULL;
}

t_point			**new_map(unsigned x_max, unsigned y_max)
{
	t_point		**map;
	unsigned	i;

	if ((x_max == 0 || (x_max > 0 && y_max == 0))
		|| !(map = (t_point **)malloc(
			sizeof(t_point *) * (x_max * y_max) + 1)))
		return (NULL);
	map[x_max * y_max] = NULL;
	i = 0;
	while (i < x_max * y_max)
		if ((map[i] = (t_point *)malloc(sizeof(t_point))))
		{
			map[i]->x = 0;
			map[i]->y = 0;
			map[i]->z = 0;
			map[i]->color = 0;
			++i;
		}
		else
		{
			delete_map(map);
			return (NULL);
		}
	return (map);
}

t_point			**fdf_fill_map(t_astr_holder *holder)
{
	t_point		**map;
	char 		**astr;
	int 		x;
	int 		y;
	int 		i;

	if (!(map = new_map(holder->x_max, holder->y_max)))
		return (NULL);
	holder->current = holder->head;
	x = 0;
	y = 0;
	i = 0;
	while (y < holder->y_max && holder->current->astr[i])
	{
		if (!(astr = ft_strsplit(holder->current->astr[i++], ',')))
		{
			delete_map(map);
			ft_astr_del(astr);
			return (NULL);
		}
		map[(holder->x_max * y) + x]->z = ft_atoi(astr[0]);
		map[(holder->x_max * y) + x]->x = x;
		map[(holder->x_max * y) + x]->y = y;
		astr[1] ? map[(holder->x_max * y) + x]->color =
						  ft_atoi_base(astr[1] + 2, 16) : FALSE;
		x == holder->x_max - 1 ? (x = 0) && ++y : ++x;
		ft_astr_del(astr);
	}
	return (map);
}

_Bool			fdf_validate_map(t_astr_holder *holder)
{
	int 		i;

	if (!holder)
		return (FALSE);
	holder->current = holder->head;
	while (holder->current)
	{
		i = 0;
		while (holder->current->astr[i])
			++i;
		if (i < holder->x_max)
			return (FALSE);
		if (holder->current->next)
			holder->current = holder->current->next;
		else
			break ;
	}
	return (TRUE);
}

int 			main(int argc, char **argv)
{
	t_astr_holder	*holder;
	t_point			**map;

	if (argc != 2)
	{
		ft_putstr("usage: fdf map_file[.fdf]\n");
		return (ERROR);
	}
	if (!(holder = new_tastr_holder())
		|| !(init_tastr_holder(holder, argv[1])))
		return (ERROR);
	if (!fdf_validate_map(holder) || !(map = fdf_fill_map(holder)))
	{
		delete_tastr_holder(holder);
		return (ERROR);
	}
	delete_map(map);
	delete_tastr_holder(holder);
	return (OK);
}
