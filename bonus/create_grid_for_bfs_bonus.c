/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_grid_for_bfs_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:01:33 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/15 01:01:33 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "./includes/so_long_bonus.h"

static int	**create_grid_b(size_t y, size_t x)
{
	int		**grid;
	size_t	i;

	grid = (int **)ft_calloc(y, sizeof(int *));
	if (!grid)
		return (FAIL);
	i = 0;
	while (i < y)
	{
		grid[i] = (int *)ft_calloc(x, sizeof(int));
		if (!grid[i])
		{
			free_grid_b(grid, y);
			return (NULL);
		}
		i++;
	}
	return (grid);
}

int	**create_bfs_grid_b(char **map_arr, size_t y, size_t x, bool for_enemy)
{
	int		**bfs_grid;
	size_t	i;
	size_t	j;

	bfs_grid = create_grid_b(y, x);
	if (!bfs_grid)
		return (NULL);
	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			if (map_arr[i][j] == CHR_WALL || map_arr[i][j] == CHR_GOAL)
				bfs_grid[i][j] = -1;
			if (for_enemy)
				if (map_arr[i][j] == CHR_ITEM)
					bfs_grid[i][j] = -1;
			j++;
		}
		i++;
	}
	return (bfs_grid);
}
