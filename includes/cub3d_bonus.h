/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:02:23 by dgerguri          #+#    #+#             */
/*   Updated: 2025/01/13 14:55:50 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# ifndef BUFF
#  define BUFF 42
# endif

/******************************************************************************/
/*								Includes  									  */
/******************************************************************************/

# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdbool.h>
# include <math.h>

# include "../libft/includes/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

/******************************************************************************/
/*								    Defines    	 							  */
/******************************************************************************/

# define WIDTH_W 1920
# define HEIGHT_W 1080
# define SIZE_B 256
# define SIZE_P 5
# define PI 3.141592
# define RAD 0.0174533
# define SPEED 10

/******************************************************************************/
/*								Error Messages	 							  */
/******************************************************************************/

# define X_VALID_ARGUMENTS "Error: Invalid number of arguments!\n"
# define X_VALID_FILE "Error: The map is not a .cub file!\n"
# define X_OPEN_FILE "Error: Couldn't open the file!\n"
# define X_READ_FILE "Error: Couldn't read the file!\n"
# define X_MALLOC "Error: Malloc allocation has failed!\n"
# define X_UNKNOWN_ELEMENT "Error: Unknown element on the file!\n"
# define X_UNKNOWN_ELEMENT_MAP "Error: Unknown element on the map!\n"
# define X_MULTIPLE_S_POINTS "Error: More than 1 starting point!\n"
# define X_S_P_MISSING "Error: Starting point is missing!\n"
# define X_MISSING_TEXTURE "Error: Texture file is missing!\n"
# define X_MISSING_COLOR "Error: Color is missing!\n"
# define X_WRONG_TEXTURE_FILE "Error: Wrong texture file!\n"
# define X_WRONG_COLOR_VALUE "Error: Wrong color value!\n"
# define X_EMPTY_LINES "Error: Map has empty lines!\n"
# define X_MAP_NOT_CLOSED "Error: Map not closed with walls!\n"
# define X_MLX "Error: MLX has failed!\n"
# define X_MAP_TOO_BIG "Error: Map too big\n"

/******************************************************************************/
/*								Structs 									  */
/******************************************************************************/

typedef struct s_vector
{
	int		x;
	int		y;
}	t_vector;

typedef struct s_float_v
{
	float	x;
	float	y;
}	t_float_v;

typedef struct s_ray
{
	float		angle;
	int			fov;
	float		raycast_angle;
	t_float_v	center;
	float		cotan;
	float		tan;
	t_float_v	h_map;
	t_float_v	h_grid;
	t_float_v	v_map;
	t_float_v	v_grid;
	float		distance;
	char		shortest;
	t_float_v	vd;
	t_float_v	hd;
}				t_ray;

typedef struct s_mlx_data
{
	mlx_t			*mlx;
	mlx_image_t		*window;
	mlx_texture_t	*north;
	mlx_texture_t	*west;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	uint32_t		floor;
	uint32_t		ceiling;
}				t_mlx_data;

typedef struct s_map_data
{
	char		**file_splitted;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	int			*floor;
	int			*ceiling;
	t_float_v	pos;
	t_float_v	dir;
	float		angle;
	char		**map;
	char		**map_c;
	int			map_w;
	int			map_h;
	t_mlx_data	*mlx_data;
}				t_map_data;

enum	e_directions
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

/******************************************************************************/
/*								Functions									  */
/******************************************************************************/

/* utils_bonus*/
char		**free_array(char **ret);
char		**duplicate_map(char **map);
int			get_rgba(int r, int g, int b, int a);
int			remove_whitespace(char *str);
void		get_map_size(t_map_data *data);

/* error_bonus*/
char		*print_error_message(char *message);
bool		error_message(char *message);

/* cleanup_bonus*/
void		cleanup(t_map_data *data);

/*---------------------------------Init---------------------------------------*/

/* data_init_bonus */
bool		data_init(t_map_data *data, char *map);

/* read_map_bonus */
bool		read_map(t_map_data *data, char *file);

/* split_line_bonus */
char		**ft_split_line(char const *s);

/* mlx_init_bonus */
bool		init_mlx(t_map_data *data);

/*---------------------------------Parsing------------------------------------*/

/* split_elements_map_bonus */
char		*parse_file(t_map_data *data);
char		*save_the_elements(t_map_data *data, int i, int j, bool *error);

/* validate_elements_bonus */
bool		validate_elements(t_map_data *data);

/* parse_colors_bonus */
void		parse_colors(t_map_data *data, int i, int j, bool *error);

/* validate_map_bonus */
bool		validate_map(t_map_data *data);

/* validate_map_utils_bonus */
t_vector	find_empty_space(char **map);
t_vector	get_last_point(char **map);
void		remove_newline(char **map);
bool		map_filled(char **map);
bool		find_wall(char **map, t_vector pos);

/* starting_position_bonus */
void		starting_point(t_map_data *d, t_vector pos, bool *p_start, char c);

/*---------------------------------Raycasting---------------------------------*/

/* raycasting_bonus */
void		raycasting(void *ptr);

/* raycasting2_bonus */
void		get_shortest(t_map_data *data, t_ray *ray);
void		check_hit_wall(t_map_data *data, t_float_v *grid, t_float_v *map,
				t_float_v *offset);
void		draw_floor_ceiling(t_map_data *data);

/* raycasting_utils_bonus */
float		fix_angle(float angle);
float		deg_to_rad(float degrees);
float		get_dist(t_float_v *player, t_float_v *wall_hit);
uint32_t	get_pixel_color(mlx_texture_t *img, uint32_t x, uint32_t y);
uint32_t	get_pixel(t_mlx_data *mlx, int x, int y, int dir);

/* pad_map_bonus */
bool		pad_map(t_map_data *data);

/* moving_bonus */
void		moving(void *ptr);

/* moving_utils_bonus */
void		turn_player(t_map_data *data, int keycode);
void		lookat(t_map_data *data, int dir);
bool		check_validity(t_map_data *data, float x, float y);

/* 3d drawing_bonus */
void		draw_view(t_map_data *data, t_ray *ray, int x);
void		draw_walls(t_map_data *data, int x, t_ray *ray, int dir);

/* 2d_drawing_bonus */
void		draw_minimap(t_map_data *data);

/* 2d_drawing2_bonus */
void		draw_map_small(t_map_data *data, int x, int y);
void		draw_map_big(t_map_data *data, int row, int column, int x);

#endif
