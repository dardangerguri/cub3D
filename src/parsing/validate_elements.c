/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:10:37 by dgerguri          #+#    #+#             */
/*   Updated: 2023/10/13 13:08:33 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	open_texture_files(char *file)
{
	int	fd;

	if (!file)
		return (error_message(X_MISSING_TEXTURE));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_message(X_WRONG_TEXTURE_FILE));
	close(fd);
	return (true);
}

static bool	validate_texture(t_map_data *data)
{
	if (!open_texture_files(data->north))
		return (false);
	if (!open_texture_files(data->south))
		return (false);
	if (!open_texture_files(data->west))
		return (false);
	if (!open_texture_files(data->east))
		return (false);
	return (true);
}

static int rgb(int r, int g, int b)
{
    return (r << 24 | g << 16 | b << 8 | 255);
}

static bool	validate_color_range(t_map_data *d, int *data, char c)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!(data[i] >= 0 && data[i] <= 255))
			return (error_message(X_WRONG_COLOR_VALUE));
		i++;
	}
	if (c == 'F')
		d->mlx_data->floor = rgb(data[0], data[1], data[2]);
	else if (c == 'C')
		d->mlx_data->ceiling = rgb(data[0], data[1], data[2]);
	return (true);
}

static bool	validate_colors(t_map_data *data)
{
	if (!data->floor || !data->ceiling)
		print_error_message(X_MISSING_COLOR);
	if (!validate_color_range(data, data->floor, 'F'))
		return (false);
	if (!validate_color_range(data, data->ceiling, 'C'))
		return (false);
	return (true);
}

bool	validate_elements(t_map_data *data)
{
	if (!validate_texture(data))
		return (false);
	if (!validate_colors(data))
		return (false);
	return (true);
}
