/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:24:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/10 23:04:58 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	calculate_turns(t_route *route, t_lem *lem, int turns_least)
{
	int		turns;
	int		paths;
	t_route	*next;

	next = route->next;
	paths = 1;
	ft_printf("\n\nTurns with route %d and...\n", route->i);
	while (next->is_valid)
	{
		if (route->compatible_with[next->i - 1])
		{
			paths++;
			turns = (lem->ants / paths) + next->len - 2;
			if (turns < turns_least)
			{
				turns_least = turns;
				lem->n_paths = paths;
			}
		}
		next = next->next;
	}
	return (turns_least);
}

t_route	*sort_ants(t_route *route, t_lem *lem)
{
	int		turns_least;
	int		turns;
	int		paths;
	t_route	*head;

	if (lem->error)
		return (NULL);
	turns_least = ~(1 << ((sizeof(int) * 8) - 1));
	head = route;
	paths = 1;
	while (route->is_valid)
	{
		turns = calculate_turns(route, lem, turns_least);
		if (turns < turns_least)
		{
			turns_least = turns;
			head = route;
			paths = lem->n_paths;
		}
		route = route->next;
	}
	lem->n_paths = paths;
	return (head);
}

/*
** swaps places of two paths in the list of paths
*/
static void	swap(t_route *prev, t_route **current, t_route *next)
{
	t_route	*tmp;

	tmp = *current;
	tmp->next = next->next;
	if (prev == NULL)
	{
		*current = next;
		(*current)->next = tmp;
	}
	else
	{
		*current = next;
		prev->next = *current;
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
	t_route	*next;
	t_route	*head;

	prev = NULL;
	head = route;
	while (route)
	{
		next = route->next;
		while (next && next->is_valid)
		{
			if (route->len > next->len)
				swap(prev, &route, next);
			next = next->next;
		}
		prev = route;
		route = route->next;
	}
	return (head);
}
