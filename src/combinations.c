/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combinations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:19:58 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/22 13:50:43 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	update_compatitbility_arr(t_route *route, int n_paths, int k)
{
	int	j;
	int	*new_compatible;

	new_compatible = (int *)malloc(sizeof(int) * n_paths);
	if (!new_compatible)
	{
		free(route->compatible_with);
		route->compatible_with = NULL;
		return ;
	}
	j = 0;
	while (j < n_paths)
	{
		new_compatible[j] = route->compatible_with[k];
		j++;
		k++;
	}
	free(route->compatible_with);
	route->compatible_with = new_compatible;
}

/*
** if the head of the final path combination isn't the shortest, we will
** re-index from 1 to n_paths starting from the head.
*/
static int	update_indexes(t_route *route, t_lem *lem)
{
	int		i;
	int		first_index;
	t_route	*head;

	head = route;
	i = 0;
	first_index = head->i - 1;
	while (route && route->is_valid)
	{
		route = route->next;
		i++;
	}
	lem->n_paths = i;
	route = head;
	i = 1;
	while (route && route->is_valid)
	{
		route->i = i;
		i++;
		update_compatitbility_arr(route, lem->n_paths, first_index);
		if (!route->compatible_with)
			return (-5);
		route = route->next;
	}
	return (0);
}

/*
** calculates turns for all path combinations, starting from shortest path and
** finding the minimimum turns using the following paths, then the second
** shortest and its following paths, and so on. the path combo that yields the
** lowest amount of turns will be used.
** returns the head of the combo with least turns.
*/
t_route	*find_path_combo(t_route *route, t_lem *lem)
{
	t_route	*head;
	int		turns;
	int		turns_least;

	head = route;
	turns_least = ~(1 << ((sizeof(int) * 8) - 1));
	while (route && route->is_valid)
	{
		turns = sort_ants(route, lem, lem->ants, (int *)ft_zeros(lem->n_paths));
		if (turns < 0)
		{
			lem->error = turns;
			return (NULL);
		}
		if (turns < turns_least)
		{
			turns_least = turns;
			head = route;
		}
		route = route->next;
	}
	lem->error = update_indexes(head, lem);
	sort_ants(head, lem, lem->ants, (int *)ft_zeros(lem->n_paths));
	return (head);
}
