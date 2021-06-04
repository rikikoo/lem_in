/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:24:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/06/04 18:40:24 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	swap(t_route **prev, t_route **current, t_route **next)
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
	t_route *next;
	t_route	*head;

	prev = NULL;
	curr = route;
	while (curr->next->is_valid)
	{
		if (curr->len == INT_MAX)
			curr->len = ft_arrlen((void **)curr->path);
		next = curr->next;
		while (next->is_valid)
		{
			if (next->len == INT_MAX)
				next->len = ft_arrlen((void **)next->path);
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

/*
** WIP
*/
void	prepare_output(t_route *route, t_lem *lem)
{
	int		i;
	t_route	*head;

	lem->edges++;
	head = route;
	while (route->next != NULL)
	{
		i = 0;
		while (route->path[i + 1] != NULL)
		{
			ft_printf("%s -> ", route->path[i]);
			i++;
		}
		ft_printf("%s\n", route->path[i]);
		route = route->next;
	}
	route = sort_paths(head);
	ft_printf("\n");
	while (route->next != NULL)
	{
		i = 0;
		while (route->path[i + 1] != NULL)
		{
			ft_printf("%s -> ", route->path[i]);
			i++;
		}
		ft_printf("%s\n", route->path[i]);
		route = route->next;
	}
}
