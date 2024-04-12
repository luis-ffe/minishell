/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:14:49 by masoares          #+#    #+#             */
/*   Updated: 2024/04/12 12:16:10 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_signal = 0;

int	main(int ac, char **av, char **env)
{
	char		*input;
	char		**heredocs;
	int			i;
	t_localenv	*local_env;

	(void) ac;
	(void) av;
	local_env = env_init(env);
	input = NULL;
	i = 0;
	switch_sig_function();
	while (1)
	{
		input = get_line(input, &heredocs, local_env);
		if (input == NULL)
			continue;
		if (input != NULL && *input && input[ft_strlen(input) - 1] != 0x03)
		{
			if (input[ignore_spaces(input, i)])
				general_executer(input, &heredocs, local_env);
			free(input);
			input = NULL;
		}
		if (input != NULL)
			free(input);
	}
}

/*
we can reuse the command_exit at the end of the main loop to free all shits 
and exit the program with the corret exit code
*/


void	clear_terminal(char *paths)
{
	char	**cmd;
	int		pid;
	char	**p_path;
	int		i;

	i = 0;
	p_path = ft_split(paths, ':');
	cmd = ft_split("clear", ' ');
	while (access(cmd[0], F_OK) != 0 && p_path[i] != NULL)
	{
		p_path[i] = ft_strjoin(p_path[i], "/");
		cmd[0] = ft_strjoin(p_path[i], "clear");
		i++;
	}
	pid = fork();
	if (pid == 0)
		execve(cmd[0], cmd, NULL);
	waitpid(pid, NULL, 0);
	free_split(cmd);
	free_split(p_path);
	return ;
}
