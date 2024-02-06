/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/06 16:54:39 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ignore_in_quotes(char *str, int pos)
{
	while (str[pos] && !is_special_char(str[pos]))
	{
		if (str[pos] == D_QUOTE)
		{
			pos++;
			while (str[pos] && str[pos] != D_QUOTE)
				pos++;
		}
		else if (str[pos] == S_QUOTE)
		{
			pos++;
			while (str[pos] && str[pos] != S_QUOTE)
				pos++;
		}
		pos++;
	}
	return (pos);
}

int	ignore_spaces(char *str, int pos)
{
	while(is_space(str[pos]))
		pos++;
	return(pos);
}

bool	is_space(char c)
{
	if ((c > 8 && c < 14) || c == ' ')
		return (true);
	return (false);
}

bool	is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<' ||  c == '&')
		return (true);
	return (false);
}

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
