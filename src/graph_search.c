/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:28:41 by rkyttala          #+#    #+#             */
/*   Updated: 2022/01/12 16:57:50 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** stores paths by backtracking from sink to source along the edges that have a
** negative flow, which means its reverse edge must have positive flow. appends
** every new path to the end of a list of paths.
*/
static void	store_paths(t_route *route, t_lem *lem, int iteration)
{
	t_edge	*sink_edge;

	while (route->next != NULL)
		route = route->next;
	sink_edge = lem->sink->edge;
	route->id = 1;
	while (sink_edge)
	{
		route->set = iteration;
		route->len = 1;
		route->path = NULL;
		if (sink_edge->flow < 0)
			route = follow_flow(lem, route, sink_edge, iteration);
		if (route->is_valid)
		{
			route->next = new_route(route->id + 1);
			route = route->next;
		}
		if (!route)
			break ;
		sink_edge = sink_edge->next_adjacent;
	}
	lem->error = (route == NULL) * -5;
}

/*
** updates directional flow of an edge along found path. removes edge capacity
** if edge->flow > 0.
*/
static void	update_edge(t_edge *edge)
{
	t_edge		*rev;

	rev = get_rev_edge(edge);
	if (rev)
	{
		edge->flow++;
		rev->flow--;
		edge->has_cap = (edge->flow < edge->has_cap);
		rev->has_cap = (rev->flow < rev->has_cap);
	}
}

/*
** traces back the edges from sink to source, updating the edges as it does so
*/
static void	send_flow(t_edge *curr, t_lem *lem)
{
	t_edge	*prev;

	update_edge(curr);
	while (curr->src != lem->source)
	{
		prev = curr->next_on_path;
		while (prev->to != curr->src)
		{
			prev = prev->next_on_path;
		}
		update_edge(prev);
		curr = prev;
	}
}

/*
** performs a breadth-first search on the graph starting from the source vertex,
** which is contained in @queue. queues visited nodes and adds the found edges
** to a path list, @bfs_edges.
** returns 1 if @sink was found, 0 otherwise.
*/
static int	bfs(t_vertex **queue, t_edge **bfs_edges, t_vertex *sink, int iter)
{
	t_vertex	*vertex;
	t_edge		*edge;

	(*queue)->visited = iter;
	while (!(*queue == NULL))
	{
		vertex = pop_first(&queue);
		edge = vertex->edge;
		while (edge != NULL)
		{
			if (edge->to->visited < iter && edge->flow < 1 && edge->has_cap)
			{
				edge->to->visited = iter;
				enqueue(queue, edge->to, -1);
				search_edge_prepend(bfs_edges, edge);
				if (edge->to == sink)
					return (1);
			}
			edge = edge->next_adjacent;
		}
	}
	return (0);
}

/*
** finds a path from source to sink and updates the flow along the path.
** repeats until no more paths are found.
** returns the list of found paths. if the sink could not be reached at all, an
** error code is stored in @lem.
**
** @lem: pointer to a general runtime info struct
*/
t_route	*saturate_graph(t_lem *lem)
{
	t_vertex	**queue;
	t_edge		*bfs_edges;
	t_route		*route;
	int			iteration;

	iteration = 1;
	queue = (t_vertex **)malloc(sizeof(t_vertex *) * (lem->vertices + 1));
	route = new_route(1);
	if (lem->error || !queue || !route)
		return (NULL);
	while (!lem->error)
	{
		bfs_edges = NULL;
		queue = wipe_queue(queue, lem->source, lem->vertices, iteration);
		if (!bfs(queue, &bfs_edges, lem->sink, iteration))
			break ;
		send_flow(bfs_edges, lem);
		store_paths(route, lem, iteration);
		iteration++;
	}
	lem->path_sets = iteration - 1;
	lem->error += (iteration < 2) * -4;
	free(queue);
	return (route);
}
