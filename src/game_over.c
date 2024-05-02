/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:19:32 by ykarakur          #+#    #+#             */
/*   Updated: 2024/04/03 12:19:35 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include <stdlib.h>

void	error_free_map_2(t_game *game, char *err, int counter)
{
	int	y;

	y = -1;
	while (++y < counter)
		free(game->map.tile_map[y]);
	free(game->map.tile_map);
	display_error(err);
}

void	display_error(char *err)
{
	ft_printf("%s", err);
	exit(1);
}

void	error_free_map(t_game *game, char *err)
{
	int	y;

	y = -1;
	while (++y < game->map.map_height)
		free(game->map.tile_map[y]);
	free(game->map.tile_map);
	display_error(err);
}

void	success_exit_game(t_game *game, char *err)
{
	int	y;

	y = -1;
	while (++y < game->map.map_height)
		free(game->map.tile_map[y]);
	free(game->map.tile_map);
	mlx_destroy_image(game->mlx.mlx_ptr, game->img.player);
	mlx_destroy_image(game->mlx.mlx_ptr, game->img.collectible);
	mlx_destroy_image(game->mlx.mlx_ptr, game->img.exit);
	mlx_destroy_image(game->mlx.mlx_ptr, game->img.ground);
	mlx_destroy_image(game->mlx.mlx_ptr, game->img.wall);
	mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.window);
	display_error(err);
}
