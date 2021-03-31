/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/03/31 18:11:35 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_lem	*init_lem(void)
{
	t_lem	*lem;

	if (!(lem = (t_lem *)malloc(sizeof(t_lem))))
		return (NULL);		// TODO: error (OOM)
	lem->ants = -1;
	lem->source = NULL;
	lem->target = NULL;
	return (lem);
}

static t_input	*new_node(void)
{
	t_input	*new;

	if (!(new = (t_input *)malloc(sizeof(t_input))))
		return (NULL);
	new->line = NULL;
	new->next = NULL;
	return (new);
}

static t_input	*read_input(void)
{
	t_input	*input;
	t_input	*head;
	int		ret;

	if (!(input = (t_input *)malloc(sizeof(t_input))))
		return (NULL);		// TODO: error (OOM)
	input->line = NULL;
	input->next = NULL;
	head = input;
	while ((ret = get_next_line(0, &input->line)))
	{
		if (ret == -1)
			return (NULL);	// TODO: error (format)
		if (!(input->next = new_node()))
			return (NULL);	// TODO: error (OOM)
		input = input->next;
	}
	return (head);
}

int				main(void)
{
	t_input	*input;
	t_index	*index;
	t_lem	*lem;

	if (!(input = read_input()))
		return (-1);	// TODO: error (format)
	if (!(index = init_index()))
		return (-1);
	if (!(lem = init_lem()))
		return (-1);
	if (parse_input(input, index, lem) < 0)
		return (-1);	// TODO: error (format)
/*
	for (int i = 0; i < SIZE; i++)
	{
		if (index->rooms[i] != NULL)
		{
			if (i == hashof(lem->source))
				ft_printf("---START---\n");
			if (i == hashof(lem->target))
				ft_printf("----END----\n");
			ft_printf("ID:% 11s\nhash:% 9d\n(x, y): (%d, %d)\ntubes to: ",
			index->rooms[i]->id, i, index->rooms[i]->x, index->rooms[i]->y);
			while (index->rooms[i]->tube != NULL)
			{
				ft_printf("%s\t", index->rooms[i]->tube->to);
				index->rooms[i]->tube = index->rooms[i]->tube->next;
			}
			ft_printf("\n");
		}
	}
*/
	return (0);
}
