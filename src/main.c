/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/15 13:39:00 by rkyttala         ###   ########.fr       */
=======
/*   Updated: 2021/07/07 15:02:07 by rkyttala         ###   ########.fr       */
>>>>>>> 3cea61acdd1e37c3f589a586f185f448a84fb5c6
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
	if (parse_input(input, index, lem) < 0)
		return (die(&input, &index, &lem, &routes));
<<<<<<< HEAD
	routes = edm_karp(index, lem);
=======
	routes = find_paths(index, lem, get(index, lem->source));
>>>>>>> 3cea61acdd1e37c3f589a586f185f448a84fb5c6
	if (!routes->is_valid)
		return (die(&input, &index, &lem, &routes));
	print_input(input);
	if (print_moves(sort_paths(routes), lem) < 0)
		(die(&input, &index, &lem, &routes));
	return (0);
}
