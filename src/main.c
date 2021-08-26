/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/26 13:11:44 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** prints all paths if program got "--paths" as an argument
*/
static void	print_paths(t_route *route, t_vertex *sink)
{
	while (route->is_valid)
	{
		ft_printf("Path length: %i\n", route->len);
		while (route->path->to != sink)
		{
			ft_printf("%s -> ", route->path->src->id);
			route->path = route->path->prev_in_path;
		}
		ft_printf("%s -> %s\n\n", route->path->src->id, route->path->to->id);
		route = route->next;
	}
}

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
**	2. validate and store graph information
**	3. saturate graph by doing repeated searches, updating edge capacities after
**		each run
**	4. separate disjoint, non-overlapping paths from overlapping paths
**	5. calculate how many paths are needed and prepare output strings
**	6. print ant movements
*/
int	main(int argc, char **argv)
{
	t_lem		lem;
	t_hashtab	*ht;
	t_input		*input;
	t_route		*route;

	lem = init_lem();
	ht = init_ht();
	input = read_input();
	route = NULL;
	lem.error = parse_input(input, ht, &lem);
	die_if_error(lem.error, &input, &ht, &route);
	route = sort_paths(find_paths(&lem, lem.source, lem.sink));
	route = find_distinct(route, &lem);
	die_if_error(lem.error, &input, &ht, &route);
/*
	t_route *head = route;
	for (;route->is_valid; route = route->next) {
		ft_printf("Route %d (len %d) is comaptible with:\n", route->i, route->len);
		for (int i = 0; i < lem.n_paths; i++) {
			if (route->compatible_with[i])
				ft_printf("%d, ", i + 1);
		}
		ft_putchar('\n');
	}
	route = head;
*/
	if (argc > 1 && ft_strequ(argv[1], "--paths"))
		print_paths(route, lem.sink);
	else
		print_output(sort_ants(route, &lem), &lem, input);
	die_if_error(lem.error, &input, &ht, &route);
	free_route(&route);
	free_input(&input);
	free_ht(&ht);
	return (0);
}
