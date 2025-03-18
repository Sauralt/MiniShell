/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:01:25 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/11 17:56:22 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define BUFFER_SIZE 1024
# define PATH_SIZE 1024

typedef struct s_stack
{
	char				*str;
	int					infile;
	int					outfile;
	int					id;
	struct s_stack		*prev;
	struct s_stack		*next;
}						t_stack;

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	t_stack	*cmd;
	t_stack	*meta;
	t_stack	*rand;
	t_token	*token;
	int		exit_code;
	int		fd[2];
	char	**env;
	char	prev_dir[PATH_SIZE];
}			t_shell;

int		main(int argc, char **argv, char **env);
int		init_tokens(t_shell *data, char *line);
t_token	*ft_new_token(char *content);
void	ft_add_token(t_token **s, t_token *new);
void	delfirst(t_token **s);
void	free_str(char **str);
char	*find_path(char *cmd, char **envp, int i);
t_stack	*ft_new_stack(t_token *t);
void	ft_add_stack(t_stack **s, t_stack *new);
void	delfirst_stack(t_stack **s);
int		init_stacks(t_shell *data);
void	free_tokens(t_token *t);
void	free_stack(t_stack *t);
void	handle_sigint(int sig);
bool	is_builtin(char *cmd);
void	exec_builtin(t_shell *data, t_token *cmd);
void	ft_cd(t_shell *data, char *path);
void	ft_pwd(void);
void	ft_env(void);
void	ft_echo(char *path);
int		ft_export(char *cmd);
void	ft_unset(char **cmd);
bool	execution(t_shell *data);

#endif