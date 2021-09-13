/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:24:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/13 17:08:43 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	calculate_differences(t_route *route, t_route *cmp, int ants)
{
	int	diff;

	while (cmp && cmp->i <= route->i && ants)
	{
		diff = cmp->len - route->len;
		if (diff > ants)
			cmp->ants = ants;
		else
			cmp->ants = diff;
		ants -= cmp->ants;
		cmp = next_compatible(cmp);
	}
	return (ants);
}

static int	calculate_turns(t_route *route, int limit)
{
	int	turns;
	int	turns_max;

	turns_max = 0;
	while (route && route->i <= limit)
	{
		turns = route->len + route->ants;
		if (turns > turns_max)
			turns_max = turns;
		route = next_compatible(route);
	}
	return (turns_max);
}

void	sort_ants(t_route *route, t_lem *lem)
{
	t_route	*head;
	t_route	*cmp;
	int		ants;
	int		turns_least;
	int		turns;

	if (lem->error)
		return ;
	head = route;
	turns_least = ~(1 << ((sizeof(int) * 8) - 1));
	while (route && route->is_valid)
	{
		ants = lem->ants;
		cmp = head;
		ants = calculate_differences(route, cmp, ants);
		distribute_ants(head, ants, route->i);
		turns = calculate_turns(head, route->i);
		if (turns > turns_least)
			break ;
		turns_least = turns;
		lem->n_paths = route->i;
		route = next_compatible(route);
	}
	ft_printf("Paths: %d\nTurns: %d\n", lem->n_paths, turns_least);
	exit(0);
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
