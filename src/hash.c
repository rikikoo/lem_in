/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:41:11 by rkyttala          #+#    #+#             */
/*   Updated: 2021/03/18 18:11:11 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_index	*init_index(void)
{
	t_index	*index;
	int		i;

	if (!(index = (t_index *)malloc(sizeof(t_index))))
		return (NULL);
	if (!(index->rooms = (t_room **)malloc(sizeof(t_room *) * SIZE)))
		return (NULL);
	i = 0;
	while (i < SIZE)
	{
		index->rooms[i] = NULL;
		i++;
	}
	return (index);
}

t_room	*new_room(const char *key, const int x, const int y)
{
	t_room	*room;

	if (!(room = (t_room *)malloc(sizeof(t_room))))
		return (NULL);		// TODO: error (OOM)
	room->id = ft_strdup(key);
	room->x = x;
	room->y = y;
	room->checked = 0;
	room->occupied = 0;
	room->next = NULL;
	return (ptr);
}

int		hashof(const char *key)
{
	int	val;
	int	i;

	val = 0;
	i = 0;
	while (i < ft_strlen(key))
	{
		val *= (89 + key[i]);
		i++;
	}
	return (val % SIZE);
}

void	set(t_index *index, const char *key, const int x, const int y)
{
	t_room	*entry;
	int		i;

	i = hashof(key);
	entry = index->rooms[i];
	if (entry == NULL)
		entry = new_room(key, x, y);
	else
	{
		while (entry != NULL)
		{
			if (!ft_strcmp(key, entry->id))
			{
				entry->x = x;
				entry->y = y;
				return ;
			}
			entry = entry->next;
		}
		entry = new_room(key, x, y);
	}
}
