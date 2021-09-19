/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distinction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:31:47 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/19 20:14:11 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	count_paths(t_route *route, t_lem *lem)
{
	lem->n_paths = 0;
	while (route && route->is_valid)
	{
		lem->n_paths++;
		route = route->next;
	}
}

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
static int	path_compatibility(t_route *route, t_lem *lem)
{
	t_route	*next;

	if (lem->error)
		return (-5);
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
** because the breadth-first search was performed backwards (sink to source)
** on the 2nd run, the edges are reversed, which is why all found paths' edges
** need to be flipped before joining all paths.
*/
static void	flip_bw_route_edges(t_route *route)
{
	t_vertex	*tmp;
	t_edge		*head;

	while (route && route->is_valid)
	{
		head = route->path;
		while (route->path)
		{
			tmp = route->path->to;
			route->path->to = route->path->src;
			route->path->src = tmp;
			route->path = route->path->prev_in_path;
		}
		route->path = head;
		route = route->next;
	}
}

/*
** reverses all paths found by the forward-bfs, flips edges of the backward-bfs,
** joins the two sets of paths together, removes possible duplicate paths and
** marks down intersecting paths.
** returns the joined and sorted list of paths. sets an error value to
** @lem->error in case a malloc failed.
*/
t_route	*find_distinct(t_route *route, t_route *bw_route, t_lem *lem)
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
	flip_bw_route_edges(bw_route);
	route = sort_paths(join_paths(rev_head, bw_route));
	route->i = 1;
	remove_duplicate_paths(route, lem);
	count_paths(route, lem);
	lem->error = path_compatibility(route, lem);
	return (route);
}
