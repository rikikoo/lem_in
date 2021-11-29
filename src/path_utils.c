/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:53:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/11/29 11:13:43 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** removes possible duplicate paths and marks down intersecting paths.
** returns the joined and sorted list of paths. sets an error value to
** @lem->error in case a malloc failed.
*/
void	count_sets(t_route *route, t_lem *lem)
{
	int	i;
	int	set_len;

	if (lem->error)
		return ;
	i = 1;
	while (i <= lem->path_sets)
	{
		set_len = 0;
		while (route && route->path && route->path->set == i)
		{
			set_len++;
			route = route->next;
		}
		if (set_len > lem->max_flow)
			lem->max_flow = set_len;
		i++;
	}
}

/*
** prepends a new path element that contains @edge & @set to the front of @path
*/
t_path	*path_prepend(t_path *path, t_edge *edge, int set)
{
	t_path	*new;

	if (!edge)
		return (NULL);
	new = (t_path *)malloc(sizeof(t_path));
	if (!new)
		return (NULL);
	new->edge = edge;
	new->set = set;
	new->next = path;
	return (new);
}

t_edge	*get_rev_edge(t_edge *edge)
{
	t_edge	*rev;

	if (edge)
	{
		rev = edge->to->edge;
		while (rev && rev->to != edge->src)
			rev = rev->next_adjacent;
		if (rev->to == edge->src)
			return (rev);
	}
	return (NULL);
}

t_route	*go_with_the_flow(
		t_lem *lem,
		t_route *route,
		t_edge *edge,
		const int iter
		)
{
	while (edge && edge->src != lem->source)
	{
		if (edge->flow < 0)
		{
			route->path = path_prepend(route->path, get_rev_edge(edge), iter);
			route->len++;
			edge = edge->to->edge;
		}
		else
			edge = edge->next_adjacent;
	}
	if (route->path)
		route->is_valid = (route->path->edge->src == lem->source);
	return (route);
}
