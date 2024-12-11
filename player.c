/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:35:16 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/10 11:28:40 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_cam(t_data *data, int reset_render)
{
	int	prev_x;
	int	prev_y;

	prev_x = data->cam.x;
	prev_y = data->cam.y;
	if (data->map.total_width > WIN_WIDTH)
		data->cam.x = clamp((data->player.x * TILE_SIZE + TILE_SIZE / 2)
				- WIN_WIDTH / 2, 0, data->map.total_width - WIN_WIDTH);
	else
		data->cam.x = (WIN_WIDTH - data->map.total_width) / -2;
	if (data->map.total_height > WIN_HEIGHT)
		data->cam.y = clamp((data->player.y * TILE_SIZE + TILE_SIZE / 2)
				- WIN_HEIGHT / 2, 0, data->map.total_height - WIN_HEIGHT);
	else
		data->cam.y = (WIN_HEIGHT - data->map.total_height) / -2;
	if (reset_render == 1 && (prev_x != data->cam.x || prev_y != data->cam.y))
		render(data, 1);
}

static void	object_collision(t_data *data, char c, int x, int y)
{
	if (x < 0 || x >= data->map.width || y < 0 || y >= data->map.height)
		return ;
	if (c == 'C')
	{
		data->map.data[y][x] = 'c';
		data->player.coins += 1;
		if (data->player.coins >= data->player.max_coins)
			render_at(data, data->map.exit.x, data->map.exit.y);
	}
	else if (c == 'E')
	{
		if (data->player.coins >= data->player.max_coins)
			data->game_state = WON;
	}
	else if (c == 'm')
		data->game_state = LOSE;
}

void	check_horizontal_collision(t_data *data, int move)
{
	char	c;
	int		x;

	x = data->player.x + move;
	if (x < 0 || x >= data->map.width)
		return ;
	c = data->map.data[data->player.y][x];
	if (c != '1')
	{
		render_at(data, data->player.x, data->player.y);
		data->player.x = x;
		data->player.move_count++;
		if (move == -1)
			data->player.direction = 0;
		else if (move == 1)
			data->player.direction = 1;
	}
	object_collision(data, c, x, data->player.y);
	update_cam(data, 1);
}

void	check_vertical_collision(t_data *data, int move)
{
	char	c;
	int		y;

	y = data->player.y + move;
	if (y < 0 || y >= data->map.height)
		return ;
	c = data->map.data[y][data->player.x];
	if (c != '1')
	{
		render_at(data, data->player.x, data->player.y);
		data->player.y = y;
		data->player.move_count++;
	}
	object_collision(data, c, data->player.x, y);
	update_cam(data, 1);
}

void	render_player(t_data *data)
{
	if (data->player.direction == 0)
		blit_img_centered(data, &(data->sprites.player_left),
			data->player.x, data->player.y);
	else
		blit_img_centered(data, &(data->sprites.player_right),
			data->player.x, data->player.y);
}
