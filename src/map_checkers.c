/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:20:10 by ykarakur          #+#    #+#             */
/*   Updated: 2024/04/03 12:20:14 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "so_long.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	rectangle_check(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		display_error("Error: Line could not be created in get_next_line.\n");
	game->map.map_width = (int)ft_strlen(line) - 1;
	game->map.map_height = 0;
	while (line != NULL)
	{
		game->map.map_height++;
		if (game->map.map_width != (int)ft_strlen(line) - 1)
		{
			free(line);
			close(fd);
			display_error("The map must be rectangular\n");
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	new_map(t_game *game, int x, int y)
{
	int		fd;
	char	*line;

	fd = open(game->paths.map_path, O_RDONLY);
	if (fd < 0)
		display_error("Error: Unable to open file for map path.\n");
	game->map.tile_map = (char **)malloc(sizeof(char *)
			* game->map.map_height);
	if (!game->map.tile_map)
		display_error("Error: Failed to allocate memory for tile map\n");
	while (++y < game->map.map_height)
	{
		line = get_next_line(fd);
		if (!line)
			error_free_map_2(game, "Error: Failed to create tile map!\n", y);
		game->map.tile_map[y] = (char *)malloc(sizeof(char)
				* game->map.map_width);
		if (!game->map.tile_map[y])
			error_free_map_2(game, "Error: Failed to create tile map!\n", y);
		x = -1;
		while (++x < game->map.map_width)
			game->map.tile_map[y][x] = line[x];
		game->map.tile_map[y][x] = '\0';
		free(line);
	}
}

void	set_defaults(t_game *game)
{
	game->map.count_player = 0;
	game->map.count_collectible = 0;
	game->map.count_exit = 0;
	game->map.excluded_item = 0;
	game->map.total_p_c = 0;
	game->map.collected_cnt = 0;
	game->map.step_cnt = 0;
}

void	count_item(t_game *game, int x, int y)
{
	while (++y < game->map.map_height)
	{
		x = -1;
		while (++x < game->map.map_width)
		{
			if (game->map.tile_map[y][x] == 'C')
				game->map.count_collectible++;
			else if (game->map.tile_map[y][x] == 'P')
			{
				game->map.count_player++;
				game->map.player_x = x;
				game->map.player_y = y;
			}
			else if (game->map.tile_map[y][x] == 'E')
			{
				game->map.count_exit++;
				game->map.exit_x = x;
				game->map.exit_y = y;
			}
			else if (game->map.tile_map[y][x] != '0' &&
				game->map.tile_map[y][x] != '1')
				game->map.excluded_item++;
		}
	}
}

void	scene_controller(char **av, t_game *game)
{
	int	x;
	int	y;
	int	fd;

	x = -1;
	y = -1;
	game->paths.map_path = av[1];
	fd = open(game->paths.map_path, O_RDONLY);
	if (fd < 0)
		display_error("Error: Unable to open file for map path.\n");
	rectangle_check(game, fd);
	new_map(game, x, y);
	set_defaults(game);
	count_item(game, x, y);
	item_check(game);
	wall_check(game, x, y);
	create_tmp_map(game, y);
}
