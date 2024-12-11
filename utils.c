/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:01:03 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/09 16:35:44 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

int	clamp(int v, int min, int max)
{
	if (v < min)
		return (min);
	if (v > max)
		return (max);
	return (v);
}

int	close_window(t_data *data)
{
	free_data(data);
	exit(0);
}

void	exit_error(char *error)
{
	write(2, "Error\n", 6);
	if (error != NULL)
		write(2, error, ft_strlen(error));
	exit(1);
}

void	close_gnl(int fd)
{
	char	*line;

	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	free_data(t_data *data)
{
	free_map(&(data->map));
	if (data->mlx == NULL)
		return ;
	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	free_img(data->mlx, &(data->sprites.wall));
	free_img(data->mlx, &(data->sprites.background));
	free_img(data->mlx, &(data->sprites.coins));
	free_img(data->mlx, &(data->sprites.player_left));
	free_img(data->mlx, &(data->sprites.player_right));
	free_img(data->mlx, &(data->sprites.opened_exit));
	free_img(data->mlx, &(data->sprites.closed_exit));
	free_img(data->mlx, &(data->sprites.enemy));
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	data->mlx = NULL;
}
