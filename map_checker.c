/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:07:45 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/09 13:19:19 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_check_line(char *line)
{
	int	i;
	int	a;

	if (line == NULL)
		return (-1);
	i = 0;
	a = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'C'
			|| line[i] == 'E' || line[i] == 'P')
			a++;
		else if (line[i] != '\n')
			return (-1);
		i++;
	}
	return (a);
}

void	map_check_border(t_map *map)
{
	int	i;

	if (map == NULL)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->data[i][0] != '1' || map->data[i][map->width - 1] != '1')
			map_error(map, -1, "The map need to be surrounded by walls\n");
		i++;
	}
	i = 1;
	while (i < map->width - 1)
	{
		if (map->data[0][i] != '1' || map->data[map->height - 1][i] != '1')
			map_error(map, -1, "The map need to be surrounded by walls\n");
		i++;
	}
}

static void	get_map_occurence(t_data *data, int *coins, int *player, int *exit)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map.height)
	{
		j = -1;
		while (++j < data->map.width)
		{
			if (data->map.data[i][j] == 'C')
				(*coins)++;
			else if (data->map.data[i][j] == 'P')
			{
				(*player)++;
				data->player.spawn.x = j;
				data->player.spawn.y = i;
			}
			else if (data->map.data[i][j] == 'E')
			{
				(*exit)++;
				data->map.exit.x = j;
				data->map.exit.y = i;
			}
		}
	}
}

int	map_check_duplicated(t_data *data)
{
	int	coins;
	int	player;
	int	exit;

	if (data == NULL)
		return (-1);
	coins = 0;
	player = 0;
	exit = 0;
	get_map_occurence(data, &coins, &player, &exit);
	if (coins <= 0)
		map_error(&(data->map), -1, "At least 1 item need to be present\n");
	if (player == 0)
		map_error(&(data->map), -1, "A player is required\n");
	if (player > 1)
		map_error(&(data->map), -1, "There can be only 1 player\n");
	if (exit == 0)
		map_error(&(data->map), -1, "An exit is required\n");
	if (exit > 1)
		map_error(&(data->map), -1, "There can be only 1 exit\n");
	return (coins);
}
