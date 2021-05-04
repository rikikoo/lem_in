/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/04/30 14:49:44 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_lem	*init_lem(void)
{
	t_lem	*lem;

	lem = (t_lem *)malloc(sizeof(t_lem));
	if (!lem)
		return (NULL);
	lem->ants = 0;
	lem->rooms = 0;
	lem->tubes = 0;
	lem->source = NULL;
	lem->target = NULL;
	return (lem);
}

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

static t_input	*read_input(void)
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
			return (NULL);	// TODO: error (format)
		if (ret == 0)
			break ;
		input->next = new_node();
		if (!input->next)
			return (NULL);
		input = input->next;
	}
	return (head);
}

int	main(void)
{
	t_input	*input;
	t_index	*index;
	t_lem	*lem;

	input = read_input();
	index = init_index();
	lem = init_lem();
	if (parse_input(input, index, lem) < 0)
		return (-1);	// TODO: error (format)
	if (edm_karp(index, lem) < 0)
		return (-1);	// TODO: error (incomplete graph)
	return (0);
}
