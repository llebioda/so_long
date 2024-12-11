/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:57:19 by llebioda          #+#    #+#             */
/*   Updated: 2024/12/09 13:18:56 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_char_number(long nb)
{
	int	a;

	a = 0;
	if (nb < 0)
	{
		a++;
		nb = -nb;
	}
	while (nb >= 10)
	{
		nb /= 10;
		a++;
	}
	return (a + 1);
}

char	*ft_itoa(int nb)
{
	char	*dest;
	int		dest_len;
	int		i;
	long	n;
	int		is_neg;

	n = (long)nb;
	dest_len = get_char_number(n);
	dest = ft_calloc(dest_len + 1, 1);
	if (dest == NULL)
		return (NULL);
	i = dest_len - 1;
	is_neg = 0;
	if (n < 0)
	{
		is_neg = 1;
		dest[0] = '-';
		n = -n;
	}
	while (i >= is_neg)
	{
		dest[i--] = n % 10 + '0';
		n /= 10;
	}
	return (dest);
}
