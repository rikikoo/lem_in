/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:32:03 by rkyttala          #+#    #+#             */
/*   Updated: 2021/06/14 19:14:25 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** returns a pointer to the last malloc'd element in the given array
**
** arr: pointer to the head of a list of paths
*/
static char	*lastof(char **arr)
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
	t_vertex	*vertex;

	ret = 0;
	vertex = get(index, edge->to);
	if (vertex->visited < route->i && edge->fwd_cap > 0 && \
	(!ft_strequ(vertex->id, lem->sink) && !ft_strequ(edge->to, lem->source)))
	{
		vertex->visited += 1;
		ret = 1 + is_linked(edge, get(index, lastof(route->path)), lem->sink);
	}
	else if (ft_strequ(vertex->id, lem->sink) && \
	is_linked(edge, get(index, lastof(route->path)), lem->sink))
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
char	**bfs(t_index *index, t_lem *lem, char **queue, t_route *route)
{
	t_vertex	*vertex;
	t_edge		*edge;
	int			traversable;

	traversable = 0;
	while (!(*queue == NULL) && traversable != 3)
	{
		vertex = get(index, pop_first(&queue));
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
				arr_append(&(route->path), lem->sink);
			edge = edge->next;
		}
	}
	return (route->path);
}
