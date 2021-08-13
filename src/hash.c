/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:41:11 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/14 00:18:36 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** returns a djb2 hash of the vertex name/id
**
** key: name/id of the vertex to be hashed
*/
static size_t	hashof(const char *key)
{
	size_t			i;
	unsigned long	hash;

	i = 0;
	hash = 5381;
	while (key[i] != '\0')
	{
		hash = (((hash << 5) + hash) + key[i]) % HT_SIZE;
		i++;
	}
	return (hash);
}

/*
** returns the requested vertex pointer if found in the hash table, else NULL
**
** ht: a pointer to t_hashtab
** key: name/id of the vertex to get
*/
t_vertex	*get(t_hashtab *ht, const char *key)
{
	int			i;
	t_vertex	*vertex;

	if (!key)
		return (NULL);
	i = hashof(key);
	vertex = ht->vertices[i];
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
** inserts a new entry to the hash table @ht
**
** @ht: a pointer to t_hashtab
** @key: name/id of the vertex to insert
** @x, @y: coordinates of the vertex
*/
void	set(t_hashtab *ht, const char *key, const int x, const int y)
{
	int			i;
	t_vertex	*prev;
	t_vertex	*new;

	i = hashof(key);
	new = ht->vertices[i];
	if (new == NULL)
	{
		ht->vertices[i] = new_vertex(key, x, y);
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
