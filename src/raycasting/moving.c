/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:38:33 by dgerguri          #+#    #+#             */
/*   Updated: 2023/11/09 20:04:29 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_left(t_map_data *data)
{
	float	x;
	float	y;

	x = data->dir.y * SPEED;
	y = -data->dir.x * SPEED;
	data->pos.x = data->pos.x + x;
	data->pos.y = data->pos.y + y;
}

static void	move_right(t_map_data *data)
{
	float	x;
	float	y;

	x = -data->dir.y * SPEED;
	y = data->dir.x * SPEED;
	data->pos.x = data->pos.x + x;
	data->pos.y = data->pos.y + y;
}

static void	move_down(t_map_data *data)
{
	float	x;
	float	y;

	x = data->pos.x - data->dir.x * SPEED;
	y = data->pos.y - data->dir.y * SPEED;
	data->pos.x = x;
	data->pos.y = y;
}

static void	move_up(t_map_data *data)
{
	float	x;
	float	y;

	x = data->pos.x + data->dir.x * SPEED;
	y = data->pos.y + data->dir.y * SPEED;
	data->pos.x = x;
	data->pos.y = y;
}

static void	turn_player(t_map_data *data, int keycode)
{
	if (keycode == MLX_KEY_LEFT)
		data->angle = fix_angle(data->angle + 5);
	else
		data->angle = fix_angle(data->angle - 5);
	data->dir.x = cos(deg_to_rad(data->angle));
	data->dir.y = -sin(deg_to_rad(data->angle));
}

void	moving(void *ptr)
{
	t_map_data *data;
	// t_float_v	move;

	data = (t_map_data *)ptr;
	// move.x = 0;
	// move.y = 0;
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_W))
	{
		move_up(data);
		print_struct(data);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_S))
	{
		move_down(data);
		print_struct(data);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_A))
	{
		move_left(data);
		print_struct(data);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_D))
	{
		move_right(data);
		print_struct(data);
	}

	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_LEFT))
	{
		turn_player(data, MLX_KEY_LEFT);
		print_struct(data);
	}
	if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_RIGHT))
	{
		turn_player(data, MLX_KEY_RIGHT);
		print_struct(data);
	}
	// if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_LEFT))
	// {
	// 	move_left_arrow(data);
	// 	print_struct(data);
	// 	// printf("data->dir.x: %f\n", data->dir.x);
	// 	// printf("data->dir.y: %f\n", data->dir.y);
	// }
	// if (mlx_is_key_down(data->mlx_data->mlx, MLX_KEY_RIGHT))
	// {
	// 	move_right_arrow(data);
	// 	print_struct(data);
	// 	// printf("data->dir.x: %f\n", data->dir.x);
	// 	// printf("data->dir.y: %f\n", data->dir.y);
	// }
}
