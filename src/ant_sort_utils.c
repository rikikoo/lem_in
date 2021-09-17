/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_sort_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikikyttala <rikikyttala@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 22:27:06 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/17 15:16:23 by rikikyttala      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	update_compatitbility_arr(t_route *route, int n_paths, int k)
{
	int	j;
	int	*new_cmp;

	new_cmp = (int *)malloc(sizeof(int) * n_paths);
	if (!new_cmp)
	{
		free(route->compatible_with);
		route->compatible_with = NULL;
		return ;
	}
	j = 0;
	while (j < n_paths)
	{
		new_cmp[j] = route->compatible_with[k];
		j++;
		k++;
	}
	free(route->compatible_with);
	route->compatible_with = new_cmp;
}

static int	update_indexes(t_route *route, t_lem *lem)
{
	int		i;
	int		first_index;
	t_route	*head;

	head = route;
	i = 0;
	first_index = head->i - 1;
	while (route->is_valid)
	{
		route = route->next;
		i++;
	}
	lem->n_paths = i;
	route = head;
	i = 1;
	while (route->is_valid)
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

t_route	*find_path_combo(t_route *route, t_lem *lem)
{
	t_route	*head;
	int		turns;
	int		turns_least;

	head = route;
	turns_least = ~(1 << ((sizeof(int) * 8) - 1));
	while (route->is_valid)
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

/*
** makes a copy of ants per path, so that we won't lose the info later
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
