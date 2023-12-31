/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:19:47 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/28 12:27:39 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*print_error_message(char *message)
{
	ft_printf(2, "%s", message);
	return (NULL);
}

bool	error_message(char *message)
{
	ft_printf(2, "%s", message);
	return (false);
}
