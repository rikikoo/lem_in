/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/11/29 17:28:24 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** prints all paths if program got "--paths" as an argument
*/
static void	print_paths(t_route *route, t_lem lem)
{
	int	set;

	if (lem.error)
		return ;
	set = 0;
	while (route && route->is_valid && ++set)
	{
		ft_printf("\n\033[0;35mSET %d\033[0m\n\n", set);
		while (route && route->path && route->path->set == set)
		{
			ft_printf("Path (index %d) length: %i\n", route->i, route->len);
			while (route->path->edge->to != lem.sink)
			{
				ft_printf("%s -> ", route->path->edge->src->id);
				route->path = route->path->next;
			}
			ft_printf("%s -> %s\n\n", route->path->edge->src->id, \
			route->path->edge->to->id);
			route = route->next;
		}
	}
}

void	print_input(t_input *input)
{
	while (input->next)
	{
		ft_putendl(input->line);
		input = input->next;
	}
	ft_putchar('\n');
}

/*
** lem_in is a program that finds all paths in an undirected graph for n ants
** to go through and prints out the moves the ants will take from source to sink
** with the least amount of moves.
** The number of ants, vertex names and coordinates and their edges are given
** as input in a specific format (see README).
** lem_in will exit and return an error value and message if the input format is
** invalid or there isn't a connection between the source and the sink.
**
**	1. read instructions from STDIN
**	2. validate and store graph information
**	3. saturate graph by doing repeated searches, updating edge capacities after
**		each run
**	4. calculate how many paths are needed and prepare output strings
**	5. print ant movements
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
	lem.error = parse_input(input, ht, &lem);
	route = saturate_graph(&lem);
	die_if_error(lem.error, &input, &ht, &route);
	sort_sets(route, &lem);
	if (argc > 1 && ft_strequ(argv[1], "--paths"))
		print_paths(route, lem);
	else
	{
		route = find_path_combo(route, &lem);

		ft_printf("max flow: %d\ntotal sets: %d\namount of turns: %d\n", \
		lem.max_flow, lem.path_sets, lem.turns);
		exit(0);

		lem.error = print_output(route, lem, input);
	}
	free_route(&route);
	free_input(&input);
	free_ht(&ht);
	return (lem.error);
}
