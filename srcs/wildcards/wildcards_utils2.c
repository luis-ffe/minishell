/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:53:10 by masoares          #+#    #+#             */
/*   Updated: 2024/04/15 12:08:44 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

char	**wild_splitter(char *str)
{
	char	**wild;
	int		i;
	int		j;
	int		k;


	i = 0;
	j = 0;
	wild = (char **) malloc (sizeof(char *) * (wildcards_counter(str) + 1));
	while (str[i])
	{
		i = ignore_in_quotes(str, i);
		if (str[i] == '*')
		{
			k = i - 1;
			while (str[k] && !is_special_char(str[j]))
			{
				if (str[k] == '<' && k > 0 && str[k - 1] == '<')
					k = -10;
				k--;
			}
			if (k < -5)
				continue;
			else if((i == 0 || is_space(str[i - 1]) || is_special_char(str[i - 1]))
				&& (!str[i + 1] || is_space(str[i + 1])
				|| is_special_char(str[i + 1])))
				wild[j] = add_simple_wildcard(str, &i);
			else if ((i == 0 || is_space(str[i - 1]) 
				|| is_special_char(str[i - 1])) && (str[i + 1] 
				&& !is_space(str[i + 1]) && !is_special_char(str[i + 1])))
				wild[j] = add_forw_wildcard(str, &i);
			else if ((i != 0 && !is_space(str[i - 1])
				&& !is_special_char(str[i - 1])) && (is_space(str[i + 1])
				|| is_special_char(str[i + 1])))
				wild[j] = add_back_wildcard(str, &i);
			else if (!is_space(str[i - 1]) && !is_special_char(str[i - 1])
				&& !is_space(str[i + 1]) && !is_special_char(str[i + 1]))
				wild[j] = add_middle_wildcard(str, &i);
			j++;
		}
		i++;
	}
	wild[j] = NULL;
	return (wild);
}

char	*add_simple_wildcard(char *str, int *i)
{
	char	*wildcard;
	int 	j;

	j = *i - 1;
	while (str[j] && !is_special_char(str[j]))
	{
		if (str[j] == '<' && j >0 && str[j - 1] == '<')
			return ("");
		j--;
	}
	wildcard = ft_calloc(1 + 1, sizeof(char));
	wildcard[0] = '*';
	(*i)++;
	wildcard[*i] = '\0';
	return (wildcard);
}

char	*add_forw_wildcard(char *str, int *i)
{
	int		beg;
	int		end;
	char	*wildcard;
	int		j;

	beg = *i;
	(*i)++;
	while (str[*i] && !is_space(str[*i]) && !is_special_char(str[*i]))
		(*i)++;
	end = *i - 1;
	j = 0;
	wildcard = (char *) malloc(sizeof(char) * (end - beg + 1));
	while (beg <= end)
	{
		wildcard[j] = str[beg];
		beg++;
		j++;
	}
	wildcard[j] = '\0';
	return (wildcard);
}

char	*add_back_wildcard(char *str, int *i)
{
	int		beg;
	int		end;
	char	*wildcard;
	int		j;

	end = *i;
	beg = *i;

	j = *i - 1;
	while (str[j] && !is_special_char(str[j]))
	{
		if (str[j] == '<' && j >0 && str[j - 1] == '<')
			return("");
		j--;
	}
	while (str[beg] && !is_space(str[beg]) && !is_special_char(str[beg]))
		(beg)--;
	(beg)++;
	j = 0;
	wildcard = (char *) malloc(sizeof(char) * (end - beg + 1));
	while (beg <= end)
	{
		wildcard[j] = str[beg];
		beg++;
		j++;
	}
	wildcard[j] = '\0';
	return (wildcard);
}

char	*add_middle_wildcard(char *str, int *i)
{
	int		beg;
	int		end;
	char	*wildcard;
	int		j;

	j = 0;
	while (str[*i] && !is_space(str[*i]) && !is_special_char(str[*i]))
		(*i)++;
	end = *i;
	(*i)--;
	while ((*i) != 0 && !is_space(str[*i]) && !is_special_char(str[*i]))
		(*i)--;
	beg = *i + 1;
	wildcard = (char *) malloc(sizeof(char) * (end - beg + 1));
	while (beg <= end)
	{
		wildcard[j] = str[beg];
		beg++;
		j++;
	}
	wildcard[j] = '\0';
	*i = end;
	return (wildcard);
}
