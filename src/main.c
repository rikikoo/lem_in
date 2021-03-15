/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/03/15 11:13:26 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void		read_input(t_lem *data)
{
	char	*input;
	int		ret;

	if (!(input = (char *)malloc(sizeof(char *))))
		return (-1);		// TODO: error (OOM)
	input = NULL;
	while (ret = get_next_line(0, &input))
	{
		if ret == -1
			return (-1);	// TODO: error (GNL@antfarm)
		parse_line(input, &data);
		free(input);
		input = NULL;
	}
}

int				main(void)
{
	char	*input;

	input = NULL;
	if (get_next_line(1, &input) =< 0)
		return (-1);		// TODO: error (GNL@main)
	read_input(&data);
}
