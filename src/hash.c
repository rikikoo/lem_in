/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:41:11 by rkyttala          #+#    #+#             */
/*   Updated: 2021/04/30 14:49:57 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_index	*init_index(void)
{
	t_index	*index;
	int		i;

	index = (t_index *)malloc(sizeof(t_index));
	if (!index)
		return (NULL);
	index->rooms = (t_room **)malloc(sizeof(t_room *) * HT_SIZE);
	if (!index->rooms)
		return (NULL);
	i = 0;
	while (i < HT_SIZE)
	{
		index->rooms[i] = NULL;
		i++;
	}
	return (index);
}

t_room	*new_room(const char *key, const int x, const int y)
{
	t_room	*room;

	room = (t_room *)malloc(sizeof(t_room));
	if (!room)
		return (NULL);
	room->id = ft_strdup(key);
	room->x = x;
	room->y = y;
	room->visited = 0;
	room->tube = NULL;
	room->next = NULL;
	return (room);
}

int	hashof(const char *key)
{
	int	val;
	int	i;

	val = 42;
	i = 0;
	while (i < (int)ft_strlen(key))
	{
		val *= key[i] + 89;
		i++;
	}
	return (val % HT_SIZE);
}

t_room	*get(t_index *index, char *key)
{
	int		i;
	t_room	*room;

	i = hashof(key);
	room = index->rooms[i];
	while (room != NULL)
	{
		if (ft_strequ(key, room->id))
			return (room);
		else
			room = room->next;
	}
	return (NULL);
}

void	set(t_index *index, const char *key, const int x, const int y)
{
	int		i;
	t_room	*prev;
	t_room	*new;

	i = hashof(key);
	new = index->rooms[i];
	if (new == NULL)
	{
		index->rooms[i] = new_room(key, x, y);
		return ;
	}
	while (new != NULL)
	{
		if (ft_strequ(key, new->id))
		{
			new->x = x;
			new->y = y;
			return ;
		}
		prev = new;
		new = prev->next;
	}
	prev->next = new_room(key, x, y);
}
