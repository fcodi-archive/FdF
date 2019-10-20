/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tastr_holder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:04:14 by fcodi             #+#    #+#             */
/*   Updated: 2019/10/16 19:58:44 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

_Bool					fill_tastr_holder(t_astr_holder *holder,
										   const int fd)
{
	char 		*line;
	int 		gnl_result;
	_Bool		is_first_time;

	if (!holder || fd <= STDERR)
		return (FALSE);
	is_first_time = TRUE;
	while ((gnl_result = get_next_line(fd, &line)) > 0)
	{
		if (!add_tastr(holder, ft_strsplit(line, ' ')))
		{
			ft_strdel(&line);
			return (FALSE);
		}
		holder->line_count++;
		if (is_first_time ? !(is_first_time = FALSE) : FALSE)
			holder->strlen_max = tastr_length(holder->tail);
		else if (tastr_length(holder->tail) < holder->strlen_max)
		{
			ft_strdel(&line);
			return (FALSE);
		}
		ft_strdel(&line);
	}
	return (gnl_result == 0 ? TRUE : FALSE);
}

t_astr_holder			*init_tastr_holder(const char *path)
{
	t_astr_holder	*holder;
	int 			fd;

	holder = NULL;
	fd = 0;
	if (!path || !(holder = new_tastr_holder())
		|| (fd = open(path, O_RDONLY)) <= STDERR
		|| !fill_tastr_holder(holder, fd))
	{
		destroy_tastr_holder(holder);
		close(fd);
		return (NULL);
	}
	return (holder);
}