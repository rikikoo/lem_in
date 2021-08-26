/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distinction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:31:47 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/25 21:19:58 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** checks @path's each vertex against @cmp's all vertices. if a match is
** encountered, @cmp cannot be used simultaneously with @path and 0 is returned,
** otherwise 1.
*/
static int	paths_are_distinct(t_edge *path, t_edge *cmp, t_vertex *sink)
{
	t_edge	*cmp_head;

	cmp_head = cmp;
	while (path && path->to != sink)
	{
		while (cmp && cmp->to != sink)
		{
			if (cmp->to == path->to)
				return (0);
			cmp = cmp->prev_in_path;
		}
		path = path->prev_in_path;
		cmp = cmp_head;
	}
	return (1);
}

/*
** for each route, mark compatibility with all other routes (i.e. do the paths
** share vertices (False) or not (True)) in the route's "compatible_with" array
*/
static int	path_combinations(t_route *route, t_lem *lem)
{
	t_route	*next;

	if (!route)
		return (-5);
	next = route->next;
	while (route->is_valid)
	{
		route->compatible_with = (int *)ft_zeros(lem->n_paths);
		if (!route->compatible_with)
			return (-5);
		next = route->next;
		while (next->is_valid)
		{
			if (paths_are_distinct(route->path, next->path, lem->sink))
				route->compatible_with[next->i - 1] = 1;
			next = next->next;
		}
		route = route->next;
	}
	return (0);
}

/*
** reverses all paths (so that they're the right way around) and marks down
** paths that do not intersect
*/
t_route	*find_distinct(t_route *route, t_lem *lem)
{
	t_route	*reversed;
	t_route	*rev_head;
	t_route	*head;

	if (lem->error)
		return (route);
	reversed = path_reverse(route);
	rev_head = reversed;
	head = route;
	route = route->next;
	while (route && reversed)
	{
		reversed->next = path_reverse(route);
		reversed = reversed->next;
		route = route->next;
	}
	free_route(&head);
	lem->error = path_combinations(rev_head, lem);
	return (rev_head);
}
