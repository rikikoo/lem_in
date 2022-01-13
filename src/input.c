/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 16:49:16 by rkyttala          #+#    #+#             */
/*   Updated: 2022/01/12 23:19:30 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** parses input, which contains all necessary info to construct the graph
** i.e. 1) number of ants 2) vertex names and coordinates 3) graph's edges.
** returns appropriate error code if input is invalid at any point.
**
** @input: pointer to the program input linked list
** @ht: pointer to hash table for vertices
** @lem: pointer to a general runtime info struct
*/
int	parse_input(t_input *input, t_hashtab *ht, t_lem *lem)
{
	if (!input || !ht || !lem)
		return (-5);
	lem->ants = ft_atoi(input->line);
	if (!lem->ants)
		return (-1);
	input = get_vertices(input->next, ht, lem);
	if (!input)
		return (-2);
	lem->edges = get_edges(input, ht);
	if (lem->edges <= 0)
		return (lem->edges);
	return (0);
}

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
** reads program input into a linked list from STDIN, a line at a time.
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
