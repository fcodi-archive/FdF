/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tastr_holder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:58:01 by fcodi             #+#    #+#             */
/*   Updated: 2019/10/16 18:31:25 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

extern void		*destroy_tastr_all(t_astr_holder *holder);

extern size_t	tastr_length(t_astr *tastr);

void			destroy_tastr_holder(t_astr_holder *holder)
{
	if (!holder)
		return ;
	destroy_tastr_all(holder);
	free(holder);
	holder = NULL;
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