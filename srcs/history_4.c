/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:48:50 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/21 13:54:17 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	join_to_line(char **total_line, char ***heredocs, t_localenv *local)
{
	int	i;

	i = 0;
	if (!ft_parser(*total_line, &i))
	{
		heredoc_writer(*total_line, heredocs, i, local);
		free_split(*heredocs);
		return (false);
	}
	heredoc_writer(*total_line, heredocs, i, local);
	if (!writer_from_input(total_line, heredocs, local, i))
		return (false);
	if (!ft_parser(*total_line, &i))
		return (free(total_line), false);
	return (true);
}
