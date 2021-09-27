/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_sort_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 22:27:06 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/27 18:06:10 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** copies the ants per path to @pants, so the original info isn't lost.
** intermediate routes that are not compatible with the path combo are given
** -1 ants, so we know to not take those paths into consideration later.
*/
void	fill_pants(t_route *route, t_lem lem, int *pants)
{
	int	*compatible;

	compatible = route->compatible_with;
	while (route && route->i <= lem.max_flow)
	{
		if (route->i != 1 && !compatible[route->i - 1])
			pants[route->i - 1] = -1;
		else
			pants[route->i - 1] = route->ants;
		route = route->next;
	}
}

/*
** after each iteration of ant distribution, store ants per path to the path
** structs.
**
** @route: pointer to the head of a list of paths in length-wise ascending order
** @pants: int array storing the number of ants per path
** @limit: index of the longest path used in the current combination of paths
** @lem: pointer to a general runtime info struct
*/
void	store_ant_count(t_route *route, int *pants, int limit, t_lem *lem)
{
	int	i;
	int	*comp;

	lem->max_flow = 0;
	comp = route->compatible_with;
	while (route && route->i <= limit)
	{
		route->ants = pants[route->i - 1];
		if (route->ants > 0)
		{
			lem->last_index = route->i;
			lem->max_flow++;
		}
		route = next_compatible(route, comp);
	}
	i = 0;
	while (i < lem->n_paths)
	{
		pants[i] = 0;
		i++;
	}
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
void	distribute_ants(t_route *route, int limit, int ants, int *pants)
{
	t_route	*head;
	int		*comp;

	if (!ants)
		return ;
	head = route;
	comp = route->compatible_with;
	while (ants)
	{
		while (route && route->i <= limit && ants)
		{
			pants[route->i - 1] += 1;
			ants -= 1;
			route = next_compatible(route, comp);
		}
		route = head;
	}
}

/*
** after distributing ants to all paths currently being tested, we find and
** return the maximum amount of turns by adding the amount of ants distributed
** to each path + that path's length.
**
** @limit: index of the longest path in this iteration of path combinations
*/
int	calculate_turns(t_route *base, int limit, int *pants)
{
	int	turns;
	int	turns_max;
	int	*comp;

	turns_max = 0;
	comp = base->compatible_with;
	while (base && base->i <= limit)
	{
		turns = base->len + pants[base->i - 1] - 1;
		if (turns > turns_max)
			turns_max = turns;
		base = next_compatible(base, comp);
	}
	return (turns_max);
}

/*
** calculates the difference of the current path's length (@route) and the paths
** following it (@base). This difference is the amount of ants that can be passed
** to the current path before using more paths is necessary.
*/
int	calculate_diff(t_route *base, t_route *route, int ants, int *pants)
{
	int	diff;
	int	*comp;

	comp = base->compatible_with;
	while (base && base->i <= route->i && ants)
	{
		diff = route->len - base->len;
		if (diff > ants)
			pants[base->i - 1] = ants;
		else
			pants[base->i - 1] = diff;
		ants -= pants[base->i - 1];
//		ft_printf("%d vs %d diff: %d => ants on %d: %d\n", \
//		route->i, base->i, diff, base->i, pants[base->i - 1]);
		base = next_compatible(base, comp);
	}
	return (ants);
}
