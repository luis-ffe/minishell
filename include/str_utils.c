/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 08:13:07 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/01/29 11:53:56 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
using in special parser at the moment
*/
#include "minishell.h"

bool	is_space(char c)
{
	if ((c > 8 && c < 14) || c == ' ')
		return (true);
	return (false);
}

/* NEED TO ADD THIS TO THE HEADER LATER I DO IT>
int	ignore_in_quotes(const char *str, int pos) // upon 
finding special char stops and returns his position in the string.
{
	while (str[pos] && is_special_char(str[pos]) == false)
	{
		if (str[pos] == D_QUOTE)
		{
			pos++;
			while (str[pos] && str[pos] != D_QUOTE) 
				pos++;
			return (pos + 1);
		}
		if (str[pos] == S_QUOTE)
		{
			pos++;
			while (str[pos] && str[pos] != S_QUOTE)
				pos++;
			return (pos + 1);
		}
		pos++;
	}
	return(pos);
}

bool	is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (true);
	return (false);
}

int	ignore_spaces(const char *str, int pos)
{
	while(is_space(str[pos]))
		pos++;
	return(pos);
}
*/
char	*ft_strcpy(char *s)
{
	int		i;
	char	*output;

	output = ft_calloc(ft_strlen(s), sizeof(char));
	i = 0;
	while (s[i])
	{
		output[i] = s[i];
		i++;
	}
	return (output);
}

t_token	*init_struct_cmd(void)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->content = NULL;
	new->next = NULL;
	return (new);
}

void	add_token(t_token **tokens, t_token *new)
{
	t_token	*trav;

	trav = NULL;
	if (*tokens == NULL)
		*tokens = new;
	else
	{
		trav = *tokens;
		while (trav->next != NULL)
			trav = trav->next;
		trav->next = new;
	}
}
