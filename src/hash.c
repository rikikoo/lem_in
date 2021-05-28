/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:41:11 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/28 13:56:31 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** allocates memory for a new vertex and returns a pointer to it
**
** key: the name/id of the vertex
** x, y: the coordinates of the vertex
*/
t_vertex	*new_vertex(const char *key, const int x, const int y)
{
	t_vertex	*vertex;

	vertex = (t_vertex *)malloc(sizeof(t_vertex));
	if (!vertex)
		return (NULL);
	vertex->id = ft_strdup(key);
	vertex->x = x;
	vertex->y = y;
	vertex->visited = 0;
	vertex->edge = NULL;
	vertex->next = NULL;
	return (vertex);
}

/*
** returns a hash of the vertex name/id
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
** returns the vertex pointer if found in the hash table, NULL otherwise
**
** index: a pointer to t_index
** key: name/id of the vertex to get
*/
t_vertex	*get(t_index *index, const char *key)
{
	int			i;
	t_vertex	*vertex;

	i = hashof(key);
	vertex = index->vertices[i];
	while (vertex != NULL)
	{
		if (ft_strequ(key, vertex->id))
			return (vertex);
		else
			vertex = vertex->next;
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
	int			i;
	t_vertex	*prev;
	t_vertex	*new;

	i = hashof(key);
	new = index->vertices[i];
	if (new == NULL)
	{
		index->vertices[i] = new_vertex(key, x, y);
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
	prev->next = new_vertex(key, x, y);
}
