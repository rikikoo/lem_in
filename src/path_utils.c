/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:53:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/27 19:04:01 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	is_duplicate(t_edge *p0, t_edge *p1, t_vertex *sink)
{
	if (p0->to == sink && p1->to == sink)
		return (1);
	while (p0 && p1 && p0->to != sink)
	{
		if (p0->to == p1->to)
		{
			p0 = p0->prev_in_path;
			p1 = p1->prev_in_path;
		}
		else
			return (0);
	}
	return (1);
}

/*
** since the breadth-first search is performed twice from two directions on the
** graph, identical paths may get stored. This function iterates over the joined
** and sorted list of paths and removes possible duplicate paths.
*/
void	discard_duplicate_paths(t_route *route, t_lem *lem)
{
	t_route	*next;
	t_route	*tmp;

	next = route->next;
	while (next && next->is_valid)
	{
		while (tmp && route->len == tmp->len)
		{
			if (is_duplicate(route->path, tmp->path, lem->sink))
			{
				tmp = next;
				route->next = tmp->next;
				free(tmp);
				break ;
			}
			tmp = tmp->next;
		}
		route->next->i = route->i + 1;
		route = route->next;
		next = route->next;
	}
}

t_route	*join_paths(t_route *r0, t_route *r1)
{
	t_route	*head;

	if (!r0)
		return (NULL);
	head = r0;
	while (r0->next && r0->next->is_valid)
		r0 = r0->next;
	if (r0->next)
	{
		free(r0->next);
		r0->next = NULL;
	}
	if (r1 && r1->is_valid)
		r0->next = r1;
	else if (r1 && !r1->is_valid)
		free(r1);
	return (head);
}

/*
** forward-bfs's edges are the right way around (src -> sink), but in the
** reverse order. Hence the function below.
*/
t_route	*path_reverse(t_route *route)
{
	t_route	*new;
	t_edge	*tmp;

	new = new_route(route->i);
	if (!new)
		return (NULL);
	new->is_valid = route->is_valid;
	new->len = route->len;
	while (route->path)
	{
		tmp = new->path;
		new->path = route->path;
		route->path = route->path->prev_in_path;
		new->path->prev_in_path = tmp;
	}
	return (new);
}
