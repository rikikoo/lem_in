/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/20 23:53:30 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** prints a boolean matrix of compatible paths
*/
static void	print_compatibles(t_route *route, int n_paths)
{
	int	i;

	i = 0;
	while (++i <= n_paths)
		ft_printf("%-3d", i);
	ft_putchar('\n');
	while (route && route->is_valid)
	{
		i = 0;
		while (i < n_paths)
		{
			if (route->compatible_with[i] == 1)
				ft_printf("\033[0;32m%-3d\033[0m", route->compatible_with[i]);
			else if (route->i == i + 1)
				ft_printf("\033[0;33m%-3d\033[0m", route->compatible_with[i]);
			else
				ft_printf("%-3d", route->compatible_with[i]);
			i++;
		}
		ft_putchar('\n');
		route = route->next;
	}
	ft_putchar('\n');
}

/*
** prints all paths if program got "--paths" as an argument
*/
static void	print_paths(t_route *route, t_lem lem)
{
	if (lem.error)
		return ;
	print_compatibles(route, lem.n_paths);
	while (route && route->is_valid)
	{
		ft_printf("Path no. %d length: %i\n", route->i, route->len);
		while (route->path->to != lem.sink)
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
** lem_in will exit and return an error value and message if the input format is
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
	t_route		*bw_route;

	lem = init_lem();
	ht = init_ht();
	input = read_input();
	lem.error = parse_input(input, ht, &lem);
	route = find_paths(&lem, lem.source, lem.sink);
	die_if_error(lem.error, &input, &ht, &route);
	bw_route = find_paths(&lem, lem.sink, lem.source);
/*
	// debug start
	t_route *rhead = route;
	while (route->is_valid) {
		ft_printf("\nPath %d - (len %d)\n", route->i, route->len);
		route = route->next;
	}
	route = rhead;
	ft_printf("\n\nBW_ROUTES START\n\n");
	rhead = bw_route;
	while (bw_route->is_valid) {
		ft_printf("\nPath %d - (len %d)\n", bw_route->i, bw_route->len);
		bw_route = bw_route->next;
	}
	bw_route = rhead;
	//debug end
*/
	route = find_distinct(route, bw_route, &lem);
	if (argc > 1 && ft_strequ(argv[1], "--paths"))
		print_paths(route, lem);
	else
	{
		route = find_path_combo(route, &lem);
		lem.error = print_output(route, lem, input, fill_pants(route, lem));
	}
	free_route(&route);
	free_input(&input);
	free_ht(&ht);
	return (lem.error);
}
