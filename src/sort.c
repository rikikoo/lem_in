/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:24:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/15 23:46:55 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** after distributing ants to all paths currently being tested, we find and
** return the maximum amount of turns by adding the amount of ants distributed
** to each path + that path's length.
**
** @limit: index of the longest path in this iteration of path combinations
*/
static int	calculate_turns(t_route *route, int limit, int *pants)
{
	int	turns;
	int	turns_max;

	turns_max = 0;
	while (route && route->i <= limit)
	{
		turns = route->len + pants[route->i - 1] - 1;
		if (turns > turns_max)
			turns_max = turns;
		route = next_compatible(route);
	}
	return (turns_max);
}

/*
** calculates the difference of the current path's length (@route) and the paths
** following it (@cmp). This difference is the amount of ants that can be passed
** to the current path before using more paths is necessary.
*/
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

/*
** starting from the shortest path, distribute ants to consequtive paths by
** adding one path at a time and calculating the turns it would take to
** transport all ants using these paths. we know the amount of paths needed to
** minimize turns after the calculated amount of turns starts eventually rising
** after first going down.
**
** @route: pointer to the head (shortest) of a list of paths
** @lem: a general runtime info struct
** @ants: total amount of ants
** @pants: an int array where the amount of ants needed per path is stored
*/
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
		if (turns > turns_least)
			break ;
		turns_least = turns;
		store_ant_count(head, pants, route->i, lem);
		route = next_compatible(route);
	}
	free(pants);
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
