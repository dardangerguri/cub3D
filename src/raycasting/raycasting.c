/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:10:33 by dardangergu       #+#    #+#             */
/*   Updated: 2023/11/10 16:59:07 by dgerguri         ###   ########.fr       */
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
	while (dof < 1000)
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

static void	draw_floor_ceiling(t_map_data *data)
{
	t_vector	window;

	window.y = 0;
	while (window.y < HEIGHT_W / 2)
	{
		window.x = 0;
		while (window.x < WIDTH_W)
		{
			mlx_put_pixel(data->mlx_data->window, window.x, window.y, data->mlx_data->ceiling);
			window.x++;
		}
		window.y++;
	}
	while (window.y < HEIGHT_W)
	{
		window.x = 0;
		while (window.x < WIDTH_W)
		{
			mlx_put_pixel(data->mlx_data->window, window.x, window.y, data->mlx_data->floor);
			window.x++;
		}
		window.y++;
	}
}

void	raycasting(void *param)
{
	t_map_data	*data;

	data = (t_map_data *)param;
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx_data->mlx);
	draw_floor_ceiling(data);
	draw_rays(data);
	draw_map(data);
	// draw_player(data);
	// draw_nose(data);
}
