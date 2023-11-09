/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:10:33 by dardangergu       #+#    #+#             */
/*   Updated: 2023/11/09 14:54:01 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_ray	init_ray(t_map_data *data)
{
	t_ray	ray;

	ray.fov = 60;
	ray.angle = fix_angle(data->angle - ray.fov / 2);
	ray.projection_width = 1370;
	ray.projection_height = 770;
	ray.raycast_angle = ray.fov / ray.projection_width;
	ray.center.x = ray.projection_width / 2;
	ray.center.y = ray.projection_height / 2;
	return (ray);
}

static void	check_hit_wall(t_map_data *data, t_float_v *grid, t_float_v *map,
t_float_v *offset)
{
	int	dof;

	dof = 0;
	if (map->x == data->pos.x && map->y == data->pos.x)
		return ;
	while (dof < 10000)
	{
		grid->x = (int)map->x / SIZE_B;
		grid->y = (int)map->y / SIZE_B;
		if (grid->y >= 0 && grid->x >= 0 && grid->x < data->map_w
			&& grid->y < data->map_h
			&& data->map[(int)grid->y][(int)grid->x] == '1')
			dof = 10000;
		else
		{
			map->x += offset->x;
			map->y += offset->y;
			dof++;
		}
	}
}

static void	cast_horizontal(t_map_data *data, t_ray *ray)
{
	t_float_v *player;

	player = &data->pos;
	ray->cotan = 1.0 / tan(deg_to_rad(ray->angle));
	if (sin(deg_to_rad(ray->angle)) > 0.001)
	{
		ray->h_map.y = ((int)player->y / SIZE_B) * SIZE_B - 0.0001;
		ray->h_map.x = player->x + ((player->y - ray->h_map.y) * ray->cotan);
		ray->hd.y = (double)-SIZE_B;
		ray->hd.x = -ray->hd.y * ray->cotan;
	}
	else if (sin(deg_to_rad(ray->angle)) < -0.001)
	{
		ray->h_map.y = (int)player->y / SIZE_B * SIZE_B + SIZE_B;
		ray->h_map.x = player->x + ((player->y - ray->h_map.y) * ray->cotan);
		ray->hd.y = (double)SIZE_B;
		ray->hd.x = -ray->hd.y * ray->cotan;
	}
	else
	{
		ray->h_map.x = player->x;
		ray->h_map.y = player->y;
	}
	check_hit_wall(data, &ray->h_grid, &ray->h_map, &ray->hd);
}
static void	cast_vertical(t_map_data *data, t_ray *ray)
{
	t_float_v	*player;

	player = &data->pos;
	ray->tan = tan(deg_to_rad(ray->angle));
	if (cos(deg_to_rad(ray->angle)) < -0.001)
	{
		ray->v_map.x = ((int)player->x / SIZE_B) * SIZE_B - 0.0001;
		ray->v_map.y = player->y + ((player->x - ray->v_map.x) * ray->tan);
		ray->vd.x = -SIZE_B;
		ray->vd.y = -ray->vd.x * ray->tan;
	}
	else if (cos(deg_to_rad(ray->angle)) > 0.001)
	{
		ray->v_map.x = ((int)player->x / SIZE_B) * SIZE_B + SIZE_B;
		ray->v_map.y = player->y + ((player->x - ray->v_map.x) * ray->tan);
		ray->vd.x = SIZE_B;
		ray->vd.y = -ray->vd.x * ray->tan;
	}
	else
	{
		ray->v_map.x = player->x;
		ray->v_map.y = player->y;
	}
	check_hit_wall(data, &ray->v_grid, &ray->v_map, &ray->vd);
}

static void	get_shortest(t_map_data *data, t_ray *ray)
{
	float	h_dist;
	float	v_dist;

	h_dist = get_dist(&data->pos, &ray->h_map);
	v_dist = get_dist(&data->pos, &ray->v_map);
	if (h_dist != 0.0f && (h_dist < v_dist || v_dist == 0.0f))
	{
		ray->shortest = 'h';
		ray->distance = h_dist * cos(deg_to_rad(ray->angle - data->angle));
	}
	else
	{
		ray->shortest = 'v';
		ray->distance = v_dist * cos(deg_to_rad(ray->angle - data->angle));
	}
}

static void	draw_rays(t_map_data *data)
{
	t_ray	ray;
	int		rays_cast;

	ray = init_ray(data);
	rays_cast = 0;
	while (rays_cast <= PROJ_V)
	{
		cast_horizontal(data, &ray);
		cast_vertical(data, &ray);
		get_shortest(data, &ray);
		draw_view(data, &ray, PROJ_V - rays_cast);
		ray.angle += ray.raycast_angle;
		ray.angle = fix_angle(ray.angle);
		rays_cast++;
	}
}

void	raycasting(void *param)
{
	t_map_data	*data;
	t_vector	cord;

	data = (t_map_data *)param;
	cord.y = 0;
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx_data->mlx);
	// draw the background. without this the lines between squares are colored with nose color
	while (cord.y < HEIGHT_W)
	{
		cord.x = 0;
		while (cord.x < WIDTH_W)
		{
			mlx_put_pixel(data->mlx_data->window, cord.x, cord.y, 0x00000000);
			cord.x++;
		}
		cord.y++;
	}
	draw_rays(data);
	draw_map(data);
	draw_player(data);
	draw_nose(data);
}

// static void	draw_line(t_player player, t_map_data *data)
// {
// 	int			color;
// 	t_float_v	angle;
// 	t_float_v	pos;

// 	(void)player;
// 	color = get_rgba(255, 0, 0, 255);
// 	angle.x = data->dir.x;
// 	angle.y = data->dir.y;
// 	pos.x = data->pos.x + SIZE_P / 2;
// 	pos.y = data->pos.y + SIZE_P / 2;
// 	int i = 0;
// 	while (i < 60 && pos.y > -1 && pos.x > -1)
// 	{
// 		mlx_put_pixel(data->mlx_data->window, pos.x, pos.y, color);
// 		pos.y += angle.y;
// 		pos.x += angle.x;
// 		i++;
// 	}
// }

// static t_player	init_player(t_map_data *data)
// {
// 	t_player	player;

// 	player.player_view.x = data->dir.x;
// 	player.player_view.y = data->dir.y;
// 	player.player_pos.x = data->pos.x;
// 	player.player_pos.y = data->pos.y;
// 	return (player);
// }

// static void	draw_rays(t_map_data *data)
// {
// 	t_player	player;

// 	player = init_player(data);
// 	player.ray_dir.x = cos(player.player_view.x);
// 	player.ray_dir.y = sin(player.player_view.y);
// }

// static void	draw_rays(t_map_data *data)
// {
// 	t_player	player;
// 	float		atan;

// 	player = init_player(data);
// 	while (player.r < 1)
// 	{
// 		player.dof = 0;
// 		atan = -1 / tan(player.raya);
// 		// check horizontal lines
// 		if (player.raya > PI)
// 		{
// 			player.rayy = (((int)player.playery>>6)<<6) - 0.0001;
// 			player.rayx = (player.playery - player.rayy) * atan + player.playerx;
// 			player.yo = -64;
// 			player.xo = -player.yo * atan;
// 		}
// 		else if (player.raya < PI)
// 		{
// 			player.rayy = (((int)player.playery>>6)<<6) + 64;
// 			player.rayx = (player.playery - player.rayy) * atan + player.playerx;
// 			player.yo = 64;
// 			player.xo = -player.yo * atan;
// 		}
// 		if (player.raya == 0 || player.raya == PI) // looking straight left or right
// 		{
// 			player.rayx = player.playerx;
// 			player.rayy = player.playery;
// 			player.dof = 8;
// 		}
// 		while (player.dof < 8)
// 		{
// 			player.mapx = (int)(player.rayx)>>6;
// 			player.mapy = (int)(player.rayy)>>6;
// 			player.mapp = player.mapy * 9 + player.mapx; // 9 = map width
// 			if (player.mapp < 9 * 5 && data->map[player.mapp] == '1')
// 				player.dof = 8;
// 			else
// 			{
// 				player.rayx += player.xo;
// 				player.rayy += player.yo;
// 				player.dof++;
// 			}
// 		}
// 		draw_line(player, data);
// 		player.r++;
// 	}
// }

// void	raycasting(void *param)
// {
// 	t_map_data	*data;
// 	t_vector	cord;

// 	data = (t_map_data *)param;
// 	cord.y = 0;
// 	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(data->mlx_data->mlx);
// 	// draw the background. without this the lines between squares are colored with nose color
// 	while (cord.y < HEIGHT_W)
// 	{
// 		cord.x = 0;
// 		while (cord.x < WIDTH_W)
// 		{
// 			mlx_put_pixel(data->mlx_data->window, cord.x, cord.y, 0x00000000);
// 			cord.x++;
// 		}
// 		cord.y++;
// 	}
// 	draw_map(data);
// 	draw_player(data);
// 	draw_nose(data);
// 	// draw_rays(data);
// }

// static void	draw_fov(t_map_data *data)
// {


// }

// static void	draw_floor_ceiling(t_map_data *data)
// {
// 	t_vector	window;

// 	window.y = 0;
// 	while (window.y < HEIGHT_W / 2)
// 	{
// 		window.x = 0;
// 		while (window.x < WIDTH_W)
// 		{
// 			mlx_put_pixel(data->mlx_data->window, window.x, window.y, data->mlx_data->ceiling);
// 			window.x++;
// 		}
// 		window.y++;
// 	}
// 	while (window.y < HEIGHT_W)
// 	{
// 		window.x = 0;
// 		while (window.x < WIDTH_W)
// 		{
// 			mlx_put_pixel(data->mlx_data->window, window.x, window.y, data->mlx_data->floor);
// 			window.x++;
// 		}
// 		window.y++;
// 	}

// }

// void	raycasting(void *ptr)
// {
// 	t_map_data *data;
// 	// t_vector 	cord;
// 	int			i;

// 	data = (t_map_data *)ptr;
// 	// cord.y = 0;
// 	i = 0;
// 	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(data->mlx_data->mlx);
// 	// this while loop will draw the background, maybe should be deleted in the end!
// 	// while (cord.y < HEIGHT_W)
// 	// {
// 	// 	cord.x = 0;
// 	// 	while (cord.x < WIDTH_W)
// 	// 	{
// 	// 		mlx_put_pixel(data->mlx_data->window, cord.x, cord.y, 0x000000);
// 	// 		cord.x++;
// 	// 	}
// 	// 	cord.y++;
// 	// }
// 	draw_floor_ceiling(data);
// 	//this will be used for the minimap, with other commented out functions!
// 	draw_map(data);
// 	draw_player(data);
// 	draw_nose(data);
// 	print_struct(data);
// 	while (i < WIDTH_W)
// 	{
// 		// calculate_ray();
// 		// draw_fov(data);
// 		// draw_3d(data);
// 		i++;
// 	}
// }
