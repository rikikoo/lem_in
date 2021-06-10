/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:24:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/06/10 13:57:28 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	mark_route_lengths(t_route *route)
{
	while (route->is_valid)
	{
		route->len = ft_arrlen((void **)route->path);
		route = route->next;
	}
}

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

t_route	*sort_paths(t_route *route)
{
	t_route	*prev;
	t_route	*curr;
	t_route	*next;
	t_route	*head;

	prev = NULL;
	curr = route;
	head = curr;
	while (curr->next->is_valid)
	{
		next = curr->next;
		while (next->is_valid)
		{
			if (curr->len > next->len)
			{
				swap(&prev, &curr, &next);
				head = curr;
			}
			next = next->next;
		}
		prev = curr;
		curr = curr->next;
	}
	return (head);
}
