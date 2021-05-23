void	print_links(t_index *index, t_lem *lem)
{
	t_room *room;
	t_link *link;

	ft_printf("Number of ants: %i\n", lem->ants);
	ft_printf("Number of rooms: %i\n", lem->rooms);
	ft_printf("Number of tubes: %i\n\n", lem->tubes);
	for (int i = 0; i < HT_SIZE; i++) {
		if (index->rooms[i] != NULL)
		{
			room = index->rooms[i];
			while (room != NULL)
			{
				if (room->tube != NULL)
				{
					link = room->tube;
					while (link != NULL)
					{
						ft_printf("Found a link! %s -> %s\n", \
						link->src, link->to);
						link = link->next;
					}
				}
				room = room->next;
			}
		}
	}
}
