/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:32:37 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/04/15 22:14:30 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ptr;
	char		*start_ptr;
	char const	*new_s;

	if (!s || start > ft_strlen(s, '\0'))
	{
		ptr = (char *)malloc(1);
		if (!ptr)
			return (NULL);
		*ptr = '\0';
		return (ptr);
	}
	if (len > (ft_strlen(s, '\0') - start))
		len = (ft_strlen(s, '\0') - start);
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (NULL);
	new_s = s + start;
	start_ptr = ptr;
	while (len-- > 0 && *new_s)
		*(ptr++) = *(new_s++);
	*ptr = '\0';
	return (start_ptr);
}

size_t	ft_strlen(const char *str, char c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != c)
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		len;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s, '\0') + 1;
	ptr = (char *)malloc(len * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*s3;

	if (s1)
		len1 = ft_strlen(s1, '\0');
	else
		len1 = 0;
	len2 = ft_strlen(s2, '\0');
	s3 = malloc(len1 + len2 + 1);
	if (!s3)
		return (NULL);
	if (s1)
		ft_memmove(s3, s1, len1);
	ft_memmove(s3 + len1, s2, len2);
	s3[len1 + len2] = '\0';
	if (s1)
		free(s1);
	s2[0] = '\0';
	return (s3);
}
