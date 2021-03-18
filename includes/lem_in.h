/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:29:14 by rkyttala          #+#    #+#             */
/*   Updated: 2021/03/18 21:36:37 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define SIZE 10000

# include <stdlib.h>
# include <unistd.h>
# include "../libft/includes/libft.h"

typedef struct	s_lem
{
	int	ants;
	int	start;
	int	finish;
}				t_lem;

typedef struct	s_input
{
	char	*line;
	t_input	*next;
}				t_input;

typedef	struct	s_room
{
	char	*id;
	int		x;
	int		y;
	int		checked;
	int		occupied;
	t_room	*next;
}				t_room;

typedef struct	s_link
{
	int		src;
	int		dst;
	int		cost;
	t_link	*next;
}				t_link;

typedef struct	s_index
{
	t_room	**rooms;
}				t_index;

#endif
