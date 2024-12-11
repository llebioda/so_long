/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:54:21 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/10 13:22:59 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <X11/keysym.h>
#include <X11/X.h>

static void	reset_game(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	reload_map(&(data->map));
	data->game_state = PLAYING;
	data->player.coins = 0;
	data->player.x = data->player.spawn.x;
	data->player.y = data->player.spawn.y;
	data->player.direction = 0;
	data->player.move_count = 0;
	update_cam(data, 0);
	render(data, 1);
}

static int	key_release(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_window(data);
	if (data->game_state == PLAYING)
	{
		if (keysym == XK_w)
			check_vertical_collision(data, -1);
		if (keysym == XK_s)
			check_vertical_collision(data, 1);
		if (keysym == XK_a)
			check_horizontal_collision(data, -1);
		if (keysym == XK_d)
			check_horizontal_collision(data, 1);
	}
	else if (keysym == XK_space)
		reset_game(data);
	return (0);
}

static int	game_loop(t_data *data)
{
	static struct timespec	start_time = {0, 0};
	static struct timespec	last_enemy_move_time = {0, 0};
	struct timespec			cur_time;

	clock_gettime(CLOCK_MONOTONIC, &cur_time);
	if (start_time.tv_sec == 0)
		start_time = cur_time;
	data->sprite_frame = SPRITE_RATE * (cur_time.tv_sec - start_time.tv_sec
			+ (cur_time.tv_nsec - start_time.tv_nsec) / 1000000000.0);
	if (data->game_state == PLAYING
		&& (cur_time.tv_nsec - last_enemy_move_time.tv_nsec) / 1000000000.0
		+ (cur_time.tv_sec - last_enemy_move_time.tv_sec) >= ENEMY_MOVE_TIME)
	{
		update_enemies(data);
		last_enemy_move_time = cur_time;
	}
	render(data, 0);
	return (0);
}

static void	init_game(t_data *data)
{
	data->map.total_width = data->map.width * TILE_SIZE;
	data->map.total_height = data->map.height * TILE_SIZE;
	reset_game(data);
	mlx_loop_hook(data->mlx, &game_loop, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &key_release, data);
	mlx_hook(data->win, DestroyNotify, 0, &close_window, data);
	mlx_loop(data->mlx);
	free_data(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		exit_error("Usage : ./so_long map_path.ber\n");
	if (ft_file_as_extension(argv[1], ".ber") == 0)
		exit_error("The file need to have the extension .ber\n");
	ft_bzero(&data, sizeof(t_data));
	if (load_map(argv[1], &data) == 0)
		exit_error("The map cannot be loaded\n");
	data.mlx = mlx_init();
	if (data.mlx == NULL)
		exit_error("Minilibx has not been initialized properly\n");
	if (load_sprites(&data) == 0)
	{
		free_data(&data);
		exit_error("An error occured when loading sprites\n");
	}
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "so_long");
	if (data.win == NULL)
	{
		free_data(&data);
		exit_error("Minilibx's Windows has not been initialized properly\n");
	}
	init_game(&data);
	return (0);
}
