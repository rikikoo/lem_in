/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:24:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/26 12:21:19 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_route	*sort_ants(t_route *route, t_lem *lem)
{
	int		turns_least;
	int		turns;
	int		paths;
	t_route	*head;

	turns_least = ~(1 << ((sizeof(int) * 8) - 1));
	head = route;
	while (route->is_valid)
	{
		turns = compare_combinations(route, lem, turns_least);
		if (turns <= turns_least)
		{
			turns_least = turns;
			head = route;
			paths = lem->n_paths;
		}
		route = route->next;
	}
	ft_printf("Route %d with its %d compatible routes is the shortest with %d turns\n", \
	head->i, lem->n_paths, turns_least);
	return (head);
}

/*
** swaps places of two paths in the list of paths
*/
static void	swap(t_route **prev, t_route **current, t_route **next)
{
	t_route	*tmp;

	tmp = *current;
	tmp->next = (*next)->next;
	if (*prev == NULL)
	{
		*current = *next;
		(*current)->next = tmp;
	}
	else
	{
		*current = *next;
		(*prev)->next = *current;
		(*current)->next = tmp;
	}
}

/*
** sorts all found paths in ascending order in regards to path length.
** returns sorted path.
**
** @route: pointer to the head of a list of paths
*/
t_route	*sort_paths(t_route *route)
{
	t_route	*prev;
	t_route	*next;
	t_route	*head;

	prev = NULL;
	head = route;
	while (route->is_valid)
	{
		next = route->next;
		while (next->is_valid)
		{
			if (route->len > next->len)
			{
				swap(&prev, &route, &next);
				head = route;
			}
			next = next->next;
		}
		prev = route;
		route = route->next;
	}
	return (head);
}
