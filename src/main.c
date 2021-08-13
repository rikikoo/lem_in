/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/13 13:09:47 by rkyttala         ###   ########.fr       */
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
**	6. print moves per turn
*/
int	main(void)
{
	t_lem	lem;
	t_input	*input;
	t_index	*index;
	t_route	*route;

	lem = init_lem();
	input = read_input();
	index = init_index();
	route = NULL;
	lem.error = parse_input(input, index, &lem);
	if (lem.error)
		return (die(&input, &index, &lem, &route));
	route = find_paths(&lem, get(index, lem.source), get(index, lem.sink));
//	if (lem.error)
//		return (die(&input, &index, &lem, &route));
	route = sort_paths(route);

	ft_printf("reversed paths in increasing order of length:\n\n");
	while (route->is_valid) {
		ft_printf("Route length: %i\n", route->len);
		while (!ft_strequ(route->path->src->id, lem.source)) {
			ft_printf("%s <- ", route->path->to->id);
			route->path = route->path->prev_in_path;
		}
		ft_printf("%s <- %s\n\n", route->path->to->id, route->path->src->id);
		route = route->next;
	}
	system("leaks lem-in");

//	print_input(input);
//	print_moves(sort_paths(route), &lem);
	return (0);
}
