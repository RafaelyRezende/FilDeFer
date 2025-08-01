/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:04:20 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/07/21 14:15:43 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;
	unsigned int	str_len;
	unsigned int	diff;

	i = 0;
	str_len = ft_strlen(s);
	if (!*s || start >= str_len || len == 0)
		return (ft_strdup(""));
	if (start >= str_len && len == 0)
	{
		substr = (char *) malloc(1);
		*substr = '\0';
		return (substr);
	}
	diff = (str_len - start);
	if (len > diff)
		len = diff;
	substr = (char *) malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
/*
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*s_ptr;
	char	*e_ptr;

	if (start >= (size_t) ft_strlen(s) || len == 0)
	{
		s_ptr = (char *) malloc(1);
		*s_ptr = '\0';
		return (s_ptr);
	}
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	s_ptr = (char *) s + start;
	e_ptr = s_ptr;
	substr = (char *) malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (len-- && *s_ptr)
	{
		*substr = *s_ptr;
		s_ptr++;
		substr++;
	}
	*substr = '\0';
	return (e_ptr);
}
*/
