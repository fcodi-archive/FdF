/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:42:54 by fcodi             #+#    #+#             */
/*   Updated: 2019/10/12 16:09:28 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define DEBUG

# include "libft/libft.h"

typedef union			u_color
{
	int					integer;
	struct
	{
		unsigned char	b: 8;
		unsigned char	g: 8;
		unsigned char	r: 8;
		unsigned char	a: 8;
	};
}						t_color;

typedef struct s_astr	t_astr;

typedef struct			s_astr_holder
{
	int 				x_max;
	int 				y_max;
	t_astr				*head;
	t_astr				*tail;
	t_astr				*current;
}						t_astr_holder;

struct					s_astr
{
	char 				**astr;
	t_astr				*next;
	t_astr				*prev;
};

typedef	struct			s_point
{
	long double			x;
	long double			y;
	long double			z;
	int 				color;
}						t_point;

#endif
