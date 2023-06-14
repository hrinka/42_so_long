/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:02:44 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/15 01:02:45 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "./includes/so_long_bonus.h"

int	draw_game_screen_b(t_mlx_vars *mlx)
{
	int		y;
	int		x;
	void	*img_ptr;

	y = 0;
	while (y < mlx->map->size_y)
	{
		x = 0;
		while (x < mlx->map->size_x)
		{
			img_ptr = get_img_ptr_b(mlx, y, x);
			if (!img_ptr)
				return (FAIL);
			put_img_b(mlx, img_ptr, y, x);
			x++;
		}
		y++;
	}
	if (!mlx->is_game_end && !mlx->is_game_over)
		draw_top_screen_info(mlx);
	return (PASS);
}

int	check_to_can_move_next_pos_b(t_mlx_vars *mlx, int dy, int dx)
{
	const int	next_y = (int)mlx->player->pos_y + dy;
	const int	next_x = (int)mlx->player->pos_x + dx;
	char		next_pos;

	if (mlx->is_game_end || mlx->is_game_over)
		return (FAIL);
	if (next_y < 0 || mlx->map->size_y < next_y)
		return (FAIL);
	if (next_x < 0 || mlx->map->size_x < next_x)
		return (FAIL);
	if (mlx->map->map_arr[next_y][next_x] == CHR_WALL)
		return (FAIL);
	if (mlx->map->map_arr[next_y][next_x] == CHR_GOAL && !mlx->player->can_exit)
		return (FAIL);
	next_pos = mlx->map->map_arr[mlx->player->next_y][mlx->player->next_x];
	if (next_pos == CHR_GOAL && !mlx->player->can_exit)
		return (FAIL);
	return (PASS);
}

static void	redraw_player_b(t_mlx_vars *mlx)
{
	const int	pos_x = (int)mlx->player->pos_x;
	const int	pos_y = (int)mlx->player->pos_y;
	const int	next_x = (int)mlx->player->next_x;
	const int	next_y = (int)mlx->player->next_y;

	if (pos_x < next_x)
		mlx->player->is_player_facing_r = true;
	else if (pos_x > next_x)
		mlx->player->is_player_facing_r = false;
	put_img_b(mlx, get_player_img_b(*mlx), next_y, next_x);
	put_img_b(mlx, get_empty_img_b(*mlx, pos_y, pos_x), pos_y, pos_x);
	mlx->map->map_arr[next_y][next_x] = CHR_PLAYER;
	mlx->map->map_arr[pos_y][pos_x] = CHR_EMPTY;
	mlx->player->pos_x = next_x;
	mlx->player->pos_y = next_y;
}

void	player_move_and_check_fin(t_mlx_vars *mlx, int dy, int dx)
{
	char	next_pos;

	if (check_to_can_move_next_pos_b(mlx, dy, dx) == FAIL)
		return ;
	mlx->player->cnt_step++;
	mlx->player->next_y = (int)mlx->player->pos_y + dy;
	mlx->player->next_x = (int)mlx->player->pos_x + dx;
	next_pos = mlx->map->map_arr[mlx->player->next_y][mlx->player->next_x];
	if (mlx->player->cnt_step >= INT_MAX)
		err_exit_b("Step counter reach the upper limit.", mlx);
	if (next_pos == CHR_GOAL && mlx->player->can_exit)
		mlx->is_game_end = true;
	if (next_pos == CHR_ENEMY)
		mlx->is_game_over = true;
	if (next_pos == CHR_ITEM)
	{
		mlx->player->cnt_item++;
		mlx->player->flg_get_item = true;
		if (mlx->player->cnt_item == mlx->map->cnt_item)
			mlx->player->can_exit = true;
	}
	redraw_player_b(mlx);
	draw_top_screen_info(mlx);
	print_step_to_stdout_b(mlx);
}
