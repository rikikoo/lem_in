/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:48:11 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/25 10:49:00 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** finds and returns the next compatible path of @route based on the
** @compatibles array, which is updated according to each new path combination
*/
t_route	*next_compatible(t_route *route, int *compatibles)
{
	route = route->next;
	while (route && route->is_valid)
	{
		if (compatibles[route->i - 1])
			return (route);
		route = route->next;
	}
	return (NULL);
}

/*
** loops over the paths following @base up to @limit and marks any path
** that isn't compatible in this path combination as unusable with @base_route.
**
** example: base = B, limit = F
**
**   A  B  C  D  E  F
** A 1  1  1  0  1  1
** B    1  1  1  1  1
** C       1  1  0  1
** D          1  1  1
** E             1  1
** F                1
**
** there is a 0 in the in the area between B and F. in other words, there is an
** incompatible path in the path combination B, C, D, E, F. in this case
** the incompatible one is E, so the final path combo when using B as the base
** is B, C, D, F.
*/
void	set_compatibles(t_route *base, int limit, t_lem *lem)
{
	int		y;
	int		y_lim;
	t_route	*head;

	if (base->i == limit)
		return ;
	head = base;
	y_lim = base->i - 1;
	while (base && base->i <= limit)
	{
		y = base->i - 1;
		while (--y >= y_lim)
		{
			if (lem->compmat[y][base->i - 1] == 0)
				head->compatible_with[base->i - 1] = 0;
		}
		base = base->next;
	}
}

void	free_compmat(t_lem *lem)
{
	int	i;

	i = 0;
	while (i < lem->n_paths)
	{
		free(lem->compmat[i]);
		lem->compmat[i] = NULL;
		i++;
	}
	free(lem->compmat);
	lem->compmat = NULL;
}

/*
** returns a duplicate of a base path's compatibility array
*/
int	*clone_compatibles(int *compatibles, int size)
{
	int	i;
	int	*arr;

	arr = (int *)ft_zeros(size);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		arr[i] = compatibles[i];
		i++;
	}
	return (arr);
}

/*
** once the compatibility arrays for every individual path has been created, we
** store all of them in a single matrix. this matrix is used to determine the
** compatibility within a combination of paths.
*/
void	store_compatibility_matrix(t_route *route, t_lem *lem)
{
	int	**compmat;

	compmat = (int **)malloc(sizeof(int *) * lem->n_paths);
	if (!compmat)
		lem->error = -5;
	else
	{
		while (route && route->is_valid)
		{
			compmat[route->i - 1] = clone_compatibles(route->compatible_with, \
			lem->n_paths);
			if (!compmat[route->i - 1])
			{
				lem->error = -5;
				return ;
			}
			route = route->next;
		}
		lem->compmat = compmat;
	}
}
