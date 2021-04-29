/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:29:14 by rkyttala          #+#    #+#             */
/*   Updated: 2021/04/29 12:04:07 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define HT_SIZE 10000
# include <stdlib.h>
# include <unistd.h>
# include "../libft/includes/libft.h"

typedef struct s_lem
{
	int		ants;
	int		rooms;
	int		tubes;
	char	*source;
	char	*target;
}	t_lem;

typedef struct s_input
{
	char			*line;
	struct s_input	*next;
}	t_input;

typedef struct s_room
{
	char			*id;
	int				x;
	int				y;
	int				visited;
	struct s_link	*tube;
	struct s_room	*next;
}	t_room;

typedef struct s_link
{
	char			*src;
	char			*to;
	int				cost;
	struct s_link	*next;
}	t_link;

typedef struct s_index
{
	struct s_room	**rooms;
	struct s_link	**links;
}	t_index;

int		hashof(const char *key);
t_index	*init_index(void);
void	set(t_index *index, const char *key, const int x, const int y);
t_room	*get(t_index *index, char *key);
t_room	*new_room(const char *key, const int x, const int y);
int		parse_input(t_input *input, t_index *index, t_lem *lem);
int		get_tubes(t_input *input, t_index *index);
int		edm_karp(t_index *index, t_lem *lem);

#endif
