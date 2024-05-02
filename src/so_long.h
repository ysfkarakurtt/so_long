/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:20:43 by ykarakur          #+#    #+#             */
/*   Updated: 2024/04/03 17:42:38 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define ON_KEYDOWN 2
# define ON_DESTROY 17
# define IMG_SIZE 64
# define W 13
# define A 0
# define S 1
# define D 2
# define ESC 53

typedef struct s_img
{
	void			*player;
	void			*exit;
	void			*collectible;
	void			*ground;
	void			*wall;

	int				height;
	int				width;

}					t_img;

typedef struct s_paths
{
	char			*map_path;
	char			*player_path;
	char			*collectible_path;
	char			*exit_path;
	char			*ground_path;
	char			*wall_path;

}					t_paths;

typedef struct s_map
{
	int				map_width;
	int				map_height;
	char			**tile_map;
	int				**tmp_map;

	int				player_x;
	int				player_y;
	int				exit_x;
	int				exit_y;

	int				count_player;
	int				count_collectible;
	int				count_exit;
	int				excluded_item;
	int				total_p_c;
	int				collected_cnt;
	int				step_cnt;

}					t_map;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*window;
}					t_mlx;

typedef struct s_game
{
	t_paths		paths;
	t_mlx		mlx;
	t_img		img;
	t_map		map;
}					t_game;

void				format_checker(char **av);
void				object_xpm_checker(t_game *game);
void				scene_xpm_checker(t_game *game);
void				scene_controller(char **av, t_game *game);
void				display_error(char *err);
void				success_exit_game(t_game *game, char *err);
void				error_free_map(t_game *game, char *err);
void				item_check(t_game *game);
void				wall_check(t_game *game, int x, int y);
void				create_tmp_map(t_game *game, int y);
void				free_map(int **map, int y);
void				move_and_put_image(int key_code, t_game *game, int i);
void				create_minilibx(t_game *game);
void				ft_key_comb(t_game *game);
void				error_free_map_2(t_game *game, char *err, int counter);

#endif
