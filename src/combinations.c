/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combinations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:19:58 by rkyttala          #+#    #+#             */
/*   Updated: 2021/11/29 17:44:37 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** copies the ants per path to @pants, so the original info isn't lost.
*/
void	fill_pants(t_route *route, int *pants)
{
	int	set;

	if (!pants)
		return ;
	set = route->path->set;
	while (route && route->is_valid && route->path->set == set)
	{
		pants[route->i] = route->ants;
		route = route->next;
	}
}

/*
**
** the path combo that yields the lowest amount of turns will be used.
** returns the head of the path set with least turns.
*/
t_route	*find_path_combo(t_route *route, t_lem *lem)
{
	int		turns_least;
	int		turns;
	int		set;
	t_route	*best_set;

	count_sets(route, lem);
	turns_least = ~(1 << ((sizeof(int) * 8) - 1));
	while (route && route->is_valid && route->path->set <= lem->path_sets)
	{
		set = route->path->set;
		turns = sort_ants(route, lem, (int *)ft_zeros(lem->max_flow));
		if (turns < 0)
			return (NULL);
		if (turns < turns_least)
		{
			turns_least = turns;
			best_set = route;
		}
		while (route && route->path && route->path->set == set)
			route = route->next;
	}
	lem->max_flow = best_set->path->set;
	lem->turns = sort_ants(best_set, lem, (int *)ft_zeros(lem->max_flow));
	return (best_set);
}

/*
** swaps the path pointer and length values of two nodes in the list of paths
*/
static void	swap_contents(t_route *longer, t_route *shorter)
{
	int		tmp_len;
	t_path	*tmp_path;

	tmp_len = longer->len;
	tmp_path = longer->path;
	longer->len = shorter->len;
	longer->path = shorter->path;
	shorter->len = tmp_len;
	shorter->path = tmp_path;
}

/*
** sorts all paths in each set to ascending order relative to path length.
*/
void	sort_sets(t_route *route, t_lem *lem)
{
	t_route	*next;
	int		set;
	int		i;

	set = 1;
	while (set <= lem->path_sets)
	{
		i = 0;
		while (route && route->is_valid && route->path->set == set)
		{
			route->i = i;
			next = route->next;
			while (next && next->is_valid && next->path->set == set)
			{
				if (route->len > next->len)
					swap_contents(route, next);
				next = next->next;
			}
			route = route->next;
			i++;
		}
		set++;
	}
}
