/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/06/02 21:22:46 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	routes = NULL;
	if (!input || !index || !lem)
		return (die(&input, &index, &lem, &routes));
	if (parse_input(input, index, lem) < 0)
		return (die(&input, &index, &lem, &routes));
	routes = edm_karp(index, lem);
	if (!routes)
		return (die(&input, &index, &lem, &routes));
/*
	ft_printf("routes found: %d\n", lem->max_flow);
	while (routes->next != NULL)
	{
		ft_printf("\n");
		for (int i = 0; routes->path[i] != NULL; i++)
		{
			ft_printf("%s\n", routes->path[i]);
		}
		routes = routes->next;
	}
*/
	print_moves(routes, lem);
	return (0);
}
