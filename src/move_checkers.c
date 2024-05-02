/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_checkers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:20:34 by ykarakur          #+#    #+#             */
/*   Updated: 2024/04/03 12:20:38 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include "so_long.h"

int	move_and_check(int y, int x, t_game *game)
{
	if (game->map.tile_map[game->map.player_y + y][game->map.player_x
		+ x] == '1')
		return (0);
	else if (game->map.tile_map[game->map.player_y + y][game->map.player_x
		+ x] == 'C')
	{
		game->map.tile_map[game->map.player_y + y][game->map.player_x
			+ x] = '0';
		game->map.collected_cnt++;
	}
	else if (game->map.tile_map[game->map.player_y + y][game->map.player_x
		+ x] == 'E')
	{
		if (game->map.collected_cnt == game->map.count_collectible)
			success_exit_game(game, "You've successfully finished the game.\n");
	}
	return (1);
}

static void	move_and_put_image2(t_game *game)
{
	game->map.step_cnt++;
	ft_printf("Number of moves: %d\n", game->map.step_cnt);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window,
		game->img.exit, game->map.exit_x * IMG_SIZE, game->map.exit_y
		* IMG_SIZE);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window,
		game->img.player, game->map.player_x * IMG_SIZE, game->map.player_y
		* IMG_SIZE);
}

void	move_and_put_image(int key_code, t_game *game, int i)
{
	if (key_code == A || key_code == D)
	{
		if (move_and_check(0, i, game) == 0)
			return ;
		mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window,
			game->img.ground, game->map.player_x * IMG_SIZE, game->map.player_y
			* IMG_SIZE);
		game->map.player_x += i;
	}
	if (key_code == W || key_code == S)
	{
		if (move_and_check(-i, 0, game) == 0)
			return ;
		mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window,
			game->img.ground, game->map.player_x * IMG_SIZE, game->map.player_y
			* IMG_SIZE);
		game->map.player_y -= i;
	}
	move_and_put_image2(game);
}
