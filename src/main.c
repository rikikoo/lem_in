/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/03/18 21:32:48 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_lem	*init_lem(void)
{
	t_lem	*lem;

	if (!(lem = (t_lem *)malloc(sizeof(t_lem))))
		return (NULL);		// TODO: error (OOM)
	lem->ants = -1;
	lem->start = -1;
	lem->finish = -1;
}

static t_input	*new_node(void)
{
	t_input	*new;

	if (!(new = (t_input *)malloc(sizeof(t_input))))
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

	if (!(input = (t_input *)malloc(sizeof(t_input))))
		return (NULL);		// TODO: error (OOM)
	input->line = NULL;
	input->next = NULL;
	head = input;
	while (ret = get_next_line(1, &input->line))
	{
		if ret == -1
			return (NULL);	// TODO: error (format)
		if (!(input->next = new_node()))
			return (NULL);	// TODO: error (OOM)
		input = input->next;
	}
	return (head);
}

int				main(void)
{
	t_input	*input;
	t_index	*index;
	t_lem	*lem;
	t_graph	*graph;
	t_link	*links;

	if (!(input = read_input()))
		return (-1);	// TODO: error (format)
	index = init_index();
	lem = init_lem();
	if (!(links = parse_input(input, index, lem)))
		return (-1);	// TODO: error (format)
	graph = create_graph(index, links, lem);
}
