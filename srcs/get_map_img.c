/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:00:29 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/23 15:21:39 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/so_long.h"

void	*get_player_img(t_mlx_vars mlx)
{
	if (mlx.player->is_facing_right)
		return (mlx.img->player_right);
	return (mlx.img->player_left);
}

void	*get_img_ptr(t_mlx_vars *mlx, size_t y, size_t x)
{
	if (mlx->map->map_arr[y][x] == CHR_WALL)
		return (mlx->img->wall);
	if (mlx->map->map_arr[y][x] == CHR_EMPTY)
		return (mlx->img->empty);
	if (mlx->map->map_arr[y][x] == CHR_ITEM)
		return (mlx->img->item);
	if (mlx->map->map_arr[y][x] == CHR_PLAYER)
		return (get_player_img(*mlx));
	if (mlx->map->map_arr[y][x] == CHR_GOAL)
		return (mlx->img->goal);
	return (NULL);
}

int	null_check_for_map_img(t_img *img)
{
	if (!img->player_right || !img->player_left)
		return (FAIL);
	if (!img->goal || !img->wall || !img->empty || !img->item)
		return (FAIL);
	return (PASS);
}
