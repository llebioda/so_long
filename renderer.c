/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:08:51 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/10 11:20:05 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void		render_canvas(t_data *data);
void		clear_canvas_area(t_data *data);
static void	*get_sprite(t_data *data, char c);

int	render(t_data *data, int all)
{
	int	x;
	int	y;

	if (data->cam.x < 0 || data->cam.y < 0)
		clear_canvas_area(data);
	if (all == 0)
		render_at(data, data->player.x, data->player.y);
	y = -1;
	while (++y < data->map.height)
	{
		x = -1;
		while (++x < data->map.width)
		{
			if (data->map.data[y][x] == 'C' || data->map.data[y][x] == 'm'
				|| (y == data->cam.y / TILE_SIZE
				&& (x == data->cam.x / TILE_SIZE
				|| x - 1 == data->cam.x / TILE_SIZE)) || all == 1)
				render_at(data, x, y);
		}
	}
	if (data->game_state == PLAYING)
		render_player(data);
	render_canvas(data);
	return (0);
}

void	render_at(t_data *data, int x, int y)
{
	void	*sprite;

	if (x < 0 || x >= data->map.width || y < 0 || y >= data->map.height)
		return ;
	sprite = get_sprite(data, data->map.data[y][x]);
	if (sprite != NULL)
		mlx_put_image_to_window(data->mlx, data->win, sprite,
			x * TILE_SIZE - data->cam.x, y * TILE_SIZE - data->cam.y);
	if (data->map.data[y][x] == 'C')
		blit_img_centered(data, &(data->sprites.coins), x, y);
	else if (data->map.data[y][x] == 'm')
		blit_img_centered(data, &(data->sprites.enemy), x, y);
}

static void	*get_sprite(t_data *data, char c)
{
	if (c == '1')
		return (data->sprites.wall.img_ptr);
	if (c == '0' || c == 'C' || c == 'c' || c == 'P' || c == 'm')
		return (data->sprites.background.img_ptr);
	if (c == 'E')
	{
		if (data->player.coins >= data->player.max_coins)
			return (data->sprites.opened_exit.img_ptr);
		else
			return (data->sprites.closed_exit.img_ptr);
	}
	return (NULL);
}

void	blit_img_centered(t_data *data, t_img *img, int x, int y)
{
	mlx_blit_img(data, img,
		x * TILE_SIZE + (TILE_SIZE - img->width) / 2 - data->cam.x,
		y * TILE_SIZE + (TILE_SIZE - img->sprite_height) / 2 - data->cam.y);
}
