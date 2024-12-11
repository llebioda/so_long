/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:50:48 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/10 13:21:52 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <time.h>

# define WIN_WIDTH 960
# define WIN_HEIGHT 704
# define TILE_SIZE 64
# define SPRITE_RATE 8			// Sprite animation speed
# define ENEMY_MOVE_TIME 1.0	// Each X seconds all the enemies move

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_itoa(int nb);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
int			ft_file_as_extension(const char *filepath, const char *ext);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			clamp(int v, int min, int max);

typedef enum e_game_state
{
	PLAYING,
	WON,
	LOSE
}	t_game_state;

typedef struct s_vector2
{
	int	x;
	int	y;
}	t_vector2;

typedef struct s_map
{
	char		**data;
	int			width;
	int			height;
	int			total_width;
	int			total_height;
	t_vector2	exit;
	int			enemy_count;
}	t_map;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		sprite_count;
	int		sprite_height;
	int		bpp;
	int		line_size;
	int		endian;
}	t_img;

typedef struct s_sprites
{
	t_img	wall;
	t_img	background;
	t_img	coins;
	t_img	player_left;
	t_img	player_right;
	t_img	opened_exit;
	t_img	closed_exit;
	t_img	enemy;
}	t_sprites;

typedef struct s_player
{
	int				x;
	int				y;
	t_vector2		spawn;
	int				direction;
	int				coins;
	int				max_coins;
	unsigned int	move_count;
}	t_player;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_map			map;
	t_sprites		sprites;
	t_player		player;
	t_vector2		cam;
	unsigned int	sprite_frame;
	t_game_state	game_state;
}	t_data;

int			close_window(t_data *data);
void		exit_error(char *error);
void		close_gnl(int fd);
void		free_data(t_data *data);

int			load_map(char *map_path, t_data *data);
void		free_map(t_map *map);
void		map_error(t_map *map, int fd, char *error);
void		reload_map(t_map *map);
t_vector2	get_neighbour_cell(t_vector2 current, int i);

void		free_img(void *mlx, t_img *img);
int			load_sprites(t_data *data);
void		mlx_blit_img(t_data *data, t_img *img, int x, int y);
void		blit_img_centered(t_data *data, t_img *img, int x, int y);

int			render(t_data *data, int all);
void		render_at(t_data *data, int x, int y);

void		update_cam(t_data *data, int reset_render);
void		check_horizontal_collision(t_data *data, int move);
void		check_vertical_collision(t_data *data, int move);
void		render_player(t_data *data);

void		update_enemies(t_data *data);

#endif
