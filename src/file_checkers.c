/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checkers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:19:21 by ykarakur          #+#    #+#             */
/*   Updated: 2024/04/03 12:19:25 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "so_long.h"
#include <fcntl.h>
#include <unistd.h>

void	format_checker(char **av)
{
	int	i;

	i = (int)ft_strlen(av[1]);
	if (av[1][i - 1] != 'r' || av[1][i - 2] != 'e' || av[1][i - 3] != 'b'
		|| av[1][i - 4] != '.')
		display_error("Error: Format must be *.ber.\n");
}

void	object_xpm_checker(t_game *game)
{
	int	fd;

	fd = open("./sprites/player.xpm", O_RDONLY);
	if (fd < 0)
		display_error("Error: Unable to open xpm file for player.\n");
	close(fd);
	fd = open("./sprites/collectible.xpm", O_RDONLY);
	if (fd < 0)
		display_error("Error: Unable to open xpm file for collectible.\n");
	close(fd);
	fd = open("./sprites/exit.xpm", O_RDONLY);
	if (fd < 0)
		display_error("Error: Unable to open xpm file for exit.\n");
	close(fd);
	game->paths.player_path = "./sprites/player.xpm";
	game->paths.collectible_path = "./sprites/collectible.xpm";
	game->paths.exit_path = "./sprites/exit.xpm";
}

void	scene_xpm_checker(t_game *game)
{
	int	fd;

	fd = open("./sprites/ground.xpm", O_RDONLY);
	if (fd < 0)
		display_error("Error: Unable to open xpm file for ground.\n");
	close(fd);
	fd = open("./sprites/wall.xpm", O_RDONLY);
	if (fd < 0)
		display_error("Error: Unable to open xpm file for wall.\n");
	close(fd);
	game->paths.ground_path = "./sprites/ground.xpm";
	game->paths.wall_path = "./sprites/wall.xpm";
}
