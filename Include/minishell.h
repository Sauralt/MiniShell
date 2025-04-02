/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:01:25 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/02 16:35:00 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "../ft_dprintf/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

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
t_token	*ft_new_token(t_shell *datam, char *content);
char	*ft_dollar(t_shell *data, char *str);
void	ft_add_token(t_token **s, t_token *new);
void	delfirst(t_token **s);
void	free_str(char **str);
char	*find_path(char *cmd, t_env *envp);
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
int		proc(t_shell *data);
int		execute(t_shell *data);
void	delfirst_stack(t_env **s);
void	ft_add_stack(t_env **s, t_env *new);
t_env	*ft_new_stack(char *t);
void	init_env(t_shell *data, char **env);
char	**make_env_str(t_env *env);
t_token	*add_param(t_shell *data, int i, char **str);
void	delone(t_shell *data, char *str);
void	check_meta_char(t_shell *data, int i);
void	strdup_param(t_token *t, int i, char **str, int count);
int		exec_abs(char **cmd, t_env *env);
void	parent_process(t_shell *data);
char	*ft_verif_str_type(t_shell *data, char *content);
char	**ft_quote(char **str);
char	**change_str(t_shell *data, char **str);
int		quote_len(char **str, char c, int i, int j);
int		skip(char **str, char c, int i, int j);
//int		change_j(char **str, char c, int i, int j);

#endif