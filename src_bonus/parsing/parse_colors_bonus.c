/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:14:45 by dgerguri          #+#    #+#             */
/*   Updated: 2025/01/12 23:48:24 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	count_commas(char *str, bool *error)
{
	int	comma;

	comma = 0;
	while (*str)
	{
		if (*str == ',')
			comma++;
		str++;
	}
	if (comma != 2)
	{
		print_error_message(X_WRONG_COLOR_VALUE);
		*(error) = true;
	}
}

static int	check_digit(char *str, bool *error)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			print_error_message(X_WRONG_COLOR_VALUE);
			*(error) = true;
			break ;
		}
		str++;
	}
	return (0);
}

static void	check_and_assign(t_map_data *data, char *str, bool *error, char c)
{
	char	**rgb;
	int		i;

	i = -1;
	count_commas(str, error);
	if (!(*error))
		rgb = ft_split(str, ',');
	if (c == 'C' && !(*error))
	{
		while (rgb[++i] && !(*error))
			if (!check_digit(rgb[i], error))
				data->ceiling[i] = ft_atoi(rgb[i]);
		free_array(rgb);
	}
	else if (c == 'F' && !(*error))
	{
		while (rgb[++i] && !(*error))
			if (!check_digit(rgb[i], error))
				data->floor[i] = ft_atoi(rgb[i]);
		free_array(rgb);
	}
}

void	parse_colors(t_map_data *data, int i, int j, bool *error)
{
	char	*str;

	str = NULL;
	if (data->file_splitted[i][j] == 'C')
	{
		str = save_the_elements(data, i, j + 1, error);
		if (!(*error))
			check_and_assign(data, str, error, 'C');
	}
	else if (data->file_splitted[i][j] == 'F')
	{
		str = save_the_elements(data, i, j + 1, error);
		if (!(*error))
			check_and_assign(data, str, error, 'F');
	}
	free(str);
}
