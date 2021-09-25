/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combinations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:19:58 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/25 20:42:12 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
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
*/

static t_route	*clone_route(t_route *route, int i)
{
	t_route	*new;

	new = new_route(i);
	if (!new)
		return (NULL);
	new->is_valid = route->is_valid;
	new->len = route->len;
	new->ants = route->ants;
	new->path = route->path;
	return (new);
}

/*
** discards incompatible paths from the final combo and re-indexes the paths
** from 1 to n_paths starting from the head.
*/
static t_route	*assemble_final_combo(t_route *route, t_lem *lem)
{
	int		i;
	int		*comp;
	t_route	*old_head;
	t_route	*new_head;
	t_route	*new_route;

	i = 1;
	comp = route->compatible_with;
	old_head = route;
	new_head = clone_route(route, i);
	new_head->compatible_with = (int *)ft_zeros(lem->max_flow);
	if (!new_head || !new_head->compatible_with)
		return (NULL);
	new_route = new_head;
	route = next_compatible(route, comp);
	while (route && route->is_valid && i <= lem->max_flow)
	{
		new_head->compatible_with[i] = comp[route->i - 1];
		i++;
		new_route->next = clone_route(route, i);
		new_route = new_route->next;
		route = next_compatible(route, comp);
	}
	free_route(&old_head);
	return (new_head);
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
	store_compatibility_matrix(route, lem);
	while (route && route->is_valid)
	{
		turns = sort_ants(route, lem, (int *)ft_zeros(lem->n_paths), 0);
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
	sort_ants(head, lem, (int *)ft_zeros(lem->n_paths), 1);
	route = assemble_final_combo(head, lem);
	return (route);
}
