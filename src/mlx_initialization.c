/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:20:19 by ykarakur          #+#    #+#             */
/*   Updated: 2024/04/03 12:20:29 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "so_long.h"
#include <stdio.h>

static void	start_mlx_2(t_game *game)
{
	if (!game->img.exit)
	{
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.player);
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.collectible);
		error_free_map(game, "Error:Exit image could not be created!\n");
	}
	game->img.wall = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			game->paths.wall_path, &game->img.width, &game->img.height);
	if (!game->img.wall)
	{
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.exit);
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.player);
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.collectible);
		error_free_map(game, "Error:Wall image could not be created!\n");
	}
	game->img.ground = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			game->paths.ground_path, &game->img.width, &game->img.height);
	if (!game->img.ground)
	{
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.wall);
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.exit);
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.player);
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.collectible);
		error_free_map(game, "Error:Ground image could not be created!\n");
	}
}

void	start_mlx(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (game->mlx.mlx_ptr == NULL)
		error_free_map(game, "Error: Minilibx could not be created!\n");
	game->mlx.window = mlx_new_window(game->mlx.mlx_ptr, game->map.map_width
			* IMG_SIZE, game->map.map_height * IMG_SIZE, "so_long");
	if (game->mlx.window == NULL)
		error_free_map(game, "Error: Window could not be created!\n");
	game->img.collectible = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			game->paths.collectible_path, &game->img.height, &game->img.width);
	if (!game->img.collectible)
		error_free_map(game,
			"Error: Collectible image could not be created!\n");
	game->img.player = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			game->paths.player_path, &game->img.width, &game->img.height);
	if (!game->img.player)
	{
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.collectible);
		error_free_map(game, "Error: Player image could not be created!\n");
	}
	game->img.exit = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			game->paths.exit_path, &game->img.width, &game->img.height);
	start_mlx_2(game);
}

static void	put_img_to_map_mlx_1(t_game *game, int x, int y)
{
	if (game->map.tile_map[y][x] == 'C')
		mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window,
			game->img.collectible, x * IMG_SIZE, y * IMG_SIZE);
	else if (game->map.tile_map[y][x] == 'E')
		mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window,
			game->img.exit, x * IMG_SIZE, y * IMG_SIZE);
	else if (game->map.tile_map[y][x] == 'P')
		mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window,
			game->img.player, x * IMG_SIZE, y * IMG_SIZE);
	else if (game->map.tile_map[y][x] == '1')
		mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window,
			game->img.wall, x * IMG_SIZE, y * IMG_SIZE);
}

void	put_img_to_map_mlx_0(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.map_height)
	{
		x = 0;
		while (x < game->map.map_width)
		{
			mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window,
				game->img.ground, x * IMG_SIZE, y * IMG_SIZE);
			put_img_to_map_mlx_1(game, x, y);
			x++;
		}
		y++;
	}
}

void	create_minilibx(t_game *game)
{
	start_mlx(game);
	put_img_to_map_mlx_0(game);
}
