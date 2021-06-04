/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/06/04 13:12:54 by rkyttala         ###   ########.fr       */
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
	if (!routes->is_valid)
		return (die(&input, &index, &lem, &routes));
	prepare_output(routes, lem);
	return (0);
}
