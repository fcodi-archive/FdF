/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:38:51 by fcodi             #+#    #+#             */
/*   Updated: 2019/10/12 21:39:00 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fdf.h"

int 			get_int_color(unsigned char	a, unsigned char r, unsigned char g,
							 unsigned char b)
{
	t_color		color;

	color.a = a;
	color.r = r;
	color.g = g;
	color.b = b;
	return (color.integer);
}

void			*delete_tastr(t_astr *tastr)
{
	if (!tastr)
		return ;
	ft_astr_del(tastr->astr);
	tastr->astr = NULL;
	if (tastr->next)
		tastr->next->prev = tastr->prev;
	if (tastr->prev)
		tastr->prev->next = tastr->next;
	tastr->next = NULL;
	tastr->prev = NULL;
	free(tastr);
	tastr = NULL;
}

t_astr			*new_tastr(void)
{
	t_astr	*tastr;

	if (!(tastr = (t_astr *)malloc(sizeof(t_astr))))
		return (NULL);
	tastr->astr = NULL;
	tastr->next = NULL;
	tastr->prev = NULL;
	return (tastr);
}

void			*delete_tastr_all(t_astr_holder *holder)
{
	if (!holder)
		return ;
	if (holder->tail)
	{
		if (holder->tail->prev)
		{
			holder->current = holder->tail;
			while (holder->current)
			{
				delete_tastr(holder->current->next);
				if (holder->current->prev)
					holder->current = holder->current->prev;
				else
					break;
			}
		}
		delete_tastr(holder->head);
	}
}

void			*delete_tastr_holder(t_astr_holder *holder)
{
	if (!holder)
		return ;
	delete_tastr_all(holder);
	free(holder);
	holder = NULL;
}

_Bool			add_tastr(t_astr_holder *holder, char **astr)
{
	if (!holder)
		return (FALSE);
	if (holder->tail)
		holder->current = holder->tail;
	if (!(holder->tail = new_tastr()))
		return (FALSE);
	holder->tail->astr = astr;
	if (holder->head)
	{
		holder->current->next = holder->tail;
		holder->tail->prev = holder->current;
	}
	else
	{
		holder->head = holder->tail;
		holder->current = holder->tail;
	}
	return (TRUE);
}

t_astr_holder	*new_tastr_holder(void)
{
	t_astr_holder	*holder;

	if (!(holder = (t_astr_holder *)malloc(sizeof(t_astr_holder))))
		return (NULL);
	holder->x_max = 0;
	holder->y_max = 0;
	holder->current = NULL;
	holder->head = NULL;
	holder->tail = NULL;
	return (holder);
}

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

_Bool			fdf_fill_tastr_holder(t_astr_holder *holder, const char *path)
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
	|| !(fdf_fill_tastr_holder(holder, argv[1])))
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
