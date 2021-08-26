/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 22:27:06 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/26 12:19:35 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	compare_combinations(t_route *route, t_lem *lem, int turns_least)
{
	int		turns;
	int		paths;
	t_route	*next;

	next = route->next;
	paths = 1;
	while (next->is_valid)
	{
		if (route->compatible_with[next->i - 1])
		{
			paths++;
			turns = (lem->ants / paths) + next->len;
			if (turns <= turns_least)
			{
				turns_least = turns;
				lem->n_paths = paths;
			}
		}
		next = next->next;
	}
	return (turns_least);
}

t_route	*path_reverse(t_route *route)
{
	t_route	*new;
	t_edge	*tmp;

	new = new_route(route->i);
	if (!new)
		return (NULL);
	new->is_valid = route->is_valid;
	new->len = route->len;
	while (route->path)
	{
		tmp = new->path;
		new->path = route->path;
		route->path = route->path->prev_in_path;
		new->path->prev_in_path = tmp;
	}
	return (new);
}

void	print_input(t_input *input)
{
	while (input->next)
	{
		ft_putendl(input->line);
		input = input->next;
	}
	ft_putchar('\n');
}
