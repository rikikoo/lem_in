/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:28:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/11/26 12:05:35 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	store_paths(t_route *route, t_lem *lem)
{
	t_edge	*sink_edges;

	while (route->next != NULL)
		route = route->next;
	sink_edges = lem->sink->edge;
	while (sink_edges)
	{
		go_with_the_flow(lem, route, sink_edges);
		if (route->is_valid)
		{
			route->next = new_route(route->i + 1);
			route = route->next;
		}
		if (!route)
			break ;
		sink_edges = sink_edges->next_adjacent;
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
		edge->cap = (edge->flow < edge->cap);
		rev->cap = (rev->flow < rev->cap);
	}
}

/*
** traces back the edges from sink to source, updating the edges as it does so
*/
static void	send_flow(t_edge *search_edges, t_lem *lem)
{
	t_edge	*curr;
	t_edge	*prev;

	curr = search_edges;
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
	lem->n_paths++;
}

/*
** performs a breadth-first search on the graph starting from the source vertex,
** which is contained in @queue. queues visited nodes and adds the found edges
** to a path list, whose head is stored in @route.
** returns 1 if @sink was found, 0 otherwise.
*/
static int	bfs(t_vertex **queue, t_edge **sea_edges, t_vertex *sink, int iter)
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
			if (edge->to->visited < iter && edge->flow < 1)
			{
				edge->to->visited = iter;
				enqueue(queue, edge->to, -1);
				path_prepend(sea_edges, edge);
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
	t_edge		*search_edges;
	t_route		*route;
	int			iteration;

	iteration = 1;
	queue = (t_vertex **)malloc(sizeof(t_vertex *) * (lem->vertices + 1));
	route = new_route(iteration);
	if (lem->error || !queue || !route)
		return (NULL);
	while (!lem->error)
	{
		search_edges = NULL;
		queue = wipe_queue(queue, lem->source, lem->vertices);
		if (!bfs(queue, &search_edges, lem->sink, iteration))
			break ;
		send_flow(search_edges, lem);
		// ft_printf("\niteration %d:\n", iteration);
		// for (t_edge *edge = search_edges; edge; edge = edge->next_on_path) {
		// 	ft_printf("%s - %s\t", edge->src->id, edge->to->id);
		// 	ft_printf("flow: %d, capacity %d\n", edge->flow, edge->cap);
		// }
		store_paths(route, lem);
		iteration++;
	}
	free(queue);
	lem->error += (iteration < 2) * -4;
	return (route);
}
