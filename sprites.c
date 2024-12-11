/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:18:30 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/09 16:36:06 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	load_img(t_data *data, t_img *img, char *path, int sprite_count)
{
	if (data == NULL || img == NULL || path == NULL || *path == '\0')
		return (0);
	img->img_ptr = mlx_xpm_file_to_image(
			data->mlx, path, &(img->width), &(img->height));
	if (img->img_ptr == NULL)
		return (0);
	img->addr = mlx_get_data_addr(
			img->img_ptr, &(img->bpp), &(img->line_size), &(img->endian));
	if (sprite_count <= 0)
		sprite_count = 1;
	img->sprite_count = sprite_count;
	img->sprite_height = img->height / sprite_count;
	return (1);
}

void	free_img(void *mlx, t_img *img)
{
	if (img->img_ptr != NULL)
		mlx_destroy_image(mlx, img->img_ptr);
	ft_bzero(img, sizeof(t_img));
}

int	load_sprites(t_data *data)
{
	if (load_img(data, &(data->sprites.wall),
			"assets/wall.xpm", 1) == 0)
		return (0);
	if (load_img(data, &(data->sprites.background),
			"assets/background.xpm", 1) == 0)
		return (0);
	if (load_img(data, &(data->sprites.coins), "assets/coins.xpm", 8) == 0)
		return (0);
	if (load_img(data, &(data->sprites.player_left),
			"assets/player_left.xpm", 4) == 0)
		return (0);
	if (load_img(data, &(data->sprites.player_right),
			"assets/player_right.xpm", 4) == 0)
		return (0);
	if (load_img(data, &(data->sprites.opened_exit),
			"assets/opened_exit.xpm", 1) == 0)
		return (0);
	if (load_img(data, &(data->sprites.closed_exit),
			"assets/closed_exit.xpm", 1) == 0)
		return (0);
	if (load_img(data, &(data->sprites.enemy), "assets/enemy.xpm", 4) == 0)
		return (0);
	return (1);
}

static int	get_img_pixel(t_img *img, int x, int y, int sprite)
{
	int	y_offset;

	if (img == NULL || x < 0 || y < 0
		|| x >= img->width || y >= img->sprite_height)
		return (0);
	if (sprite < 0 || sprite >= img->sprite_count)
		sprite = 0;
	y_offset = (y + img->sprite_height * sprite) * img->line_size;
	return (*(int *)(img->addr + y_offset + (x * img->bpp / 8)));
}

void	mlx_blit_img(t_data *data, t_img *img, int x, int y)
{
	int	sprite;
	int	color;
	int	i;
	int	j;

	if (data == NULL || img == NULL || img->img_ptr == NULL)
		return ;
	sprite = 0;
	i = 0;
	while (i < img->sprite_height)
	{
		j = 0;
		while (j < img->width)
		{
			if (img->sprite_count > 1)
				sprite = data->sprite_frame % img->sprite_count;
			color = get_img_pixel(img, j, i, sprite);
			if ((color & 0xFF000000) == 0)
				mlx_pixel_put(data->mlx, data->win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}
