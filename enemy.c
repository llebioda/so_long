/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:46:42 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/10 11:37:39 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_valid_cell(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	if (map->data[y][x] == '0')
		return (1);
	return (0);
}

static int	can_enemy_move(t_map *map, int enemy_x, int enemy_y)
{
	if (is_valid_cell(map, enemy_x + 1, enemy_y) == 1)
		return (1);
	if (is_valid_cell(map, enemy_x - 1, enemy_y) == 1)
		return (1);
	if (is_valid_cell(map, enemy_x, enemy_y + 1) == 1)
		return (1);
	if (is_valid_cell(map, enemy_x, enemy_y - 1) == 1)
		return (1);
	return (0);
}

static t_vector2	*get_enemies(t_map *map)
{
	t_vector2	*enemies;
	int			x;
	int			y;
	int			i;

	enemies = ft_calloc(map->enemy_count, sizeof(t_vector2));
	if (enemies == NULL)
		return (NULL);
	i = 0;
	y = 1;
	while (y < map->height - 1)
	{
		x = 1;
		while (x < map->width - 1)
		{
			if (map->data[y][x] == 'm')
			{
				enemies[i].x = x;
				enemies[i++].y = y;
			}
			x++;
		}
		y++;
	}
	return (enemies);
}

static t_vector2	get_new_cell(t_map *map, t_vector2 pos)
{
	t_vector2	new_cell;
	int			r;

	r = rand() % 4;
	new_cell = get_neighbour_cell(pos, r);
	while (is_valid_cell(map, new_cell.x, new_cell.y) == 0)
	{
		r = (r + 1) % 4;
		new_cell = get_neighbour_cell(pos, r);
	}
	return (new_cell);
}

void	update_enemies(t_data *data)
{
	t_vector2	*enemies;
	t_vector2	new_cell;
	int			i;

	enemies = get_enemies(&(data->map));
	if (enemies == NULL)
		return ;
	i = -1;
	while (++i < data->map.enemy_count)
	{
		if (can_enemy_move(&(data->map), enemies[i].x, enemies[i].y) == 0)
			continue ;
		new_cell = get_new_cell(&(data->map), enemies[i]);
		data->map.data[enemies[i].y][enemies[i].x] = '0';
		data->map.data[new_cell.y][new_cell.x] = 'm';
		render_at(data, enemies[i].x, enemies[i].y);
		if (new_cell.x == data->player.x && new_cell.y == data->player.y)
			data->game_state = LOSE;
	}
	free(enemies);
}
