/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:58:34 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/28 12:57:49 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_input(t_input **input)
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

static void	free_index(t_index **index)
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
				free(tmp_edge);
			}
			(*index)->vertices[i] = (*index)->vertices[i]->next;
			free(tmp_vertex);
		}
		i++;
	}
	free((*index)->vertices);
	free(*index);
}

static void	free_lem(t_lem **lem)
{
	if ((*lem)->source)
		free((*lem)->source);
	if ((*lem)->sink)
		free((*lem)->sink);
	free(*lem);
}

int	die(t_input **input, t_index **index, t_lem **lem, t_route **route)
{
	if (*input)
		free_input(input);
	if (*index)
		free_index(index);
	if (*lem)
		free_lem(lem);
	if (*route)
		free(*route);
	ft_printf("\nE       R\n");
	ft_printf("  R   O  \n");
	ft_printf("    R    \n");
	ft_printf("  R   O  \n");
	ft_printf("E       R\n\n");
	return (-1);
}

void	free_output(char ****out, t_lem *lem)
{
	int		outer_p;
	int		inner_p;

	outer_p = 0;
	inner_p = 0;
	while (outer_p < lem->ants)
	{
		while (**out[inner_p])
		{
			free(**out[inner_p]);
			inner_p++;
		}
		free(*out[outer_p]);
		outer_p++;
	}
	free(*out);
}
