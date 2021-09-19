/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_sort_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 22:27:06 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/19 19:49:00 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** returns a copy of ants per path, so that the original info isn't lost
*/
int	*fill_pants(t_route *route, t_lem lem)
{
	int	*pants;

	pants = (int *)ft_zeros(lem.max_flow);
	if (!pants)
		return (NULL);
	while (route && route->i <= lem.max_flow)
	{
		pants[route->i - 1] = route->ants;
		route = next_compatible(route);
	}
	return (pants);
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

	while (route && route->i <= limit)
	{
		route->ants = pants[route->i - 1];
		if (route->ants)
			lem->max_flow = route->i;
		route = next_compatible(route);
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

	if (!ants)
		return ;
	head = route;
	while (ants)
	{
		while (route && route->i <= limit && ants)
		{
			pants[route->i - 1] += 1;
			ants -= 1;
			route = next_compatible(route);
		}
		route = head;
	}
}
