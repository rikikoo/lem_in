/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:24:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/05 20:35:45 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_route	*final_path_combo(t_route *route, int n_paths)
{
	t_route	*head;
	t_route	*next;
	int		i;

	head = route;
	next = route->next;
	i = 0;
	while (i < n_paths)
	{
		while (!route->compatible_with[next->i - 1])
			next = next->next;
		route->next = next;
		i++;
	}
	return (head);
}

t_route	*sort_ants(t_route *route, t_lem *lem)
{
	int		turns_least;
	int		turns;
	t_route	*head;

	if (lem->error)
		return (NULL);
	turns_least = ~(1 << ((sizeof(int) * 8) - 1));
	head = route;
	while (route->is_valid)
	{
		turns = compare_combinations(route, lem, turns_least);
		if (turns < turns_least)
		{
			turns_least = turns;
			head = route;
		}
		route = route->next;
	}
	return (final_path_combo(head, lem->n_paths));
}

/*
** swaps places of two paths in the list of paths
*/
static void	swap(t_route *prev, t_route **current, t_route *next)
{
	t_route	*tmp;

	tmp = *current;
	tmp->next = next->next;
	if (prev == NULL)
	{
		*current = next;
		(*current)->next = tmp;
	}
	else
	{
		*current = next;
		prev->next = *current;
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
	while (route)
	{
		next = route->next;
		while (next && next->is_valid)
		{
			if (route->len > next->len)
				swap(prev, &route, next);
			next = next->next;
		}
		prev = route;
		route = route->next;
	}
	return (head);
}
