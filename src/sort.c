/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:24:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/28 18:11:31 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	distributor(t_route *base, t_route *route, t_lem *lem, int *pants)
{
	int		ants;
	int		turns;

	set_compatibles(base, route->i, lem);
	ants = calculate_diff(base, route, lem->ants, pants);
	distribute_ants(base, route->i, ants, pants);
	turns = calculate_turns(base, route->i, pants);
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
int	sort_ants(t_route *route, t_lem *lem, int *pants, int final)
{
	t_route	*head;
	int		turns_least;
	int		turns;
	int		i;

	if (lem->error || !pants)
		return (-5);
	head = route;
	turns_least = ~(1 << ((sizeof(int) * 8) - 1));
	while (route && route->is_valid)
	{
		turns = distributor(head, route, lem, pants);
		if (turns > turns_least)
			break ;
		turns_least = turns;
		store_ant_count(head, pants, route->i, lem);
		route = next_compatible(route, head->compatible_with);
	}
	free(pants);
	if (final)
		return (turns_least);
	i = -1;
	while (++i < lem->n_paths)
		head->compatible_with[i] = lem->compmat[head->i - 1][i];
	return (turns_least);
}

/*
** swaps the path pointer and length values of two nodes in the list of paths
*/
static void	swap_contents(t_route *longer, t_route *shorter)
{
	int		tmp_len;
	t_edge	*tmp_path;

	tmp_len = longer->len;
	tmp_path = longer->path;
	longer->len = shorter->len;
	longer->path = shorter->path;
	shorter->len = tmp_len;
	shorter->path = tmp_path;
}

/*
** sorts all found paths in ascending order in regards to path length.
** returns sorted path.
**
** @route: pointer to the head of a list of paths
*/
t_route	*sort_paths(t_route *route)
{
	t_route	*next;
	t_route	*head;

	head = route;
	while (route)
	{
		next = route->next;
		while (next && next->is_valid)
		{
			if (route->len > next->len)
				swap_contents(route, next);
			next = next->next;
		}
		route = route->next;
	}
	return (head);
}
