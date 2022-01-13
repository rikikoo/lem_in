/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 08:37:04 by rkyttala          #+#    #+#             */
/*   Updated: 2022/01/10 18:39:39 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
** sorts all found paths in ascending order in regards to path length.
** returns sorted path.
**
** @route: pointer to the head of a list of paths
*/
void	sort_paths(t_route *route, t_lem *lem)
{
	t_route	*next;
	int		set;

	set = 1;
	while (set <= lem->path_sets)
	{
		while (route && route->set == set)
		{
			next = route->next;
			while (next && next->set == set)
			{
				if (route->len > next->len && next->is_valid)
					swap_contents(route, next);
				next = next->next;
			}
			route = route->next;
		}
		set++;
	}
}
