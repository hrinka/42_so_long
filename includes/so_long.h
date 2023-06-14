/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:03:25 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/15 01:03:26 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include "./../minilibx-linux/mlx.h"
# include "./../lib/libft/libft.h"
# include "./../lib/libftprintf/ft_printf.h"
# include "./../lib/gnl/get_next_line.h"

# define IMG_PLAYER_R	"./assets/img/player32_r.xpm"
# define IMG_PLAYER_L	"./assets/img/player32_l.xpm"
# define IMG_GOAL		"./assets/img/goal.xpm"
# define IMG_WALL		"./assets/img/wall.xpm"
# define IMG_ITEM		"./assets/img/item.xpm"
# define IMG_EMPTY		"./assets/img/field.xpm"

# define EVENT_KEY_PRESS	2
# define EVENT_DESTROY		33

# define KEY_ESC	0xff1b
# define KEY_LEFT	0xff51
# define KEY_UP		0xff52
# define KEY_RIGHT	0xff53
# define KEY_DOWN	0xff54

# define CHR_WALL	'1'
# define CHR_EMPTY	'0'
# define CHR_ITEM	'C'
# define CHR_PLAYER	'P'
# define CHR_GOAL	'E'

# define PASS		1
# define FAIL		0
# define FINISH		2

# define MAP_MIN	2
# define MAP_MAX	66

# define IMAGE_SIZE 32

# define SPACES		"\t\n\v\f\r "
# define FILE_EXTENSION	".ber"

typedef struct s_player
{
	size_t	pos_x;
	size_t	pos_y;
	int		next_x;
	int		next_y;
	size_t	cnt_step;
	size_t	cnt_item;
	bool	can_exit;
	bool	is_facing_right;
	bool	flg_get_item;
}			t_player;

typedef struct s_map_param
{
	char	**map_arr;
	size_t	cnt_item;
	size_t	cnt_start;
	size_t	cnt_exit;
	size_t	cnt_others;
	size_t	size_x;
	size_t	size_y;
	size_t	start_x;
	size_t	start_y;
}			t_map_param;

typedef struct s_img
{
	void	*player_right;
	void	*player_left;
	void	*goal;
	void	*wall;
	void	*item;
	void	*empty;
}			t_img;

typedef struct s_mlx_vars
{
	void		*mlx;
	void		*win;
	t_player	*player;
	t_map_param	*map;
	t_img		*img;
	bool		is_game_end;
}				t_mlx_vars;

typedef struct s_queue
{
	int				x;
	int				y;
	struct s_queue	*next;
}					t_queue;

// read and create map
void	read_and_valid_map(char *path, t_map_param *map);

// map valid
int		valid_map(t_map_param *map);

// bfs
void	bfs(int **visited, t_map_param map);

// create grid for bfs
int		**create_visited(char **map_arr, size_t y, size_t x);
void	free_grid(int **grid, size_t y);

// get img
void	*get_player_img(t_mlx_vars mlx);
void	*get_img_ptr(t_mlx_vars *mlx, size_t y, size_t x);
int		null_check_for_map_img(t_img *img);

// create game screen
int		draw_game_screen(t_mlx_vars *mlx);
void	move_and_judge_finish(t_mlx_vars *mlx, int dy, int dx);
int		check_to_can_move_next_pos(t_mlx_vars *mlx, int dy, int dx);

// mlx keyhooks
void	mlx_key_hooks(t_mlx_vars *mlx);

// mlx utils
void	*xpm_to_img_ptr(t_mlx_vars mlx, char *filepath);
void	put_img(t_mlx_vars *mlx, void *img, size_t y, size_t x);
int		close_window(t_mlx_vars *mlx);
int		destroy_mlx_and_map(t_mlx_vars *mlx);
char	*valid_map_path_name(char *argv);

// sl utils
void	print_step_to_stdout(t_mlx_vars *mlx);
int		free_map_arr(t_map_param *map, int ret_val);
int		err_exit(char *msg, t_mlx_vars *mlx);
//void	print_map(t_map_param map, char *str);
//void	print_bfs(int **grid, t_map_param map, char *str);

#endif
