/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:32:03 by rkyttala          #+#    #+#             */
/*   Updated: 2021/06/02 16:20:31 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** returns a pointer to the last malloc'd element of the array
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
** bfs performs a breadth-first search and returns the found path
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
