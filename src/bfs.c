/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:32:03 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/07 14:18:40 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** returns a pointer to the last malloc'd element in the given array
**
** arr: pointer to the head of a list of paths
*/
static t_vertex	*lastof(t_vertex **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	if (i > 0)
		return (arr[i - 1]);
	else
		return (NULL);
}

/*
** checks if current vertex has been visited already and if the edge connecting
** it to the previous vertex has capacity.
** returns 1 if not visited, 2 if linked to previous vertex in the path,
** 3 if it's the sink and the two previous checks apply.
**
** index: pointer to the hash table containing all vertices
** lem: pointer to a general runtime info struct
** edge: pointer to the edge we want to traverse
** route: pointer to the head of a list of paths
*/
static int	traverse(t_index *index, t_lem *lem, t_edge *edge, t_route *route)
{
	int			ret;
	t_vertex	*source;
	t_vertex	*sink;
	t_vertex	*curr;

	ret = 0;
	source = get(index, lem->source);
	sink = get(index, lem->sink);
	curr = edge->to;
	if (curr->visited < route->i && edge->fwd_cap > 0 && curr != sink && \
	curr != source)
	{
		curr->visited += 1;
		ret = 1 + is_linked(edge, lastof(route->path), sink);
	}
	else if (curr == sink && is_linked(edge, lastof(route->path), sink))
	{
		ret = 3;
	}
	return (ret);
}

/*
** bfs performs a breadth-first search and returns the found path:
**	- pop first vertex in queue
**	- mark all adjacent vertices as visited and add unvisited ones to queue
**	- append currently examined edge's src vertex to path if not already in it
**	- repeat until queue empty
*/
t_vertex	**bfs(t_index *index, t_lem *lem, t_vertex **queue, t_route *route)
{
	t_vertex	*vertex;
	t_edge		*edge;
	int			traversable;

	traversable = 0;
	while (!(*queue == NULL) && traversable != 3)
	{
		vertex = pop_first(&queue);
		if (vertex == NULL)
			break ;
		edge = vertex->edge;
		while (edge != NULL)
		{
			traversable = traverse(index, lem, edge, route);
			if (traversable)
				arr_append(&queue, edge->to);
			if (traversable > 1)
				arr_append(&(route->path), edge->src);
			if (traversable > 2)
				arr_append(&(route->path), get(index, lem->sink));
			edge = edge->next;
		}
	}
	return (route->path);
}
