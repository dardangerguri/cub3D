/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:10:33 by dardangergu       #+#    #+#             */
/*   Updated: 2025/01/13 14:54:52 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_ray	init_ray(t_map_data *data)
{
	t_ray	ray;

	ray.fov = 60;
	ray.angle = fix_angle(data->angle - ray.fov / 2);
	ray.raycast_angle = ray.fov / (float)WIDTH_W;
	ray.center.x = WIDTH_W / 2;
	ray.center.y = HEIGHT_W / 2;
	return (ray);
}

static void	cast_horizontal(t_map_data *data, t_ray *ray)
{
	t_float_v	*player;

	player = &data->pos;
	ray->cotan = 1.0 / tan(deg_to_rad(ray->angle));
	if (sin(deg_to_rad(ray->angle)) > 0.001)
	{
		ray->h_map.y = floor(player->y / SIZE_B) * SIZE_B - 0.001;
		ray->h_map.x = player->x + ((player->y - ray->h_map.y) * ray->cotan);
		ray->hd.y = -SIZE_B;
		ray->hd.x = -ray->hd.y * ray->cotan;
	}
	else if (sin(deg_to_rad(ray->angle)) < -0.001)
	{
		ray->h_map.y = floor(player->y / SIZE_B) * SIZE_B + SIZE_B;
		ray->h_map.x = player->x + ((player->y - ray->h_map.y) * ray->cotan);
		ray->hd.y = SIZE_B;
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
		ray->v_map.x = floor(player->x / SIZE_B) * SIZE_B - 0.001;
		ray->v_map.y = player->y + ((player->x - ray->v_map.x) * ray->tan);
		ray->vd.x = -SIZE_B;
		ray->vd.y = -ray->vd.x * ray->tan;
	}
	else if (cos(deg_to_rad(ray->angle)) > 0.001)
	{
		ray->v_map.x = floor(player->x / SIZE_B) * SIZE_B + SIZE_B;
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

static void	draw_rays(t_map_data *data)
{
	t_ray	ray;
	int		rays_cast;

	ray = init_ray(data);
	rays_cast = 0;
	while (rays_cast <= WIDTH_W)
	{
		cast_horizontal(data, &ray);
		cast_vertical(data, &ray);
		get_shortest(data, &ray);
		draw_view(data, &ray, WIDTH_W - rays_cast);
		ray.angle += ray.raycast_angle;
		ray.angle = fix_angle(ray.angle);
		rays_cast++;
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
	draw_minimap(data);
}
