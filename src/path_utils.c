/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:53:41 by rkyttala          #+#    #+#             */
/*   Updated: 2022/01/12 17:26:02 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** prepends a new path element that contains @edge & @set to the front of @path
*/
t_path	*path_prepend(t_path *path, t_edge *edge)
{
	t_path	*new;

	if (!edge)
		return (NULL);
	new = (t_path *)malloc(sizeof(t_path));
	if (!new)
		return (NULL);
	new->edge = edge;
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

void	free_path(t_path *path)
{
	t_path	*tmp;

	while (path)
	{
		tmp = path;
		path = path->next;
		free(tmp);
	}
}

t_route	*follow_flow(t_lem *lem, t_route *route, t_edge *edge, int iter)
{
	while (edge && edge->src != lem->source)
	{
		if (edge->flow < 0 && edge->to->valid != iter)
		{
			if (edge->to != lem->source)
				edge->to->valid = iter;
			route->path = path_prepend(route->path, get_rev_edge(edge));
			if (!route->path)
				return (NULL);
			route->len++;
			edge = edge->to->edge;
		}
		else if (edge->src != lem->sink)
			edge = edge->next_adjacent;
		else
			break ;
	}
	if (route->path && route->path->edge->src == lem->source)
		route->is_valid = 1;
	else
		free_path(route->path);
	return (route);
}
