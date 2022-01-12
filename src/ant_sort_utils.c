/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_sort_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 22:27:06 by rkyttala          #+#    #+#             */
/*   Updated: 2022/01/12 18:51:40 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** copies the ants per path to @pants, so the original info isn't lost.
*/
void	fill_pants(t_route *route, int *pants, t_lem *lem)
{
	int	paths;

	if (!pants)
		return ;
	paths = 0;
	while (route && route->is_valid && route->set == lem->best_set)
	{
		paths++;
		pants[route->id - 1] = route->ants;
		route = route->next;
	}
	lem->max_flow = paths;
}

/*
** after distributing ants to all paths currently being tested, we find and
** return the maximum amount of turns by adding the amount of ants distributed
** to each path + that path's length.
*/
int	calculate_turns(t_route *route, int set)
{
	int	turns;
	int	turns_max;

	turns_max = 0;
	while (route && route->is_valid && route->set == set)
	{
		turns = route->len + route->ants - 1;
		if (turns > turns_max)
			turns_max = turns;
		route = route->next;
	}
	return (turns_max);
}

/*
** after calculating differences in route lengths and distributing those
** 'leftover' ants, loop over all paths until remaining ants have been
** distributed evenly.
**
** @route: pointer to the head of a list of paths in length-wise ascending order
** @limit: index of the longest path used in the current combination of paths
** @ants: remaining amount of ants
** @pants: int array storing the number of ants per path
*/
void	distribute_ants(t_route *route, int ants, int set)
{
	t_route	*head;

	if (!ants)
		return ;
	head = route;
	while (ants)
	{
		while (route && route->is_valid && route->set == set && ants)
		{
			route->ants += 1;
			ants -= 1;
			route = route->next;
		}
		route = head;
	}
}

/*
** calculates the difference between the length of the longest path in the set
** and the paths before it. each difference is the amount of ants that can be
** passed to the shorter path before using the following paths.
*/
int	calculate_diff(t_route *route, int ants, int set)
{
	int		diff;
	t_route	*last;

	last = route;
	while (last->next && last->next->is_valid && last->next->set == set)
		last = last->next;
	while (route->id < last->id && ants)
	{
		diff = last->len - route->len;
		if (diff > ants)
			route->ants = ants;
		else
			route->ants = diff;
		ants -= route->ants;
		route = route->next;
	}
	return (ants);
}
