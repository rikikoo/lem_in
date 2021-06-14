/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/06/15 01:16:49 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** lem_in is a program that finds all paths in an undirected graph for n ants
** to go through and prints out the moves the ants will take from source to sink
** with the least amount of moves.
** The number of ants, vertex names and coordinates and their edges are given
** as input in a specific format (see README).
** lem_in will exit and return an error if the format of the instructions is
** invalid or there isn't a connection between the source and the sink.
**
**	1. read instructions from STDIN
**	2. validate and store relevant information into appropriate structs
**	3. construct graph and find all paths
**	4. sort paths
**	5. distribute ants to paths and prepare output strings
**	6. print moves per turn on a single line
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
	routes = NULL;
	if (!input || !index || !lem)
		return (die(&input, &index, &lem, &routes));
	if (parse_input(input, index, lem) < 0)
		return (die(&input, &index, &lem, &routes));
	routes = edm_karp(index, lem);
	if (!routes->is_valid)
		return (die(&input, &index, &lem, &routes));
	free_index(&index);
	while (input != NULL)
	{
		ft_printf("%s\n", input->line);
		input = input->next;
	}
	if (print_moves(sort_paths(routes), lem) < 0)
		(die(&input, &index, &lem, &routes));
	return (0);
}
