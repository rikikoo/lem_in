/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:13:29 by rkyttala          #+#    #+#             */
/*   Updated: 2021/03/18 21:54:55 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_link	*new_link(int src, int dst)
{
	t_link	*link;

	if (!(link = (t_link *)malloc(sizeof(link))))
		return (NULL);
	link->src = src;
	link->dst = dst;
	link->cost = -1;
	link->next = NULL;
	return (link);
}

t_link	*get_tubes(t_input *input, t_index *index)
{
	char	**arr;
	t_link	*head;
	t_link	*link;

	link = new_link(-1, -1);
	head = link;
	while (input != NULL)
	{
		arr = ft_strsplit(input->line, '-');
		if (sizeof(arr) / sizeof(arr[0]) != 2)
			return (NULL);
		link->src = hashof(arr[0]);
		link->dst = hashof(arr[1]);
		if (index->rooms[link->src] != NULL && index->rooms[link->dst != NULL])
			input = input->next;
		else
			return (NULL);
	}
}
