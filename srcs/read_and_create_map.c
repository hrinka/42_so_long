/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_check_maps.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:09:16 by takira            #+#    #+#             */
/*   Updated: 2022/11/26 19:09:18 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/so_long.h"

static int	create_map_arr(char *path, t_map_param *map)
{
	int		fd;
	char	*line;
	size_t	row;

	map->map_arr = (char **)malloc(sizeof(char *) * (map->size_x + 1));
	if (!map->map_arr)
		return (FAIL);
	fd = open(path, O_RDONLY);
	row = 0;
	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		map->map_arr[row] = line;
		row++;
	}
	map->map_arr[row] = NULL;
	free(line);
	close(fd);
	return (PASS);
}

static void	count_line_elems(const char *line, t_map_param *map)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == CHR_ITEM)
			map->cnt_item++;
		else if (line[i] == CHR_PLAYER)
		{
			map->cnt_start++;
			map->start_x = i;
		}
		else if (line[i] == CHR_GOAL)
			map->cnt_exit++;
		else if (line[i] != CHR_WALL && line[i] != CHR_EMPTY)
			map->cnt_others++;
		i++;
	}
	if (map->size_x == 0)
		map->size_x = i;
}

static int	read_mapfile_and_get_param(char *path, t_map_param *map)
{
	const int	fd = open(path, O_RDONLY);
	char		*line;

	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		count_line_elems(line, map);
		if (map->start_y == 0 && map->cnt_start)
			map->start_y = map->size_y;
		map->size_y++;
		free(line);
	}
	free(line);
	close(fd);
	if (errno == 0)
		return (PASS);
	free(path);
	return (FAIL);
}

static void	init_map_param(t_map_param *map)
{
	map->map_arr = NULL;
	map->cnt_item = 0;
	map->cnt_start = 0;
	map->cnt_exit = 0;
	map->cnt_others = 0;
	map->size_x = 0;
	map->size_y = 0;
	map->start_x = 0;
	map->start_y = 0;
}

void	read_and_valid_map(char *path, t_map_param *map)
{
	init_map_param(map);
	if (read_mapfile_and_get_param(path, map) == FAIL)
		error_exit("[Fail] Fail to read file.", NULL);
	if (map->cnt_start != 1 || map->cnt_exit != 1)
		error_exit("[Invalid map] Map must have 1 'P' and 'E'.", NULL);
	if (map->cnt_item == 0)
		error_exit("[Invalid map] Map must contain at least 1 'C'.", NULL);
	if (map->cnt_others >= 1)
		error_exit(\
		"[Invalid map] Map has to be constructed by '0', '1', 'C', 'E', 'P'.", \
		NULL);
	if (errno != 0 || create_map_arr(path, map) == FAIL)
	{
		free_map_arr(map, EXIT_FAILURE);
		error_exit("[Fail] Fail to create map arr.", NULL);
	}
	if (errno != 0 || valid_map(map) == FAIL)
	{
		free_map_arr(map, EXIT_FAILURE);
		error_exit(\
		"[Invalid map] Must be rectangular, closed by '1', have valid path.", \
		NULL);
	}
}
