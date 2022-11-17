/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:40:36 by lbrianna          #+#    #+#             */
/*   Updated: 2022/10/19 15:25:41 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>

# define WIN_WIDTH 1024
# define WIN_HEIGHT  768
# define BUFFER_SIZE 42

# define NEW_LINE '\n'
# define SPACE ' '

# define PLANE 0.66
# define ESC 	53
# define W		13
# define S 	1
# define D	2
# define A 	0
# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125
# define STEP	0.2

# define FOV 		1.0471975512
# define ROT_STEP	0.0924291465
# define SCALE_FOR_MP 8

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;
//

typedef struct s_map
{
	char	**map;
	char	side;
	int		width;
	int		height;
	int		coord_x;
	int		coord_y;
}	t_map;
// Основа для парсера
typedef struct s_info
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	t_map	*map;
	t_color	*floor;
	t_color	*ceiling;
}	t_info;

typedef struct s_intcoord
{
	int		x;
	int		y;
}	t_intcoord;

typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct s_texture
{
	void	*img;
	int		bpp;
	int		size_line;
	int		endian;
	char	*addr;
	int		width;
	int		height;
	void	*mlx;
}	t_texture;

typedef struct s_ray
{
	int		pix;
	int		map_x;
	int		map_y;
	double	camera_x;

	double	dir_x;
	double	dir_y;

	double	delta_dist_x;
	double	delta_dist_y;
}	t_ray;

typedef struct s_game
{
	unsigned int	floor;
	unsigned int	ceiling;
	char			**map;
	void			*mlx;
	void			*win;
	t_coord			player;
	double			player_dir;
	t_texture		*texture;
	t_info			*info;
	int				step_x;
	int				step_y;
	int				x_cur;
	int				y_cur;
	double			dist;
	double			player_start;
	char			side;
}	t_game;

int				main(int argc, char **argv);
int				do_exit(t_game *game);
void			init_map(t_map *map);
void			init_player(t_map *map);
t_info			*init_data(void);
void			parser(char **argv, t_info *data);
int				return_error(char *str, int code);
int				check_extension(char *str);
char			*read_map(int fd);
void			make_data(t_info *data, char *str);
int				get_width(char *line);
int				process_colors(char *str, t_info *data);
int				process_texture(char *str, t_info *data);
t_map			*data_to_map(char *str);
void			define_color(char *str, t_info *data);
int				get_color(char *str);
int				get_floor_ceil(char *str);
void			check_color(t_color *color);
void			define_side_path(t_info *data, char *str);
void			check_path(char *path);
int				get_side(char *str);
char			*get_substr(char *str);
int				find_id(char *str, char symb);
void			check_map(t_map *map);
void			check_map_2(char **arr, int i, int j);
char			**make_map(char *str, int h, int w, int i);
int				get_height(char *line);
void			func_norme(int j, int w, char *line);
t_game			*init_game(t_info *data);
void			process_map(t_map *map, t_game *game);
void			init_colors(t_info *data, t_game *game);
void			init_mlx(t_info *data, t_game *game);
void			make_texture(t_info *data, t_game *game);
void			get_data_addr(t_texture *txr);
void			convert_xpm(t_texture *txr, char *path, void *mlx);
int				key_hook(int key, t_game *game);
unsigned int	ft_color_define(t_color *color);
int				ray_cast(t_game *game);
void			ft_draw_celling_and_floor(t_game *game);
void			draw_mini_map(t_game *game);
int				ray(t_game *game);
void			draw_line(t_game *game, t_ray *ray, int x);
void			my_mlx_pixel_put(t_texture *data, int x, int y, int color);
void			choose_image(int *image, t_texture *tex,
					t_game *game, t_ray *ray);
int				get_the_y(t_game *game, double h, int y, int start);
void			free_game(t_game *game);
void			free_data(t_info *data);

#endif
