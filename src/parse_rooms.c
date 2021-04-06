/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:35:22 by rkyttala          #+#    #+#             */
/*   Updated: 2021/04/06 09:53:38 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	room_parse(t_index *index, char *str, t_lem *lem, int sink)
{
	char	**arr;
	int		i;
	int		j;

	if (!str)
		return (-1);
	arr = ft_strsplit(str, ' ');
	if (ft_lstlen((void **)arr) != 3)
		return (-1);
	i = 0;
	j = 0;
	while (ft_isdigit(arr[1][i]))
		i++;
	while (ft_isdigit(arr[2][j]))
		j++;
	if (arr[1][i] != '\0' && arr[2][j] != '\0' && i < 1 && j < 1)
		return (-1);
	if (sink)
		lem->target = ft_strdup(arr[0]);
	else
		lem->source = ft_strdup(arr[0]);
	set(index, arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]));
	ft_liberator(4, &arr[0], &arr[1], &arr[2], &arr[3]);
	free(arr);
	return (0);
}

static t_input	*check_command(t_input *input, t_index *index, t_lem *lem)
{
	char	*str;
	char	**arr;
	int		i;

	str = input->line;
	arr = NULL;
	i = 0;
	if (ft_strlen(str) < 3 || (str[0] != '#' && str[1] != '#'))
		return (input->next);
	if (ft_strequ((str + 2), "start") && lem->source == NULL)
	{
		input = input->next;
		if (room_parse(index, input->line, lem, 0) < 0)
			return (NULL);		// TODO: error (format)
	}
	else if (ft_strequ((str + 2), "end") && lem->target == NULL)
	{
		input = input->next;
		if (room_parse(index, input->line, lem, 1) < 0)
			return (NULL);		// TODO: error (format)
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
			if (room_parse(index, input->line, lem, 2) < 0)
				return (NULL);
			input = input->next;
		}
		lem->rooms += 1;
	}
	if (lem->source != NULL && lem->target != NULL)
		return (input);
	else
		return (NULL);
}

int	parse_input(t_input *input, t_index *index, t_lem *lem)
{
	t_input	*tmp;

	lem->ants = ft_atoi(input->line);
	if (!lem->ants)
		return (-1);		// TODO: error (no ants)
	input = get_rooms(input->next, index, lem);
	if (!input)
		return (-1);		// TODO: error (format)
	if (get_tubes(input, index) < 0)
		return (-1);		// TODO: error (format)
	while (input != NULL)
	{
		tmp = input;
		input = input->next;
		free(tmp->line);
		free(tmp);
	}
	return (0);
}
