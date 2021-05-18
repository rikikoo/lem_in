/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:41:11 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/18 19:36:05 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** index in this case is an implementation of a hash table in C.
** t_index is a struct that has an array of pointers to rooms/vertices.
** the size of the array HT_SIZE is pre-defined in lem_in.h
**
** init_index returns a pointer to t_index, all pointers initialized to NULL
*/
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

/*
** allocates memory for a new room/vertex and returns a pointer to it
**
** key: the name/id of the vertex
** x, y: the coordinates of the vertex
*/
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

/*
** returns a hash of the room name/id
**
** key: name/id of the vertex to be hashed
**
** TODO: look up an actual hashing algorithm, don't use this nonsense
*/
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

/*
** returns the room/vertex pointer if found in the hash table, NULL otherwise
**
** index: a pointer to t_index
** key: name/id of the vertex to get
*/
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

/*
** inserts a new entry to the hash table (index)
**
** index: a pointer to t_index
** key: name/id of the vertex to insert
** x, y: coordinates of the vertex
*/
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
