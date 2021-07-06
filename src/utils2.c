/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 19:18:54 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/06 19:21:16 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_input(t_input *input)
{
	while (input->next)
	{
		ft_printf("%s\n", input->line);
		input = input->next;
	}
	ft_putchar('\n');
}
