/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 16:49:16 by rkyttala          #+#    #+#             */
/*   Updated: 2021/06/14 19:15:15 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** returns a new list element
*/
static t_input	*new_node(void)
{
	t_input	*new;

	new = (t_input *)malloc(sizeof(t_input));
	if (!new)
		return (NULL);
	new->line = NULL;
	new->next = NULL;
	return (new);
}

/*
** reads input (graph info) into a linked list, a line at a time, from STDIN.
** returns head of the list (first line) after reaching EOF.
*/
t_input	*read_input(void)
{
	t_input	*input;
	t_input	*head;
	int		ret;

	input = new_node();
	if (!input)
		return (NULL);
	input->line = NULL;
	input->next = NULL;
	head = input;
	while (1)
	{
		ret = get_next_line(0, &input->line);
		if (ret == -1)
			return (NULL);
		if (ret == 0)
			break ;
		input->next = new_node();
		if (!input->next)
			return (NULL);
		input = input->next;
	}
	return (head);
}

/*
** parses input, which contains all necessary info to construct the graph
** and frees it after it's been processed and stored.
**
** input: pointer to the program input linked list
** index: pointer to hash table for vertices
** lem: pointer to a general runtime info struct
*/
int	parse_input(t_input *input, t_index *index, t_lem *lem)
{
	t_input	*tmp;

	lem->ants = ft_atoi(input->line);
	if (!lem->ants)
		return (-1);
	tmp = get_vertices(input->next, index, lem);
	if (!tmp)
		return (-1);
	lem->edges = get_edges(tmp, index);
	if (lem->edges < 0)
		return (-1);
	while (input != NULL)
	{
		tmp = input;
		input = input->next;
		free(tmp->line);
		free(tmp);
	}
	return (0);
}
