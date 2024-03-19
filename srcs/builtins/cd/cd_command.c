/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:09:06 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/03/19 10:40:02 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	change_directory(const char *path)
{
	if (chdir(path) == -1)
		return (-1);
	return (0);
}

char	*get_home_directory(t_localenv *local)
{
	char	*home_dir;

	home_dir = ft_getenv("HOME", local->content);
	if (!home_dir)
		return (NULL);
	return (home_dir);
}

char	*get_previous_directory(t_localenv *local)
{
	char	*prev_dir;

	prev_dir = ft_getenv("OLDPWD", local->content);
	if (!prev_dir)
		return (NULL);
	return (prev_dir);
}

int	update_directories(t_localenv *local, char *cwd)
{
	if (ft_setenv("OLDPWD", ft_getenv("PWD", local->content), local) == -1)
		return (-1);
	if (ft_setenv("PWD", cwd, local) == -1)
		return (-1);
	return (0);
}

int	command_cd(char **cmds, t_localenv *local)
{
	char	*target_dir;
	char	cwd[PATH_MAX];

	if (cmds[1] == NULL || cmds[1][0] == '\0')
		target_dir = get_home_directory(local);
	else if (strcmp(cmds[1], "-") == 0)
		target_dir = get_previous_directory(local);
	else
	{
		if (cmds[1][0] == '$')
			target_dir = master_expander(cmds[1], local);
		else
			target_dir = cmds[1];
	}
	if (!target_dir)
		return (1);
	if (change_directory(target_dir) == -1)
		return (1);
	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	if (update_directories(local, cwd) == -1)
		return (1);
	return (0);
}

//ADICIONAR EXPANSION DE VARIABLES