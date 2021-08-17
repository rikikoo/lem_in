/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:24:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/17 23:10:49 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_route	*path_reverse(t_route *route)
{
	t_route	*new;
	t_edge	*head;

	new = new_route(1);
	if (!new)
		return (NULL);
	new->is_valid = 1;
	new->len = route->len;
	head = route->path;
	while (route->path)
	{
		path_prepend(&new->path, route->path);
		route->path = route->path->prev_in_path;
	}
	free_route(&route);
	return (new);
}

t_route	*sort_ants(t_route *overlap, t_route *disjoint, t_lem *lem)
{
	int		paths_needed;
	int		minimum_turns;
	int		least_turns;
	t_route	*head;

	lem->n_paths = 1;
	if (!disjoint->is_valid)
		return (path_reverse(overlap));
	paths_needed = 0;
	minimum_turns = overlap->len - 1 + lem->ants;
	head = disjoint;
	least_turns = ~paths_needed;
	while (disjoint != NULL && disjoint->is_valid)
	{
		paths_needed++;
		if ((lem->ants / paths_needed) + disjoint->len < minimum_turns && \
		least_turns == (lem->ants / paths_needed) + disjoint->len)
			break ;
		least_turns = (lem->ants / paths_needed) + disjoint->len;
		disjoint = disjoint->next;
	}
	if (paths_needed < 2)
		return (path_reverse(overlap));
	lem->n_paths = paths_needed;
	free_route(&overlap);
	return (head);
}

/*
** swaps places of two paths in the list of paths
*/
static void	swap(t_route **prev, t_route **current, t_route **next)
{
	t_route	*tmp;

	tmp = *current;
	tmp->next = (*next)->next;
	if (*prev == NULL)
	{
		*current = *next;
		(*current)->next = tmp;
	}
	else
	{
		*current = *next;
		(*prev)->next = *current;
		(*current)->next = tmp;
	}
}

/*
** sorts all found paths in ascending order in regards to path length.
** returns sorted path.
**
** @route: pointer to the head of a list of paths
*/
t_route	*sort_paths(t_route *route)
{
	t_route	*prev;
	t_route	*curr;
	t_route	*next;
	t_route	*head;

	prev = NULL;
	curr = route;
	head = curr;
	while (curr->is_valid)
	{
		next = curr->next;
		while (next->is_valid)
		{
			if (curr->len > next->len)
			{
				swap(&prev, &curr, &next);
				head = curr;
			}
			next = next->next;
		}
		prev = curr;
		curr = curr->next;
	}
	return (head);
}
