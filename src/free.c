/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:58:34 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/20 16:10:50 by rkyttala         ###   ########.fr       */
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

void	free_ht(t_hashtab **ht)
{
	int			i;
	t_vertex	*tmp_vertex;
	t_edge		*tmp_edge;

	i = 0;
	while (i < HT_SIZE)
	{
		while ((*ht)->vertices[i] != NULL)
		{
			tmp_vertex = (*ht)->vertices[i];
			if (tmp_vertex->id != NULL)
				free(tmp_vertex->id);
			while (tmp_vertex->edge != NULL)
			{
				tmp_edge = tmp_vertex->edge;
				tmp_vertex->edge = tmp_edge->next_adjacent;
				free(tmp_edge);
			}
			(*ht)->vertices[i] = (*ht)->vertices[i]->next;
			free(tmp_vertex);
		}
		i++;
	}
	free((*ht)->vertices);
	free(*ht);
}

void	free_route(t_route **route)
{
	t_route	*tmp;

	while (*route != NULL)
	{
		tmp = *route;
		*route = (*route)->next;
		free(tmp);
	}
}

void	free_output(char ***out)
{
	int		i_path;
	int		i_move;

	i_path = 0;
	i_move = 0;
	while (out[i_path] != NULL)
	{
		while (out[i_path][i_move] != NULL)
		{
			free(out[i_path][i_move]);
			i_move++;
		}
		i_move = 0;
		free(out[i_path]);
		i_path++;
	}
	free(out);
}

int	die(t_input **input, t_hashtab **ht, t_lem *lem, t_route **route)
{
	int	error;

	if (!input || !ht)
		return (ft_printf("ERROR: Out of memory\n") * -1);
	error = lem->error;
	if (error < 0)
	{
		if (error == -1)
			ft_printf("ERROR: Number of ants not specified\n");
		else if (error == -2)
			ft_printf("ERROR: Invalid rooms specified\n");
		else if (error == -3)
			ft_printf("ERROR: Invalid rooms in links\n");
		else
			ft_printf("ERROR: Sink not reachable\n");
	}
	free_input(input);
	free_ht(ht);
	free_route(route);
	return (error);
}
