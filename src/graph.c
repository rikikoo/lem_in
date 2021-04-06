/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:28:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/04/06 10:21:28 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	bfs(t_link *src, t_link *dst)
{
	int	flow;

	flow = 0;
	if (src->cost == 0 && src->src != dst->src)
		flow++;
	return (flow);
}

int	edm_karp(t_index *index, t_lem *lem)
{
	for (int i = 0; i < lem->rooms; i++) {
		if (index->rooms[i] != NULL)
		{
			ft_printf("Found a link! %s -> %s\n", \
			index->rooms[i]->id, \
			index->rooms[i]->tube->to);
			ft_printf("Flow: %i", bfs(index->rooms[i]->tube, \
			index->rooms[i]->tube->next));
		}
	}
	return (0);
}
