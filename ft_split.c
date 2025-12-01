/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupalhan <lupalhan@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:43:07 by lupalhan          #+#    #+#             */
/*   Updated: 2025/11/30 20:18:51 by lupalhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static void	free_split(char **split, size_t i)
{
	while (i > 0)
	{
		i--;
		free(split[i]);
	}
	free(split);
}

static char	*get_next_word(char const *s, char c, size_t *idx)
{
	size_t	len;
	char	*word;

	len = 0;
	while (s[*idx] == c)
		(*idx)++;
	while (s[*idx + len] && s[*idx + len] != c)
		len++;
	word = ft_substr(s, *idx, len);
	*idx += len;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	words;
	size_t	i;
	size_t	idx;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	i = 0;
	idx = 0;
	while (i < words)
	{
		res[i] = get_next_word(s, c, &idx);
		if (!res[i])
		{
			free_split(res, i);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}
