/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:28:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/04/07 19:54:58 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	bfs(t_link *link)
{
	return (link->cost);
}

static void	print_links(t_index *index, t_lem *lem)
{
	t_room *room;
	t_link *link;

	ft_printf("Number of ants: %i\n", lem->ants);
	ft_printf("Number of rooms: %i\n", lem->rooms);
	ft_printf("Number of tubes: %i\n\n", lem->tubes);
	for (int i = 0; i < HT_SIZE; i++) {
		if (index->rooms[i] != NULL)
		{
			room = index->rooms[i];
			while (room != NULL)
			{
				if (room->tube != NULL)
				{
					link = room->tube;
					while (link != NULL)
					{
						ft_printf("Found a link! %s -> %s\t\tflow: %d\n", \
						link->src, link->to, bfs(link));
						link = link->next;
					}
				}
				room = room->next;
			}
		}
	}
}

int	edm_karp(t_index *index, t_lem *lem)
{
	print_links(index, lem);
	return (0);
}
