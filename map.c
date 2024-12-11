/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:06:47 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/10 09:54:44 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

int			map_check_line(char *line);
void		map_check_border(t_map *map);
int			map_check_duplicated(t_data *data);
void		map_check_path(t_data *data);
void		add_enemies(t_map *map);

static int	set_map_size(t_map *map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL && (*line == '\n' || *line == '\0'))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line == NULL || map_check_line(line) <= 2)
		return (free(line), 0);
	map->width = map_check_line(line);
	map->height = 0;
	while (line != NULL)
	{
		if ((*line == '\n' || *line == '\0') && map->height > 2)
			return (free(line), 1);
		if (((*line == '\n' || *line == '\0') && map->height <= 2)
			|| (map_check_line(line) != map->width))
			return (free_map(map), free(line), 0);
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

static void	set_map_data(t_map *map, int fd)
{
	char	*line;
	int		i;

	map->data = ft_calloc(map->height, sizeof(char *));
	if (map->data == NULL)
		map_error(map, fd, "Malloc allocation for the map has failed\n");
	line = get_next_line(fd);
	while (line != NULL && (*line == '\n' || *line == '\0'))
	{
		free(line);
		line = get_next_line(fd);
	}
	i = 0;
	while (i < map->height)
	{
		if (line == NULL)
			map_error(map, fd, "An error occured when reading next line\n");
		map->data[i] = ft_substr(line, 0, map->width);
		free(line);
		if (map->data[i] == NULL)
			map_error(map, fd, "ft_substr malloc allocation has failed\n");
		line = get_next_line(fd);
		i++;
	}
	free(line);
}

static void	set_enemy_count(t_map *map)
{
	int	x;
	int	y;
	int	c;

	c = 0;
	y = 1;
	while (y < map->height - 1)
	{
		x = 1;
		while (x < map->width - 1)
		{
			if (map->data[y][x++] == '0')
				c++;
		}
		y++;
	}
	map->enemy_count = 0;
	if (c > 220)
		map->enemy_count = 4;
	else if (c > 120)
		map->enemy_count = 3;
	else if (c > 50)
		map->enemy_count = 2;
	else if (c > 10)
		map->enemy_count = 1;
}

int	load_map(char *map_path, t_data *data)
{
	int	fd;
	int	r;

	if (map_path == NULL || *map_path == '\0')
		return (0);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (0);
	r = set_map_size(&(data->map), fd);
	close_gnl(fd);
	if (r == 0)
		return (0);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (free_map(&(data->map)), 0);
	set_map_data(&(data->map), fd);
	close_gnl(fd);
	map_check_border(&(data->map));
	data->player.max_coins = map_check_duplicated(data);
	map_check_path(data);
	set_enemy_count(&(data->map));
	add_enemies(&(data->map));
	return (1);
}

void	reload_map(t_map *map)
{
	int	x;
	int	y;

	y = 1;
	while (y < map->height - 1)
	{
		x = 1;
		while (x < map->width - 1)
		{
			if (map->data[y][x] == 'c')
				map->data[y][x] = 'C';
			else if (map->data[y][x] == 'm')
				map->data[y][x] = '0';
			x++;
		}
		y++;
	}
	add_enemies(map);
}
