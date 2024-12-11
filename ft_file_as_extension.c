/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_as_extension.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:46:46 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/10 10:52:10 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_strendwith(const char *str, const char *end)
{
	int	i;
	int	j;

	if (str == NULL || end == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	j = 0;
	while (end[j])
		j++;
	if (j > i)
		return (0);
	while (j >= 0)
	{
		if (str[i] != end[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}

int	ft_file_as_extension(const char *filepath, const char *ext)
{
	char	*file;
	int		len;

	if (filepath == NULL)
		return (0);
	if (ext == NULL || *ext == '\0')
		return (1);
	len = ft_strlen(filepath);
	while (len >= 0 && filepath[len] != '/')
		len--;
	file = (char *)(&filepath[len + 1]);
	return (ft_strendwith(file, ext) && ft_strlen(file) > ft_strlen(ext));
}
