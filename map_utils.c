/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:56:31 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/10 10:54:45 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	add_enemies(t_map *map)
{
	int	enemies_to_generate;
	int	rand_row;
	int	rand_col;

	enemies_to_generate = map->enemy_count;
	srand(time(NULL));
	while (enemies_to_generate > 0)
	{
		rand_row = rand() % map->width;
		rand_col = rand() % map->height;
		if (map->data[rand_col][rand_row] == '0')
		{
			map->data[rand_col][rand_row] = 'm';
			enemies_to_generate--;
		}
	}
}

t_vector2	get_neighbour_cell(t_vector2 current, int i)
{
	if (i == 0)
		current.x++;
	else if (i == 1)
		current.x--;
	else if (i == 2)
		current.y++;
	else if (i == 3)
		current.y--;
	return (current);
}

void	free_map(t_map *map)
{
	int	i;

	if (map == NULL)
		return ;
	if (map->data != NULL)
	{
		i = 0;
		while (i < map->height)
			free(map->data[i++]);
		free(map->data);
		map->data = NULL;
	}
}

void	map_error(t_map *map, int fd, char *error)
{
	if (fd >= 0)
		close_gnl(fd);
	if (map != NULL)
		free_map(map);
	exit_error(error);
}
