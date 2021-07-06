/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:58:34 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/06 19:22:53 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_input(t_input **input)
{
	t_input	*tmp;

	while (*input)
	{
		tmp = *input;
		if ((*input)->line != NULL)
			free((*input)->line);
		*input = (*input)->next;
		free(tmp);
	}
}

void	free_index(t_index **index)
{
	int			i;
	t_vertex	*tmp_vertex;
	t_edge		*tmp_edge;

	i = 0;
	while (i < HT_SIZE)
	{
		while ((*index)->vertices[i] != NULL)
		{
			tmp_vertex = (*index)->vertices[i];
			if (tmp_vertex->id != NULL)
				free(tmp_vertex->id);
			while (tmp_vertex->edge != NULL)
			{
				tmp_edge = tmp_vertex->edge;
				tmp_vertex->edge = tmp_edge->next;
				ft_liberator(3, &(tmp_edge->src), &(tmp_edge->to), &tmp_edge);
			}
			(*index)->vertices[i] = (*index)->vertices[i]->next;
			free(tmp_vertex);
		}
		i++;
	}
	free((*index)->vertices);
	free(*index);
}

void	free_lem(t_lem **lem)
{
	if ((*lem)->source)
		free((*lem)->source);
	if ((*lem)->sink)
		free((*lem)->sink);
	free(*lem);
}

void	free_route(t_route **route)
{
	t_route	*tmp;
	int		i;

	i = 0;
	while (*route != NULL)
	{
		tmp = *route;
		while (tmp->path[i] != NULL)
		{
			free(tmp->path[i]);
			i++;
		}
		*route = (*route)->next;
		free(tmp);
	}
}

void	free_queue(char ***queue, int size)
{
	while (size >= 0)
	{
		if ((*queue)[size] != NULL)
			free((*queue)[size]);
		size--;
	}
	free(*queue);
}
