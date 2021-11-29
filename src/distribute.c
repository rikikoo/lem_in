/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:24:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/11/29 17:20:55 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** after distributing ants to all paths currently being tested, we find and
** return the maximum amount of turns by adding the amount of ants distributed
** to each path + that path's length.
*/
static int	calculate_turns(t_route *route, int *pants)
{
	int	turns;
	int	turns_max;
	int	set;

	turns_max = 0;
	set = route->path->set;
	while (route && route->path &&  route->path->set == set)
	{
		turns = route->len + pants[route->i] - 1;
		if (turns > turns_max)
			turns_max = turns;
		route = route->next;
	}
	return (turns_max);
}

/*
** loop over all paths in the set until the leftover ants have been distributed
** evenly.
**
** @route: pointer to the head of a list of paths in length-wise ascending order
** @ants: remaining amount of ants
** @pants: int array storing the number of ants per path
*/
static void	distribute_ants(t_route *route, int ants, int *pants)
{
	t_route	*head;
	int		set;

	if (!ants)
		return ;
	head = route;
	set = route->path->set;
	while (ants)
	{
		while (route && route->path && route->path->set == set && ants)
		{
			pants[route->i] += 1;
			ants -= 1;
			route = route->next;
		}
		route = head;
	}
}

/*
** calculates the difference of the current path's length (@route) and the paths
** following it (@cmp) in the current set. This difference is the amount of ants
** that can be passed to the current path before using more paths is necessary.
** returns the leftover ant count.
*/
static int	calculate_diff(t_route *route, int ants, int *pants)
{
	int		diff;
	int		set;
	t_route	*cmp;

	set = route->path->set;
	cmp = route->next;
	while (cmp && cmp->path && cmp->path->set == set && ants)
	{
		diff = cmp->len - route->len;
		if (diff > ants)
			pants[cmp->i] = ants;
		else
			pants[cmp->i] = diff;
		ants -= pants[cmp->i];
		cmp = cmp->next;
	}
	return (ants);
}

static int	distributor(t_route *route, t_lem *lem, int *pants)
{
	int		ants;
	int		turns;

	ants = calculate_diff(route, lem->ants, pants);
	distribute_ants(route, ants, pants);
	turns = calculate_turns(route, pants);
	return (turns);
}

/*
** starting from the shortest path, distribute ants to consequtive paths by
** adding one path at a time and calculating the turns it would take to
** transport all ants using these paths. we know the amount of paths needed to
** minimize turns after the calculated amount of turns starts eventually rising
** after first going down.
**
** @route: pointer to a path in a list of paths
** @lem: pointer to a general runtime info struct
** @pants: an int array where the amount of ants needed per path is stored
*/
int	sort_ants(t_route *route, t_lem *lem, int *pants)
{
	int	turns;
	int	set;

	if (lem->error || !pants)
		return (-5);
	set = route->path->set;
	turns = distributor(route, lem, pants);
	while (route && route->i < set)
	{
		route->ants = pants[route->i];
		if (route->ants > 0)
			lem->last_index = route->i;
		route = route->next;
	}
	free(pants);
	return (turns);
}
