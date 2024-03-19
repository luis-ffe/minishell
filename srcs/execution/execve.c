/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:49:36 by masoares          #+#    #+#             */
/*   Updated: 2024/03/14 18:20:41 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_execve(char **cmds, t_localenv *local, t_info info, t_cmd_info cmd_info)
{
	char	**p_path;

	p_path = ft_split(ft_getenv("PATH", local->content), ':');
	if (ft_strchr(cmds[0], '/'))
		execve_decider(cmds, local, info, cmd_info);
	else
	{
		test_commands(cmds, p_path);
		execve_decider(cmds, local, info, cmd_info);
	}
	return (free_split(p_path), 0);
}

void test_commands(char **cmds, char **p_path)
{
	char	*line;
	char	*cmd_0;
	int		i;
	
	cmd_0 = ft_strcpy(cmds[0]);
	line = cmds[0];
	cmds[0] = ft_strjoin("/usr/local/sbin/", cmd_0);
	free(line);
	i = 0;
	while (access(cmds[0], F_OK) != 0 && p_path[i] != NULL)
	{
		line = p_path[i];
		p_path[i] = ft_strjoin(p_path[i], "/");
		free(line);
		line = cmds[0];
		cmds[0] = ft_strjoin(p_path[i], cmd_0);
		free(line);
		i++;
	}
	free (cmd_0);
}

int		execve_decider(char **cmds, t_localenv *local, t_info info, t_cmd_info cmd_info)
{
	int		pid;
	int		status;
	
	status = 0;
	if (cmd_info.in_out[0] == HEREDOC)
		status = execve_heredoc(info, cmds, local);
	else if (cmd_info.in_out[0] == IN_DOC)
	 	execve_doc(cmd_info.fd_in_out[0], info, cmds, local);
	else
	{
		pid = fork();
		if (pid == 0)
			status = execve(cmds[0], cmds, local->content);
		waitpid(pid, NULL, 0);
	}
	printf("%d\n", status);
	return(status);
}

int		execve_heredoc(t_info info, char **cmds, t_localenv *local)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	
	pipe(fd);
	pid1 = fork();
	if (pid1 < 0)
		return (-1) ;
	else if(pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		printf("%s", (*info.heredocs)[info.pos_heredoc]);
		exit(EXIT_SUCCESS);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (-2) ;
	else if(pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(cmds[0], cmds, local->content);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

int		execve_doc(int fd_in, t_info info, char **cmds, t_localenv *local)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	char	buffer[21];
	int		bread;
	(void) info;
	
	pipe(fd);
	pid1 = fork();
	if (pid1 < 0)
		return (-1);
	else if(pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		while (bread > 0)
		{
			bread = read(fd_in, buffer, 20);
			buffer[bread] = '\0';
			printf("%s", buffer);
		}
		exit(EXIT_SUCCESS);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (-2) ;
	else if(pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(cmds[0], cmds, local->content);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}