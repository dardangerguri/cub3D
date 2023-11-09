/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:02:23 by dgerguri          #+#    #+#             */
/*   Updated: 2023/11/09 15:23:18 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFF
#  define BUFF 42
# endif

/******************************************************************************/
/*								Includes  									  */
/******************************************************************************/

# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h> //read
# include <sys/uio.h> //read
# include <stdbool.h>
# include <math.h>

# include "../libft/includes/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define WIDTH_W 1490
# define HEIGHT_W 1080
# define SIZE_B 30 // Size of "block" (wall/empty etc..)?
# define SIZE_P 5 // Size of player?
# define PI 3.141592
# define RAD 0.0174533
# define PROJ_H 1080
# define PROJ_V 1490

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

// typedef struct s_player
// {
// 	int		r; // ray count
// 	int		mapx; // map x?
// 	int		mapy; // map y?
// 	int		mapp; // map position?
// 	int		dof; // depth of field
// 	float	rayx; // ray x
// 	float	rayy; // ray y
// 	float	raya; // ray angle
// 	float	xo; // x offset
// 	float	yo; // y offset
// 	float	playera; // player angle
// 	float	playerx; // player x
// 	float	playery; // player y
// }			t_player;

typedef struct s_ray
{
	float		angle;
	int			fov;
	float		raycast_angle;
	float		projection_width;
	float		projection_height;
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
	mlx_image_t		*north;
	mlx_image_t		*west;
	mlx_image_t		*east;
	mlx_image_t		*south;
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
	t_float_v	dir; // player direction vector (in radians)
	float		angle; // player viewangle in degrees
	char		**map;
	int			map_w;
	int			map_h;
	size_t		longest_line; //change name
	size_t		map_size;	//change name
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

/* error */
char		*print_error_message(char *message);
bool		error_message(char *message);

/* util.c */
char		**free_array(char **ret);
char		**duplicate_map(char **map);

/* cleanup */
void		cleanup(t_map_data *data);

/*---------------------------------Init---------------------------------------*/

/* data_init */
bool		data_init(t_map_data *data, char *map);

/* read_map */
bool		read_map(t_map_data *data, char *file);

/* split_line */
char		**ft_split_line(char const *s);

/* mlx_init */
bool	init_mlx(t_map_data *data);

/*---------------------------------Parsing------------------------------------*/

/* split_elements_map */
char		*parse_file(t_map_data *data);
char		*save_the_elements(t_map_data *data, int i, int j, bool *error);

/* validate_elements */
bool		validate_elements(t_map_data *data);

/* parse_colors */
void		parse_colors(t_map_data *data, int i, int j, bool *error);

/* validate_map */
bool		validate_map(t_map_data *data);

/* validate_map_utils */
t_vector	find_empty_space(char **map);
t_vector	get_last_point(char **map);
void		remove_newline(char **map);
bool		map_filled(char **map);
bool		find_wall(char **map, t_vector pos);

/*---------------------------------Raycasting---------------------------------*/

/* raycasting */
void		raycasting(void *ptr);

/* moving */
void		moving(void *ptr);

/* 3d drawing */
void	draw_view(t_map_data *data, t_ray *ray, int x);
void	draw_walls(t_map_data *data, int x, t_ray *ray, int dir);
unsigned int	get_pixel(t_mlx_data *mlx, int x, int y, int dir);

/* raycasting_utils */
float	fix_angle(float angle);
float	deg_to_rad(float degrees);
float	get_dist(t_float_v *player, t_float_v *wall_hit);
int		get_rgba(int r, int g, int b, int a);

/* TEMPORARY IN MAIN */
void		print_struct(t_map_data *data);

/* TEMPORARY IN MAIN */
void	draw_map(t_map_data *data);
void	draw_player(t_map_data *data);
void	draw_nose(t_map_data *data);

#endif
