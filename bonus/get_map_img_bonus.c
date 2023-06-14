/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_img_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:02:03 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/15 01:02:03 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "./includes/so_long_bonus.h"

void	*get_player_img_b(t_mlx_vars mlx)
{
	if (mlx.player->is_player_facing_r)
		return (mlx.img->players[0]);
	return (mlx.img->players[0 + CNT_PLAYER_FLM]);
}

void	*get_enemy_img_b(t_mlx_vars mlx, size_t flame, bool right)
{
	flame %= CNT_ENEMY_FLM;
	if (right)
		return (mlx.img->enemies[flame]);
	return (mlx.img->enemies[flame + CNT_ENEMY_FLM]);
}

void	*get_empty_img_b(t_mlx_vars mlx, size_t y, size_t x)
{
	if ((y + x) % 2 == 0)
		return (mlx.img->empties[0]);
	else if ((y + x) % 7 == 0)
		return (mlx.img->empties[2]);
	else if ((y + x) % 3 == 0)
		return (mlx.img->empties[3]);
	return (mlx.img->empties[1]);
}

void	*get_item_img_b(t_mlx_vars mlx, size_t y, size_t x)
{
	return (mlx.img->items[(y + x) % CNT_ITEM]);
}

void	*get_img_ptr_b(t_mlx_vars *mlx, size_t y, size_t x)
{
	if (mlx->map->map_arr[y][x] == CHR_WALL)
		return (mlx->img->wall);
	if (mlx->map->map_arr[y][x] == CHR_EMPTY)
		return (get_empty_img_b(*mlx, y, x));
	if (mlx->map->map_arr[y][x] == CHR_ITEM)
		return (get_item_img_b(*mlx, y, x));
	if (mlx->map->map_arr[y][x] == CHR_PLAYER)
		return (get_player_img_b(*mlx));
	if (mlx->map->map_arr[y][x] == CHR_GOAL)
		return (mlx->img->goal);
	if (mlx->map->map_arr[y][x] == CHR_ENEMY)
		return (get_enemy_img_b(*mlx, true, 0));
	return (NULL);
}
