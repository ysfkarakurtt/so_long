/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checkers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:20:00 by ykarakur          #+#    #+#             */
/*   Updated: 2024/04/03 12:20:04 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "so_long.h"
#include <stdlib.h>

void	wall_check(t_game *game, int x, int y)
{
	while (++y < game->map.map_height)
	{
		if (y == 0 || y == game->map.map_height - 1)
		{
			x = -1;
			while (++x < game->map.map_width)
				if (game->map.tile_map[y][x] != '1')
					error_free_map(game,
						"Error: The map must be surrounded by walls!\n");
		}
		if (game->map.tile_map[y][0] != '1'
			|| game->map.tile_map[y][game->map.map_width - 1] != '1')
			error_free_map(game,
				"Error: The map must be surrounded by walls!\n");
	}
}

static void	scan_tmp_map(t_game *game, int x, int y)
{
	if (game->map.tile_map[y][x] == 'P' || game->map.tile_map[y][x] == 'C')
		game->map.total_p_c++;
	if (game->map.tile_map[y][x + 1] != '1' && game->map.tmp_map[y][x + 1] != 1)
	{
		game->map.tmp_map[y][x + 1] = 1;
		scan_tmp_map(game, x + 1, y);
	}
	if (game->map.tile_map[y + 1][x] != '1' && game->map.tmp_map[y + 1][x] != 1)
	{
		game->map.tmp_map[y + 1][x] = 1;
		scan_tmp_map(game, x, y + 1);
	}
	if (game->map.tile_map[y - 1][x] != '1' && game->map.tmp_map[y - 1][x] != 1)
	{
		game->map.tmp_map[y - 1][x] = 1;
		scan_tmp_map(game, x, y - 1);
	}
	if (game->map.tile_map[y][x - 1] != '1' && game->map.tmp_map[y][x - 1] != 1)
	{
		game->map.tmp_map[y][x - 1] = 1;
		scan_tmp_map(game, x - 1, y);
	}
}

void	free_map(int **map, int y)
{
	while (y-- && map[y])
		free(map[y]);
	free(map);
}

void	create_tmp_map(t_game *game, int y)
{
	game->map.tmp_map = (int **)malloc(sizeof(int *) * game->map.map_width);
	if (!game->map.tmp_map)
		error_free_map (game, "Error: Failed to create tmp_map!\n");
	while (++y < game->map.map_height)
	{
		game->map.tmp_map[y] = ft_calloc(game->map.map_width, sizeof(int));
		if (!game->map.tmp_map[y])
		{
			free_map (game->map.tmp_map, y);
			error_free_map(game, "Error: Failed to create tmp_map!\n");
		}
	}
	scan_tmp_map(game, game->map.exit_x, game->map.exit_y);
	if (game->map.count_player
		+ game->map.count_collectible != game->map.total_p_c)
	{
		free_map(game->map.tmp_map, game->map.map_height);
		error_free_map(game,
			"Error: Player could not access all collectibles and exit!\n");
	}
	free_map(game->map.tmp_map, game->map.map_height);
}

void	item_check(t_game *game)
{
	if (game->map.count_collectible < 1)
		error_free_map(game,
			"Error: The map must contain at least 1 collectible!\n");
	if (game->map.count_exit != 1)
		error_free_map(game, "Error Message: The map must contain 1 exit!\n");
	if (game->map.count_player != 1)
		error_free_map(game, "Error: The map must contain 1 player!\n");
	if (game->map.excluded_item > 0)
		error_free_map(game,
			"Error: The map must contain only valid elements!\n");
}
