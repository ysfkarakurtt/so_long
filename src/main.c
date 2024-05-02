/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:19:51 by ykarakur          #+#    #+#             */
/*   Updated: 2024/04/03 12:19:54 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../minilibx/mlx.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		display_error("Error: Program requires two arguments.\n");
	format_checker(av);
	object_xpm_checker(&game);
	scene_xpm_checker(&game);
	scene_controller(av, &game);
	create_minilibx(&game);
	ft_key_comb(&game);
	mlx_loop(game.mlx.mlx_ptr);
}
