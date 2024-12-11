/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:18:17 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/10 10:55:03 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_valid_cell(t_map *map, t_vector2 pos, char *visited)
{
	if (pos.x < 0 || pos.x >= map->width || pos.y < 0 || pos.y >= map->height)
		return (0);
	if (map->data[pos.y][pos.x] == '1')
		return (0);
	if (visited[pos.y * map->width + pos.x] == 1)
		return (0);
	return (1);
}

static int	bfs(t_data *data, char *visited, t_vector2 *q, t_vector2 front_back)
{
	t_vector2	current;
	t_vector2	new;
	int			cell_to_reach;
	int			i;

	cell_to_reach = data->player.max_coins + 1;
	while (front_back.x < front_back.y)
	{
		current = q[(front_back.x)++];
		if (data->map.data[current.y][current.x] == 'E'
			|| data->map.data[current.y][current.x] == 'C')
			cell_to_reach--;
		if (cell_to_reach <= 0)
			return (1);
		i = 0;
		while (i < 4)
		{
			new = get_neighbour_cell(current, i++);
			if (is_valid_cell(&(data->map), new, visited) == 0)
				continue ;
			q[(front_back.y)++] = new;
			visited[new.y * data->map.width + new.x] = 1;
		}
	}
	return (0);
}

void	map_check_path(t_data *data)
{
	char		*visited;
	t_vector2	*queue;
	t_vector2	front_back;
	int			return_value;

	visited = ft_calloc(data->map.width * data->map.height, sizeof(char));
	if (visited == NULL)
		map_error(&(data->map), -1, "Malloc allocation failed for visited\n");
	queue = ft_calloc(data->map.width * data->map.height, sizeof(t_vector2));
	if (queue == NULL)
	{
		free(visited);
		map_error(&(data->map), -1, "Malloc allocation failed for queue\n");
	}
	queue[0] = data->player.spawn;
	visited[data->player.spawn.y * data->map.width + data->player.spawn.x] = 1;
	front_back.x = 0;
	front_back.y = 1;
	return_value = bfs(data, visited, queue, front_back);
	free(queue);
	free(visited);
	if (return_value == 0)
		map_error(&(data->map), -1,
			"The player cannot reach the exit or a coin\n");
}
