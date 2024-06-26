/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:18:48 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/21 14:15:26 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <stdbool.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <linux/limits.h>
# include "parser.h"
# include "builtins.h"
# include "wildcards.h"
# include "signals.h"
//# include <sys/syslimits.h>

# define S_QUOTE 39
# define D_QUOTE 34

extern int	g_signal;

typedef enum e_builtin
{
	UNDEFINED,
	ECHOS,
	CD,
	PWD,
	ENV,
	EXPORT,
	UNSET,
	EXIT,
	PRINTENV,
}	t_builtin;

/*Define special characters that separate strings*/
typedef enum e_type
{
	NO_PIPE,
	D_PIPE,
	D_AMP,
}	t_type;

/*Define special characters within the separated strings*/
typedef enum e_special
{
	NONE,
	S_REDIR_IN,
	S_REDIR_OUT,
	D_REDIR_IN,
	D_REDIR_OUT,
	S_PIPE
}	t_special;

typedef enum s_in_out
{
	IN_DOC,
	HEREDOC,
	OUT_DOC,
	OUT_UND,
	UNDEF,
}	t_in_out;

typedef struct s_command
{
	char		*cmds;
	t_special	type;
	t_builtin	id;
}	t_command;

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
	struct s_token	*down;
	t_type			next_type;
	t_command		*cmds;
}	t_token;

typedef struct s_info
{
	char		***heredocs;
	int			pos_heredoc;
	t_localenv	*local;
	t_token		*token;
	t_token		*head;
}	t_info;

typedef struct s_cmd_info
{
	int			in_out[2];
	int			fd_in_out[2];
	t_builtin	id;	
}	t_cmd_info;

typedef struct s_heredocker
{
	char	***heredocs;
	int		n_heredocs;
	char	*line_read;
	int		i;
}	t_heredocker;

/*Definition of error cases*/
enum e_ERRORS
{
	SYNTAX_NEWLINE,
	SYNTAX_CLOSE_P,
	SYNTAX_OPEN_P,
	SYNTAX_PIPE,
	SYNTAX_D_PIPE,
	SYNTAX_PIPE_AMP,
	SYNTAX_AMP,
	SYNTAX_D_AMP,
	SYNTAX_AMP_PIPE,
	SYNTAX_CMD,
	SYNTAX_ASP,
	SYNTAX_S_ASP,
	SYNTAX_L_S_REDIR,
	SYNTAX_R_S_REDIR,
	SYNTAX_L_D_REDIR,
	SYNTAX_R_D_REDIR,
	SYNTAX_BACKSLASH,
	SYNTAX_COLON,
	HEREDOC_EOF,
};

/* ************************************************************************** */
/*                                TESTERS                                     */
/* ************************************************************************** */

/*in general_executor*/
int			tester_function(t_token **list);

/* ************************************************************************** */
/*                               MINISHELL                                    */
/* ************************************************************************** */

/*On start-up, this function clears the terminal before starting execution*/
void		clear_terminal(char *paths);

/* ************************************************************************** */
/*                              HISTORY_MAKER                                 */
/* ************************************************************************** */

/*Get a string from the command line and add to history.
Function sends error signal to ERRORS if anything wrong happens and returns
NULL, and returns the full string otherwise*/
char		*get_line(char *total_line, char ***heredocs, \
t_localenv *local_env);
bool		join_to_line(char **total_line, char ***heredocs, \
t_localenv *local);
bool		end_pipe_and(char *total_line);
int			is_only_spaces(char *total_line);
void		add_space_line(char **total_line, char *line_read);
int			open_parenthesis(char *total_line);
char		*create_pc_name(t_localenv *local_env);
char		*get_end_path(t_localenv *local_env);
void		first_fork(int fd0, int fd1, t_localenv *local_env, char *pwd);
void		line_reader(int fd0, int fd1, char **total_line);
void		extra_fork(int fd0, int fd1, t_localenv *local, \
char *line_read);

/* ************************************************************************** */
/*                             PARSER_GENERAL                                 */
/* ************************************************************************** */

/* General parser function. It must guarantee all clean-up of the string 
received and its freeing. The output is a completely clean string to 
be interpreted*/
bool		ft_parser(char *line_read, int *i);
bool		text_in_parenthesis(char *line_read, int *i);
bool		parenthesis_after_command(char *line_read, int *i);
bool		parenthesis_before_command(char *line_read, int *i);

