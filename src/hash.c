/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:41:11 by rkyttala          #+#    #+#             */
/*   Updated: 2021/03/16 13:47:25 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_index			*init_index(void)
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

static t_room	*new_room(const char *key, const char *val)
{
	t_room	*room;

	if (!(room = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	room->name = ft_strdup(key);
	room->xy = ft_strdup(val);
	room->checked = 0;
	room->occupied = 0;
	room->next = NULL;
	return (ptr);
}

static int		hashof(const char *key)
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

char			*valueof(t_index *index, const char *key)
{
	t_room	*room;
	int		i;

	i = hashof(key);
	room = index->rooms[i];
	if (room == NULL)
		return (NULL);
	if (!ft_strcmp(key, room->name))
		return (room->xy);
	else
		return (NULL);
}

void			insert(t_index *index, const char *key, const char *val)
{
	t_room	*entry;
	int		i;

	i = hashof(key);
	entry = index->rooms[i];
	if (entry == NULL)
		entry = new_room(key, val);
	else
	{
		while (entry != NULL)
		{
			if (!ft_strcmp(key, entry->name))
			{
				free(entry->xy);
				entry->xy = ft_strdup(val);
				return ;
			}
			entry = entry->next;
		}
		entry = new_room(key, val);
	}
}
