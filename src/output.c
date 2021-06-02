/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:24:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/06/02 21:43:22 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** WIP
*/
void	print_moves(t_route *route, t_lem *lem)
{
	int		paths;
	int		ant;
	char	**path;

	ant = 1;
	paths = lem->max_flow;
	path = route->path;
}
