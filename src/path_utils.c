/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:53:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/11/26 12:25:52 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	go_with_the_flow(t_lem *lem, t_route *route, t_edge *edge)
{
	while (edge && edge->src != lem->source)
	{
		if (edge->flow < 0)
		{
			path_prepend(&(route->path), get_rev_edge(edge));
			route->len++;
			edge = edge->to->edge;
		}
		else
			edge = edge->next_adjacent;
	}
	if (route->path)
		route->is_valid = (route->path->src == lem->source);
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

static int	is_duplicate(t_edge *p0, t_edge *p1, t_vertex *sink)
{
	if (p0->to == sink && p1->to == sink)
		return (1);
	while (p0 && p1 && p0->to != sink)
	{
		if (p0->to == p1->to)
		{
			p0 = p0->next_on_path;
			p1 = p1->next_on_path;
		}
		else
			return (0);
	}
	return (1);
}

/*
** discards identical paths that were stored during bfs
*/
void	discard_duplicate_paths(t_route *route, t_lem *lem)
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
