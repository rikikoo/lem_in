/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:24:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/14 21:25:11 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	calculate_turns(t_route *route, int limit, int *pants)
{
	int	turns;
	int	turns_max;

	turns_max = 0;
	while (route && route->i <= limit)
	{
		turns = route->len + pants[route->i - 1];
		if (turns > turns_max)
			turns_max = turns;
		route = next_compatible(route);
	}
	return (turns_max);
}

static int	calculate_diff(t_route *route, t_route *cmp, int ants, int *pants)
{
	int	diff;

	while (cmp && cmp->i <= route->i && ants)
	{
		diff = route->len - cmp->len;
		if (diff > ants)
			pants[cmp->i - 1] = ants;
		else
			pants[cmp->i - 1] = diff;
		ants -= pants[cmp->i - 1];
		cmp = next_compatible(cmp);
	}
	return (ants);
}

int	sort_ants(t_route *route, t_lem *lem, int ants, int *pants)
{
	t_route	*head;
	t_route	*cmp;
	int		turns_least;
	int		turns;

	if (lem->error)
		return (lem->error);
	if (!pants)
		return (-5);
	head = route;
	turns_least = ~(1 << ((sizeof(int) * 8) - 1));
	while (route && route->is_valid)
	{
		cmp = head;
		ants = calculate_diff(route, cmp, lem->ants, pants);
		distribute_ants(head, route->i, ants, pants);
		turns = calculate_turns(head, route->i, pants);
		ft_printf("Route no. %d turns: %d\n", route->i, turns);
		if (turns > turns_least)
			break ;
		turns_least = turns;
		store_ant_count(head, pants, route->i, lem);
		route = next_compatible(route);
	}
	free(pants);
	// debug start
	ft_printf("Number of the longest path used: %d\n\n", lem->max_flow);
	while (head->i <= lem->max_flow) {
		ft_printf("Path %d\n   length: %d\n   ants: %d\n", head->i, head->len, head->ants);
		head = next_compatible(head);
	}
	// exit(0);
	// debug end
	return (0);
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
