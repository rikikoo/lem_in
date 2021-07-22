/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:28:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/22 21:29:29 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** for each vertex in the found path, mark all incoming and outgoing edges as
** filled (== 0 capacity)
**
** path: pointer to vertex ids on the path
** sink: pointer to the sink vertex
*/
static int	send_flow(t_vertex **path, t_vertex *sink)
{
	t_vertex	*vertex;
	t_edge		*edge_out;
	t_edge		*edge_in;
	int			i;

	i = 1;
	if (path[i] == sink)
		path[0]->edge->fwd_cap = 0;
	while (path[i + 1] != NULL && path[i] != sink)
	{
		vertex = path[i];
		edge_out = vertex->edge;
		while (edge_out != NULL)
		{
			edge_out->fwd_cap = 0;
			vertex = path[i - 1];
			edge_in = vertex->edge;
			while (edge_in->to != path[i])
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
** path: pointer to vertex ids on the path
** sink: pointer to the sink vertex
*/
static int	path_found(t_vertex **path, t_vertex *sink)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		if (path[i] == sink)
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
t_route	*find_paths(t_index *index, t_lem *lem, t_vertex *source, \
t_vertex *sink)
{
	t_vertex	**queue;
	t_route		*route;
	t_route		*head;
	int			i;

	queue = (t_vertex **)malloc(sizeof(t_vertex *) * (lem->vertices + 1));
	i = 1;
	route = new_route(source, lem->vertices, i);
	head = route;
	if (!queue || !route)
		return (NULL);
	while (1)
	{
		queue = wipe_queue(queue, source, lem->vertices);
		route->path = bfs(index, lem, queue, route);

		ft_printf("round %d\n", route->i);
		for (int x = 0; route->path[x]; x++) {
			ft_printf("%s\n", route->path[x]->id);
		}
		ft_printf("\n");
		
		if (!path_found(route->path, sink))
			break ;
		route->is_valid = 1;
		lem->max_flow += send_flow(route->path, sink);
		route->next = new_route(source, lem->vertices, ++i);
		route = route->next;
	}
	free(queue);
	return (head);
}
