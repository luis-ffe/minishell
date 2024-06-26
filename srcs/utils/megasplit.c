/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megasplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:46:03 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 09:46:08 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	word_counter(char *s, char *c);
static int	string_size(char *s, char *c);

int	quote_ignore(char *s, char c)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (1);
}

int	all_quotes_ignore(char *s)
{
	if (*s == '\"')
		return (quote_ignore(s, D_QUOTE) + 1);
	else if (*s == '\'')
		return (quote_ignore(s, S_QUOTE) + 1);
	return (1);
}

static int	word_counter(char *s, char *c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		while (ft_strchr(c, s[i]) && s[i] != '\0')
			i += all_quotes_ignore(s + i);
		if (s[i] != '\0')
			counter++;
		while (!ft_strchr(c, s[i]) && s[i] != '\0')
			i += all_quotes_ignore(s + i);
	}
	return (counter);
}

static int	string_size(char *s, char *c)
{
	int	i;

	i = 0;
	while (!ft_strchr(c, s[i]) && s[i] != '\0')
		i += all_quotes_ignore(s + i);
	return (i);
}

char	**ft_split_ignore_quotes(char *s, char *c)
{
	char	**str_array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	str_array = malloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (!str_array)
		return (NULL);
	while (s[i] != '\0')
	{
		while (ft_strchr(c, s[i]) && s[i] != '\0')
			i += all_quotes_ignore(s + i);
		if (s[i] != '\0')
		{
			str_array[j] = ft_substr(s, i, string_size(s + i, c));
			j++;
		}
		while (!ft_strchr(c, s[i]) && s[i] != '\0')
			i += all_quotes_ignore(s + i);
	}
	str_array[j] = NULL;
	return (str_array);
}
