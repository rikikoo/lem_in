/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/28 20:02:19 by rkyttala         ###   ########.fr       */
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
** reads input (graph info) into a linked list, a line at a time
*/
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
**	1. read instructions from STDIN
**	2. validate and store relevant information into appropriate structs
**	3. free input
**	4. calculate the paths of the ants
**	5. ???
**	6. PROFIT!
*/
int	main(void)
{
	t_input	*input;
	t_index	*index;
	t_lem	*lem;
	t_route	*routes;

	input = read_input();
	index = init_index();
	lem = init_lem();
	if (parse_input(input, index, lem) < 0)
		return (-1);
	routes = edm_karp(index, lem);
	if (!routes)
		return (-1);

	ft_printf("there should be %d routes...\n", lem->max_flow);
	while (routes->next != NULL)
	{
		ft_printf("\n");
		for (int i = 0; routes->path[i] != NULL; i++)
		{
			ft_printf("%s\n", routes->path[i]);
		}
		routes = routes->next;
	}
	return (0);
}
