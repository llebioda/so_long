/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:48:19 by llebioda          #+#    #+#             */
/*   Updated: 2024/11/08 16:35:22 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	s;
	char	*c;
	size_t	i;

	if (nmemb == 0 || size == 0)
		return (NULL);
	s = nmemb * size;
	if (s / nmemb != size)
		return (NULL);
	ptr = malloc(s);
	if (ptr == NULL)
		return (NULL);
	c = ptr;
	i = 0;
	while (i < s)
		c[i++] = 0;
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dst = malloc(len_s1 + len_s2 + 1);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < len_s1 || i < len_s2)
	{
		if (i < len_s1)
			dst[i] = s1[i];
		if (i < len_s2)
			dst[i + len_s1] = s2[i];
		i++;
	}
	dst[len_s1 + len_s2] = '\0';
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (0);
}
