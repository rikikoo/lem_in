/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:28:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/20 17:03:41 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** remove capacity from the edges along @route->path and count its length
*/
static t_edge	*send_flow(t_route *route)
{
	t_edge	*head;

	head = route->path;
	while (route->path)
	{
		route->len++;
		route->path->cap = 0;
		route->path = route->path->prev_in_path;
	}
	return (head);
}

/*
** connects the edges that belong to the actual path and marks the path as valid
** returns the head of the path
*/
static t_edge	*store_path(t_route *route, t_vertex *source, t_lem *lem)
{
	t_edge	*head;
	t_edge	*prev;

	head = route->path;
	while (route->path->src != source)
	{
		prev = route->path->prev_in_path;
		while (prev->to != route->path->src)
		{
			prev = prev->prev_in_path;
		}
		route->path->prev_in_path = prev;
		route->path = route->path->prev_in_path;
	}
	route->path->prev_in_path = NULL;
	route->is_valid = 1;
	lem->n_paths++;
	return (head);
}

/*
** performs a breadth-first search on the graph starting from the source vertex.
** utilises @queue for queueing the visited nodes and adding the found edges
** to a path list, whose head is stored in @route.
** returns 1 if @sink was found, 0 otherwise.
*/
static int	bfs(t_vertex **queue, t_route *route, t_vertex *sink)
{
	t_vertex	*vertex;
	t_edge		*edge;

	(*queue)->visited = route->i;
	while (!(*queue == NULL))
	{
		vertex = pop_first(&queue);
		edge = vertex->edge;
		while (edge != NULL)
		{
			if (edge->to->visited < route->i && edge->cap != 0)
			{
				edge->to->visited = route->i;
				queue_append(&queue, edge->to);
				path_prepend(&(route->path), edge);
				if (edge->to == sink)
					return (1);
			}
			edge = edge->next_adjacent;
		}
	}
	return (0);
}

/*
** finds a path from @source to @sink, stores it and updates its flow.
** repeats until no more paths are found.
** returns the list of found paths. if the sink could not be reached, an error
** code is stored in @lem.
**
** @lem: pointer to a general runtime info struct
** @source: pointer to the graph's source vertex
** @sink: pointer to the graph's sink vertex
*/
t_route	*find_paths(t_lem *lem, t_vertex *source, t_vertex *sink)
{
	t_vertex	**queue;
	t_route		*route;
	t_route		*head;
	int			bfs_iteration;

	queue = (t_vertex **)malloc(sizeof(t_vertex *) * (lem->vertices + 1));
	sink->visited--;
	bfs_iteration = lem->n_paths + 1;
	route = new_route(bfs_iteration);
	head = route;
	if (!queue || !route)
		return (NULL);
	while (1)
	{
		queue = wipe_queue(queue, source, lem->vertices);
		if (!bfs(queue, route, sink))
			break ;
		route->path = store_path(route, source, lem);
		route->path = send_flow(route);
		route->next = new_route(++bfs_iteration);
		route = route->next;
	}
	free(queue);
	lem->error = !(head->is_valid) * -4;
	return (head);
}
