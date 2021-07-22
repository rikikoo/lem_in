/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:28:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/06/18 22:40:16 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** for each vertex in the found path, mark all incoming and outgoing edges as
** filled (== 0 capacity)
**
** index: pointer to hash table containing all vertices
** path: pointer to vertex ids on the path
** sink: id of the sink as a string
*/
static int	send_flow(t_index *index, char **path, char *sink)
{
	t_vertex	*vertex;
	t_edge		*edge_out;
	t_edge		*edge_in;
	int			i;

	i = 1;
	if (ft_strequ(path[i], sink))
		(get(index, path[0]))->edge->fwd_cap = 0;
	while (path[i + 1] != NULL && !ft_strequ(path[i], sink))
	{
		vertex = get(index, path[i]);
		edge_out = vertex->edge;
		while (edge_out != NULL)
		{
			edge_out->fwd_cap = 0;
			vertex = get(index, path[i - 1]);
			edge_in = vertex->edge;
			while (!ft_strequ(edge_in->to, path[i]))
				edge_in = edge_in->next;
			edge_in->fwd_cap = 0;
			edge_out = edge_out->next;
		}
		i++;
	}
	return (1);
}

/*
** loop through vertex names until sink name found.
** return true if found, false otherwise.
**
** sink: id of the sink as a string
** path: pointer to vertex ids on the path
*/
static int	path_found(char **path, char *sink)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		if (ft_strequ(path[i], sink))
			return (1);
		i++;
	}
	return (0);
}

/*
** WIP
**
** init queue for bfs algorithm,
** perform bfs on graph,
** check if valid path,
** update graph capacities
** store path
** repeat until no path found
*/
t_route	*edm_karp(t_index *index, t_lem *lem)
{
	char	**queue;
	t_route	*route;
	t_route	*head;
	int		i;

	queue = (char **)malloc(sizeof(char *) * (lem->vertices + 1));
	queue[lem->vertices] = NULL;
	i = 1;
	route = new_route(lem->vertices, i, lem->source);
	head = route;
	if (!queue || !route)
		return (NULL);
	while (1)
	{
		queue = wipe_array(queue, lem->vertices, lem->source);
		route->path = bfs(index, lem, queue, route);
		if (!path_found(route->path, lem->sink))
			break ;
		route->is_valid = 1;
		lem->max_flow += send_flow(index, route->path, lem->sink);
		route->next = new_route(lem->vertices, ++i, lem->source);
		route = route->next;
	}
	free_queue(&queue, lem->vertices);
	return (head);
}
