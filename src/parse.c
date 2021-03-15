/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:35:22 by rkyttala          #+#    #+#             */
/*   Updated: 2021/03/15 11:13:23 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	store_command(char *str)
{
	int		i;
	char	*coord;

	i = 0;
	if (str[0] != '#' && str[1] != '#')
		break ;			// error (format)
	if (ft_strcmp(str + 2, "start"))
	{
		get_next_line(1, &command_loc);

	}
}

void		parse_line(char *input)
{
	if (ft_strchr(input, '#'))
		store_command(input);
}
