/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:35:22 by rkyttala          #+#    #+#             */
/*   Updated: 2021/03/18 21:43:40 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int		room_parse(t_index *index, char *str)
{
	char	**arr;

	if (!str)
		return (-1);
	arr = ft_strsplit(str, ' ');
	set(index, arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]));
	return (hashof(arr[0]));
}

static t_input	*check_command(t_input *input, t_index *index, t_lem *lem)
{
	char	*str;
	int		slot;

	str = input->line;
	slot = 0;
	if (ft_strlen(str) < 3 || (str[0] != '#' && str[1] != '#'))
		return (input->next);
	if (!ft_strcmp(*(str + 2), "start") && lem->start == -1)
	{
		input = input->next;
		if ((slot = room_parse(index, input->line)) < 0)
			return (NULL);		// TODO: error (format)
		lem->start = slot;
	}
	else if (!ft_strcmp(*(str + 2), "end") && lem->finish == -1)
	{
		input = input->next;
		if ((slot = room_parse(index, input->line)) < 0)
			return (NULL);		// TODO: error (format)
		lem->finish = slot;
	}
	else
		return (NULL);			// TODO: error (format)
	return (input->next);
}

static t_input	*get_rooms(t_input *input, t_index *index, t_lem *lem)
{
	while (1)
	{
		if (!input)
			return (NULL);
		if (ft_strchr(input->line, '#'))
		{
			input = check_command(input, index, lem);
			if (!input)
				return (NULL);
		}
		else if (ft_strchr(input->line, '-'))
			break ;
		else
		{
			if (room_parse(index, input->line) < 0)
				return (NULL);
			input = input->next;
		}
	}
	if (lem->start >= 0 && lem->finish >= 0)
		return (input);
	else
		return (NULL);
}

t_link			*parse_input(t_input *input, t_index *index, t_lem *lem)
{
	t_link	*links;

	lem->ants = ft_atoi(input->line);
	input = input->next;
	if (!(input = get_rooms(input, index)))
		return (NULL);		// TODO: error (format)
	if (!(links = get_tubes(input, index)))
		return (NULL);		// TODO: error (format)
	return (links);
}
