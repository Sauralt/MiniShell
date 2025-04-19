/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:01:25 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/18 15:28:04 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdarg.h>

# define BUFFER_SIZE 1024
# define PATH_SIZE 1024

typedef struct s_token
{
	int				type;
	char			**str;
	int				infile;
	int				outfile;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*str;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	char	prev_dir[PATH_SIZE];
	t_token	*token;
	int		exit_code;
	int		fd[2];
	int		del_num;
	t_env	*env;
}			t_shell;

int		main(int argc, char **argv, char **env);
int		init_tokens(t_shell *data, char *line);
int		parsing(t_shell *data, char *line);
void	init_list_tok(t_shell *data, char *str, int flag);
int		set_token_type(t_shell *data, char *str);
void	check_meta_char(t_shell *data, t_token *t);
void	heredoc(t_shell *data, char *delimiter);
t_token	*add_param(t_shell *data, t_token *t);
t_token	*ft_new_token(t_shell *data, char *content, int flag);
char	*ft_dollar(t_shell *data, char *str);
void	ft_add_token(t_token **s, t_token *new);
void	delfirst(t_token **s);
void	delone(t_shell *data, t_token *t);
char	*find_path(char *cmd, t_env *envp);
t_env	*find_env(t_env *env, const char *key);
int		init_stacks(t_shell *data);
void	free_tokens(t_token *t);
void	handle_sigint(int sig);
bool	is_builtin(char *cmd);
void	exec_cmd(char *line);

void	ft_cd(t_shell *data, t_token *str);
int		ft_pwd(t_shell *data);
int		ft_env(t_shell *data);
int		ft_echo(t_shell *data, t_token *str);
int		ft_unset(t_shell *data, t_token *str);
int		ft_export(t_shell *data, t_token *str);
int		ft_exit(t_shell *data, t_token *str);

void	free_all(t_shell *data, char *line);
void	free_env(t_env *env);
void	free_str(char **str);
void	ft_close(int *fd);

int		proc(t_shell *data);
int		execute(t_shell *data);

void	delfirst_stack(t_env **s);
void	ft_add_stack(t_env **s, t_env *new);
t_env	*ft_new_stack(char *t);
void	init_env(t_shell *data, char **env);
char	**make_env_str(t_env *env);

int		exec_abs(char **cmd, t_env *env);
char	**re_split(t_shell *data, char **str);
char	**change_str(t_shell *data, char **str);
char	*ft_verif_str_type(t_shell *data, char *content);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
int		is_valid_var_char(char c);
int		check_str(char *str);
char	**change_result(t_shell *data, char **result, char **new_result);
char	**change_env_var(t_shell *data, char **str, char **result);
char	**init_str(t_shell *data, char *line);
int		exec(t_shell *data, t_token *t);

int		ft_dprintf(int fd, const char *f, ...);
int		ft_printhex(int fd, char c, int l, unsigned int a);
int		ft_printint(int fd, int l, int a);
int		ft_printptr(int fd, int t, int l, void *a);
int		ft_printstring(int fd, int l, char *a);
int		ft_printuns(int fd, int l, unsigned int a);

#endif