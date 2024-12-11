/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_renderer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:21:41 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/10 11:22:46 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	render_coins(t_data *data);

void	render_canvas(t_data *data)
{
	char	*move_nb;
	char	*text;

	if (data->game_state != PLAYING)
	{
		if (data->game_state == WON)
			mlx_string_put(data->mlx, data->win, WIN_WIDTH / 2 - 33,
				WIN_HEIGHT / 2 - 8, 0xFFFFFFFF, "You escaped");
		else if (data->game_state == LOSE)
			mlx_string_put(data->mlx, data->win, WIN_WIDTH / 2 - 57,
				WIN_HEIGHT / 2 - 8, 0xFFFFFFFF, "You have been eaten");
		mlx_string_put(data->mlx, data->win, WIN_WIDTH / 2 - 66,
			WIN_HEIGHT / 2 + 8, 0xFFFFFFFF, "Press SPACE to restart");
	}
	render_coins(data);
	move_nb = ft_itoa(data->player.move_count);
	if (move_nb == NULL)
		return ;
	text = ft_strjoin("move : ", move_nb);
	free(move_nb);
	if (text == NULL)
		return ;
	mlx_string_put(data->mlx, data->win, 4, 16, 0xFFFFFFFF, text);
	free(text);
}

static int	render_coins(t_data *data)
{
	char	*coins_nb;
	char	*max_coins_nb;
	char	*text;

	coins_nb = ft_itoa(data->player.coins);
	if (coins_nb == NULL)
		return (0);
	text = ft_strjoin("coins : ", coins_nb);
	free(coins_nb);
	if (text == NULL)
		return (0);
	coins_nb = ft_strjoin(text, "/");
	free(text);
	if (coins_nb == NULL)
		return (0);
	max_coins_nb = ft_itoa(data->player.max_coins);
	if (max_coins_nb == NULL)
		return (free(coins_nb), 0);
	text = ft_strjoin(coins_nb, max_coins_nb);
	free(coins_nb);
	free(max_coins_nb);
	if (text == NULL)
		return (0);
	mlx_string_put(data->mlx, data->win, 4, 28, 0xFFFFFFFF, text);
	return (free(text), 0);
}

void	clear_canvas_area(t_data *data)
{
	int	x;
	int	y;

	y = 7;
	while (y < 29)
	{
		x = 4;
		while (x < 124)
		{
			mlx_pixel_put(data->mlx, data->win, x, y, 0);
			x++;
		}
		y++;
	}
}
