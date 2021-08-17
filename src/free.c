/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:58:34 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/17 22:44:24 by rkyttala         ###   ########.fr       */
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

static void	free_ht(t_hashtab **ht)
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

	while (*route)
	{
		tmp = *route;
		*route = (*route)->next;
		free(tmp);
	}
}

void	free_output(char ****out)
{
	int	outer_ptr;
	int	inner_ptr;

	outer_ptr = 0;
	inner_ptr = 0;
	while ((*out)[outer_ptr])
	{
		while ((**out)[inner_ptr])
		{
			free((**out)[inner_ptr]);
			inner_ptr++;
		}
		free((*out)[outer_ptr]);
		outer_ptr++;
	}
	free(*out);
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
