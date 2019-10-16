/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tastr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:56:37 by fcodi             #+#    #+#             */
/*   Updated: 2019/10/16 17:18:56 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

size_t			tastr_length(t_astr *tastr)
{
	size_t		len;

	if (!tastr)
		return (0);
	len = 0;
	while (tastr->astr[len])
		++len;
	return (len);
}

void			*destroy_tastr(t_astr *tastr)
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

void			*destroy_tastr_all(t_astr_holder *holder)
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
				destroy_tastr(holder->current->next);
				if (holder->current->prev)
					holder->current = holder->current->prev;
				else
					break;
			}
		}
		destroy_tastr(holder->head);
	}
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