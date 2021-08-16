/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:24:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/16 21:44:19 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	sort_ants(t_route *overlap, t_route *disjoint, int ants)
{
	int		paths_needed;
	int		minimum_turns;

	if (!disjoint->is_valid)
		return (0);
	paths_needed = 0;
	minimum_turns = overlap->len - 1 + ants;
	while (disjoint != NULL && disjoint->is_valid)
	{
		paths_needed++;
		if ((ants / paths_needed) + disjoint->len < minimum_turns)
				break;
		disjoint = disjoint->next;
	}
	if (paths_needed < 2)
		return (0);
	return (paths_needed);
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
