/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distinction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:31:47 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/24 19:02:06 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	**init_clash(int size)
{
	int	**clash;
	int	i;

	clash = (int **)malloc(sizeof(int *) * size);
	if (!clash)
		return (NULL);
	i = 0;
	while (i < size)
	{
		clash[i] = (int *)ft_zeros(size);
		if (!clash[i])
			return (NULL);
		i++;
	}
	return (clash);
}

static int	paths_are_distinct(t_edge *path, t_edge *cmp, t_vertex *sink)
{
	t_edge	*cmp_head;

	cmp_head = cmp;
	while (path && path->to != sink)
	{
		while (cmp && cmp->to != sink)
		{
			if (cmp->to == path->to)
				return (0);
			cmp = cmp->prev_in_path;
		}
		path = path->prev_in_path;
		cmp = cmp_head;
	}
	return (1);
}

static int	**get_distinct_paths(t_route *route, t_lem lem)
{
	t_route	*next;
	int		**clash;

	next = route->next;
	clash = init_clash(lem.n_paths);
	if (!clash)
		return (NULL);
	while (route->is_valid)
	{
		next = route->next;
		while (next->is_valid)
		{
			if (!paths_are_distinct(route->path, next->path, lem.sink))
			{
				clash[route->i - 1][next->i - 1] = 1;
				ft_printf("Route %d clashes with %d\n", route->i-1, next->i-1);
			}
			next = next->next;
		}
		route = route->next;
	}
	return (clash);
}

static t_route	*revalidate_paths(t_route *route, t_lem lem, int **clash)
{
	int		n;
	int		m;
	t_route	*head;

	if (!route || !clash)
		return (NULL);
	n = 0;
	head = route;
	while (n < lem.n_paths)
	{
		m = 0;
		while (m < lem.n_paths)
		{
			if (clash[n][m])
			{
				route->is_valid = 0;
				break ;
			}
			m++;
		}
		route = route->next;
		n++;
	}
	return (head);
}

/*
** reverses all paths and sends them forward for parsing before returning a list
** of distinct paths
*/
t_route	*find_distinct(t_route *route, t_lem lem)
{
	t_route	*reversed;
	t_route	*rev_head;
	t_route	*head;

	reversed = path_reverse(route);
	rev_head = reversed;
	head = route;
	route = route->next;
	while (route)
	{
		reversed->next = path_reverse(route);
		reversed = reversed->next;
		route = route->next;
	}
	free_route(&head);
	return (revalidate_paths(rev_head, lem, get_distinct_paths(rev_head, lem)));
}
