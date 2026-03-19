/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:13:53 by kqueiroz          #+#    #+#             */
/*   Updated: 2025/07/31 14:15:45 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			words++;
		i++;
	}
	return (words);
}

static char	*copy_word(const char *s, char c)
{
	int		len;
	int		i;
	char	*dest;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	i = 0;
	while (i < len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	free_split(char **arr, int i)
{
	while (--i >= 0)
		free(arr[i]);
	free(arr);
}

static int	fill_split(char **s_splited, const char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			s_splited[i] = copy_word(s, c);
			if (!s_splited[i])
				return (free_split(s_splited, i), 0);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	s_splited[i] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**s_splited;
	int		words;

	if (!s)
		return (0);
	words = count_words(s, c);
	s_splited = malloc((words + 1) * sizeof(char *));
	if (!s_splited)
		return (0);
	if (!fill_split(s_splited, s, c))
		return (0);
	return (s_splited);
}
