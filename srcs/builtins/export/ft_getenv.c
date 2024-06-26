/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:05:28 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/17 16:16:06 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_getenv(const char *name, char **envp)
{
	size_t	len;
	char	**env_var;

	if (name == NULL || envp == NULL)
		return (NULL);
	len = ft_strlen(name);
	env_var = envp;
	while (*env_var)
	{
		if (ft_strncmp(name, *env_var, len) == 0 && (*env_var)[len] == '=')
		{
			return (ft_strdup(*env_var + len + 1));
		}
		env_var++;
	}
	return (NULL);
}

int	index_locator(char *var, t_localenv *local)
{
	int	ret;

	ret = -1;
	ret = find_variable_index_recursive(var, local->content, 0);
	return (ret);
}

int	command_printenv(char **cmds, t_localenv *lo)
{
	int	i;
	int	index;

	i = 1;
	if (cmds == NULL || lo == NULL || lo->content == NULL)
		return (EXIT_FAILURE);
	if (cmds[i] == NULL)
		return (command_env(lo));
	if (cmds[i])
	{
		while (cmds[i])
		{
			index = index_locator(cmds[i], lo);
			if (index < 0)
				return (EXIT_FAILURE);
			else
				ft_printf("%s\n", lo->content[index] + ft_strlen(cmds[i]) + 1);
			i++;
		}
		if (i > 1)
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