/* ************************************************************************** */
/*                              PARSER_QUOTES                                 */
/* ************************************************************************** */

/*General function to do the first clean-up of the string received in the
terminal. It gets rid of the unnecessary quotes*/
bool		parser_quotes(char *input, int *i);

/* ************************************************************************** */
/*                               GENERAL_EXECUTOR                             */
/* ************************************************************************** */

/**/
void		general_executer(char *input, char ***heredocs, \
t_localenv *local_env);
/*general function to divide the full line read into parts separated by pipes*/
t_token		*command_organizer(char *input);
/*function used to divide the full line read into parts separated by pipes*/
void		command_divider(t_token **list, char *in, \
t_type	type, t_token *token);
t_type		type_definer(char *input, int *i);
bool		token_has_par(t_token *token);
char		*trim_string(char *str);

/*Function to find the next '"' or '''*/
int			find_next(char *input, int init_pos);
/* creates new t_token node with the segment of the full line read*/
t_token		*create_node(int init, int end, char *input, t_type type);
int			find_closed(char *input, int i);
t_token		*token_creator(int i, int j, char *input, int type);
int			jumper_i(char *input, int *i);
void		addings_tokens(t_token **list, t_token *token, t_type type);

/* ************************************************************************** */
/*                              GENERAL_EXECUTOR_2                            */
/* ************************************************************************** */

/*within each element of the linked list created, this function takes care of 
the general division of the partial strings in an array of structs separated by
special characters*/
void		commands_separator(t_token *cmd_list);
/*This function counts the number of special characters that are in the
substring, >> << && etc count as one special character*/
int			pipe_counter(t_token *cmd_list, int pos);
/*This is an altered version of the split to stop separating at a special
character. We can also make it so it can also complete all the structs instead
of just one*/
char		*mega_divider(char *content, int *pos);
char		*write_to_line(int count, char *content, int *pos);
int			ft_count_words(char *content, int pos);
int			find_next_stop(char *content, int pos);
t_special	pipe_selector(t_token *cmd_list, int *pos);
int			count_spaces(int *pos, char *content);
void		fill_cmds(t_token *cmd_list, int pipes);
void		pass_quotes(char *content, int *pos);
void		pass_spaces(char *content, int *pos);

/* ************************************************************************** */
/*                              OUT_SETUP_GENERAL                             */
/* ************************************************************************** */
/*discovers what type of command we have as the first argument  and returns 
the enum corresponding to it*/
t_builtin	get_builtin_id(const char *str);

/*gest the previous function working and seting the structure id of the comand
to the correct comand enum id flag*/
void		set_id_flag_cmd(char **cmd, t_builtin *id);

/*receives the struct t_comand as argument and will match execution
with its id flag*/
int			exec_correct_builtin(char **cmds, t_info info, \
t_builtin id, t_cmd_info cmd_info);
/*defines which function should run the commands sent. It receives the struct
where we can access the arrays of the commands */
void		commands_sorter(t_token *cmd_list, t_info info, t_localenv *local);
int			inter_executioner(t_token *cmd_list, t_info info, \
t_localenv *local, int i);
int			mult_cmd_executer(t_token *cmd_list, t_info info, \
t_localenv *local, int i);
int			waiter_function(t_token *cmd_list, int res);
int			pied_piper(t_token *cmd_list, int *fd, int i, int *stdin);
int			all_data_in_fork(char **final_cmds, t_info info, \
t_cmd_info	*cmd_info);

/* ************************************************************************** */
/*                                    ERRORS                                  */
/* ************************************************************************** */
/*Handle of all errors*/
void		errors(int error_code, char *cmd);
void		errors_2(int error_code, char *cmd);
int			wrong_syntax(char *total_line);
int			error_definer(char *cmd);

/* ************************************************************************** */
/*                                     FINEX                                  */
/* ************************************************************************** */

void		clean_cmd_list(t_token *cmd_list, char ***heredocs);
/*Handle the memory freeing of an array of strings*/
int			free_split(char **splitted);
int			tree_cleaner(t_token *cmd_list);

