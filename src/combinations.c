/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combinations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:19:58 by rkyttala          #+#    #+#             */
/*   Updated: 2022/01/12 23:45:30 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	distributor(t_route *route, t_lem *lem, int set)
{
	int	ants;
	int	turns;

	ants = calculate_diff(route, lem->ants, set);
	distribute_ants(route, ants, set);
	turns = calculate_turns(route, set);
	return (turns);
}

/*
** calculates turns for all path sets.
** returns a pointer to the first route of the set with least turns.
*/
t_route	*find_best_set(t_route *route, t_lem *lem)
{
	t_route	*best_set_head;
	int		turns_least;
	int		turns;
	int		set;

	turns_least = ~(1 << ((sizeof(int) * 8) - 1));
	while (route && route->is_valid)
	{
		set = route->set;
		turns = distributor(route, lem, set);
		if (turns < 0)
			return (NULL);
		if (turns < turns_least)
		{
			best_set_head = route;
			turns_least = turns;
		}
		while (route && route->is_valid && route->set == set)
			route = route->next;
	}
	lem->turns = turns_least;
	lem->best_set = best_set_head->set;
	return (best_set_head);
}
