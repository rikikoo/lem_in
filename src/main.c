/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/03/16 14:19:37 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_index	read_input(t_lem *lem)
{
	char	*input;
	t_index	*index;
	int		ret;

	input = NULL;
	index = init_index();
	while (ret = get_next_line(1, &input))
	{
		if ret == -1
			return (-1);	// TODO: error (GNL@antfarm)
		parse_line(input, &index);
		free(input);
		input = NULL;
	}
	return (index);
}

int				main(void)
{
	char	*input;
	t_lem	*lem;
	t_index	*index;

	input = NULL;
	if (get_next_line(1, &input) =< 0)
		return (-1);		// TODO: error (GNL@main)
	if (!(lem = (t_lem *)malloc(sizeof(t_lem))))
		return (-1);		// TODO: error (OOM)
	lem->ants = ft_atoi(input);
	free(input);
	index = read_input(lem);
}