/* ************************************************************************** */
/*                                   STR_UTILS                                */
/* ************************************************************************** */

int			ignore_in_quotes(char *str, int pos);
int			ignore_spaces(char *str, int pos);
bool		is_special_char(char c);
bool		is_space(char c);
char		*ft_strcpy(char *s);
/*Creates a new node from the line read*/
t_token		*init_struct_cmd(void);

/*adds the node created to the linked list of tokens*/
void		add_token(t_token **tokens, t_token *new);

/* ************************************************************************** */
/*                                    HEREDOCS                                */
/* ************************************************************************** */

void		heredoc_writer(char *line_read, char ***heredocs, \
int i, t_localenv *local);
int			heredoc_counter(char *line_read, int i);
int			adjust_heredocs(t_heredocker heredocker, t_localenv *local);
void		add_newline_line(char **total_line, char *line_read);
void		add_heredocs(char ***new_hd, int cur_hd, \
t_heredocker hdoker, t_localenv *local);
void		add_partials(char **heredoc, char *str);
int			heredoc_creator(char ***new_heredocs, int *cur_heredocs, \
t_heredocker heredocker, t_localenv *local);
char		*ft_strjoin_2(char *s1, char const *s2);

/* ************************************************************************** */
/*                             PARSER_PARENTHESIS                             */
/* ************************************************************************** */

int			parser_parenthesis(char *total_line, int *i);
bool		check_operator_open_p(char *total_line, int *i, int k);
bool		check_open_p_operator(char *total_line, int *i);
bool		check_operator_closed_p(char *total_line, int *i);
bool		check_closed_p_operator(char *total_line, int *i);

/* ************************************************************************** */
/*                                   SOLVER                                   */
/* ************************************************************************** */

int			solver(char **final_cmds, t_info info, t_cmd_info *cmd_info);
int			cd_output_exec(char **cmds, t_info info, t_builtin id, \
t_cmd_info cmd_info);
int			define_input(t_command *cmds, int *fd, int *heredocs, int *in);
int			define_output(t_command *cmds, int *fd, int *out, int pos0);
char		*create_file_name(char *cmd, int *i);
char		**clean_cmds(t_command *full_cmds, t_localenv *local);
char		*clean_str(char *cmds, int i, int j);

/* ************************************************************************** */
/*                                   EXECVE                                   */
/* ************************************************************************** */

int			execve_heredoc(t_info info, char **cmds, t_localenv *local);

/*executes commands using the execve function*/
int			command_execve(char **cmds, t_localenv *local, \
t_info info, t_cmd_info cmd_info);
int			execve_doc(int fd_in, t_info info, char **cmds, \
t_localenv *local);
int			execve_decider(char **cmds, t_localenv *local, \
t_info info, t_cmd_info cmd_info);
char		*test_commands(char **cmds, char **p_path);
void		exec_not(char *cmd);
int			all_data_to_solver(char **final_cmds, t_info info, \
t_cmd_info	*cmd_info, t_command cmds);
void		cmd_info_starter(t_cmd_info	*cmd_info);
void		set_lastcommand(char **final_cmds, t_localenv *local);

/* ************************************************************************** */
/*                                  MEGASPLIT                                 */
/* ************************************************************************** */

char		**ft_split_ignore_quotes(char *s, char *c);
bool		check_condition(int pos, char *str);
void		command_exit(t_info info, char **cmds);
void		free_t_token(t_token *tok);
void		free_info_andenv(t_info info);
void		free_t_info(t_info info);

void		all_initial_free(char *pwd, char ***heredocs, \
t_localenv *local_env, int res);
void		read_to_line(char **total_line, \
char **line_read, int *fd);
int			writer_to_final(char **total_line, \
char **line_read, t_localenv *local);
bool		writer_from_input(char **total_line, \
char ***heredocs, t_localenv *local, int i);
int			error_definer_(int *err, int *pos, char *cmds);

/* ************************************************************************** */
/*                                  WILDUTILS7                                */
/* ************************************************************************** */

int			wild_words(char *s);
int			decidings(char *str, int k, char *new);
int			*check_wild_redirs(char *str, char **wild, char **new);
int			free_wild_split(char **splitted);
void		add_wildcard(char **wild, char *origin);

#endif