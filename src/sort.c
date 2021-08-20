/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:24:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/19 18:51:07 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_route	*path_reverse(t_route *route)
{
	t_route	*new;
	t_edge	*tmp;

	new = new_route(1);
	if (!new)
		return (NULL);
	new->is_valid = 1;
	new->len = route->len;
	while (route->path)
	{
		tmp = new->path;
		new->path = route->path;
		route->path = route->path->prev_in_path;
		new->path->prev_in_path = tmp;
	}
	free_route(&route);
	return (new);
}

t_route	*sort_ants(t_route *overlap, t_route *disjoint, t_lem *lem)
{
	int		turns_floor;
	int		turns_least;
	int		turns;
	t_route	*head;

	lem->n_paths = 1;
	turns_floor = overlap->len - 1 + lem->ants;
	turns_least = turns_floor;
	turns = (lem->ants / lem->n_paths) + disjoint->len;
	head = disjoint;
	while (disjoint->is_valid && (turns >= turns_floor || turns <= turns_least))
	{
		turns_least = (lem->ants / lem->n_paths) + disjoint->len;
		lem->n_paths++;
		disjoint = disjoint->next;
		turns = (lem->ants / lem->n_paths) + disjoint->len;
	}
	if (lem->n_paths < 2)
	{
		free_route(&head);
		return (path_reverse(overlap));
	}
	free_route(&overlap);
	lem->n_paths--;
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
