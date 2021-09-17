/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:53:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/15 23:24:35 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** loops over the paths following @route until a path that doesn't intersect
** with it is found.
** returns the found path or NULL if none of the following paths are compatible.
*/
t_route	*next_compatible(t_route *route)
{
	t_route	*next;

	next = route->next;
	while (next && next->is_valid)
	{
		if (route->compatible_with[next->i - 1])
			return (next);
		next = next->next;
	}
	return (NULL);
}

/*
**
** NOTE: for some reason, on maps generated by './generator --big-superposition'
** there is always be one path in the backward paths that before being passed to
** 'find_distinct()' contains all rooms when checked, but after contatins only
** three rooms. This is why the last if statement is present this function.
*/
static int	is_duplicate(t_edge *p0, t_edge *p1, t_vertex *sink)
{
	int	same;

	if (p0->to == sink && p1->to == sink)
		return (1);
	same = 0;
	while (p0 && p1 && p0->to != sink)
	{
		same += (p0->to == p1->to);
		p0 = p0->prev_in_path;
		p1 = p1->prev_in_path;
	}
	if ((p0 && !p1) || (!p0 && p1))
		return (1);
	return (same);
}

/*
** since the breadth-first search is performed twice from two directions on the
** graph, identical paths may get stored. This function iterates over the joined
** and sorted list of paths and removes potential duplicate paths.
*/
void	remove_duplicate_paths(t_route *route, t_lem *lem)
{
	t_route	*next;
	t_route	*tmp;

	next = route->next;
	while (next && next->is_valid)
	{
		tmp = next;
		while (tmp && route->len == tmp->len)
		{
			if (is_duplicate(route->path, tmp->path, lem->sink))
			{
				if (next->next == tmp->next)
					route->next = next->next;
				else
					next->next = tmp->next;
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
	while (r1 && r1->is_valid)
	{
		r0->next = r1;
		r0 = r0->next;
		r1 = r1->next;
	}
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