/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:09:13 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 14:25:06 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_localenv
{
	char	**content;
	char	**sorted;
}				t_localenv;

typedef struct s_lstexpand
{
	int					status;
	char				*content;
	struct s_lstexpand	*next;
}				t_lstexpand;

/* ************************************************************************** */
/*                                    BUILTINS                                */
/* ************************************************************************** */

int			command_pwd(t_localenv *local_env);
void		print_string_array(char **strings);
void		prtstr_arr_env(char **strings);
int			command_env(t_localenv *local);
int			unset_variable(const char *variable, t_localenv *local);
int			command_unset(char **cmds, t_localenv *local);
bool		variable_name_check(const char *var);

/* ************************************************************************** */
/*                                   EXPANDER.c                               */
/* ************************************************************************** */

char		*get_ds_code(char *cmd);
char		*ds_replace_codeword(char *cmd, char *code, char *env_val);
char		*expand_single_variable(char *cmd, t_localenv *local);
char		*join_list_contents(t_lstexpand *head);
void		clean_quotes_in_list(t_lstexpand *head, int len);

/* ************************************************************************** */
/*                                 EXPANDER_LST.c                             */
/* ************************************************************************** */

void		insert_lstexpand_node(t_lstexpand **head, t_lstexpand *new_node);
void		free_lstexpand(t_lstexpand *head);
void		create_list_quotes(char *cmd, t_lstexpand **in_cmd_list);
void		expand_content_in_list(t_lstexpand *head, t_localenv *local);

t_lstexpand	*create_node_lstexpand(int status, char *content);

/* ************************************************************************** */
/*                                 EXPANDER_UTILS.c                           */
/* ************************************************************************** */

bool		is_str_empty(char *str);
int			quotes_counter(char *cmd);
char		*ft_strndup(const char *s, size_t n);
int			quotation_size(char *cmd, int start);
void		print_list(t_lstexpand *head);

/* ************************************************************************** */
/*                                 EXPANDER_MAIN.c                            */
/* ************************************************************************** */

char		*master_expander(char *cmd, t_localenv *local);
char		*master_expander_out(char *cmd, t_localenv *local);
char		*expander_heredocs(char *cmd, t_localenv *local);

/* ************************************************************************** */
/*                                  CD_COMMAND.C                              */
/* ************************************************************************** */

int			change_directory(const char *path);
char		*get_home_directory(t_localenv *local);
char		*get_previous_directory(t_localenv *local);
int			update_directories(t_localenv *local, char *cwd);
int			command_cd(char **cmds, t_localenv *local, int err);

/* ************************************************************************** */
/*                                  CD_UTILS.C                                */
/* ************************************************************************** */

void		*ft_realloc(void *ptr, size_t size);
int			add_env_variable(char *name, char *value, t_localenv *local);
int			update_env_variable(char *name, char *value, t_localenv *local);
int			ft_setenv(char *name, char *value, t_localenv *local);

/* ************************************************************************** */
/*                                     ECHO.C                                 */
/* ************************************************************************** */

/* returns true everytime it finds -n or -n 
folowed by n n_times else returns false*/
bool		ft_find_n(char *str);
int			command_echo(char **cmds);

/* ************************************************************************** */
/*                                 EXPORT.c                                   */
/* ************************************************************************** */

char		*extract_variable_name(const char *variable);
char		**copy_environment(char **old_env, int num_vars);
int			command_export(char **cmds, t_localenv *local);
int			update_variable(const char *variable, t_localenv *local);
int			add_variable(const char *variable, t_localenv *local);
int			update_var_cont(const char *variable, t_localenv *local);
int			add_var_cont(const char *variable, t_localenv *local);

/* ************************************************************************** */
/*                                EXPORT_UTILS.c                              */
/* ************************************************************************** */

// void		ft_free_str_array(char **ar_str); apagada!!!!
int			find_variable_index_recursive(const char *name, \
char **env, int index);
int			find_variable_index(const char *variable, char **env);
char		*ft_strncpy(char *dst, const char *src, size_t n);
void		*ft_memalloc(size_t size);

/* ************************************************************************** */
/*                               EXPORT_ENVCPY.c                              */
/* ************************************************************************** */

t_localenv	*env_init(char **envirion);
void		copy_env_var_utils(char **env, int num_vars, char **env_copy);
char		**copy_environment_variables(char **environ);
int			print_sorted_strings(char **sorted);
void		put_quotes_expdr(char **arrstr);
void		sort_strings(char **strings, int i, int j, int k);

/* ************************************************************************** */
/*                             EXPORT_UTILS_SORT.c                            */
/* ************************************************************************** */

size_t		ft_strarrlen(char **arr);
char		**ft_strarrdup(char **src);
void		print_next_string(char **str);
void		swap_strings(char **str1, char **str2);

/* ************************************************************************** */
/*                                 FT_GETENV.c                                */
/* ************************************************************************** */

char		*ft_getenv(const char *name, char **envp);

/* ************************************************************************** */
/*                                 EXIT_COMMAND.c                             */
/* ************************************************************************** */

int			command_printenv(char **cmds, t_localenv *local);
int			bi_err(char *str1, char *str2, char *str3);
bool		isvar_valid(const char *name);
int			ex_code(int code);
char		*ft_env_getenv(char *env, char *code_w, t_localenv *local);
char		*ft_env_itoa(char *env);

#endif