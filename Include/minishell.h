/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:01:25 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/17 15:39:06 by marvin           ###   ########.fr       */
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
	char	*cwd;
}			t_shell;

int		main(int argc, char **argv, char **env);
int		init_tokens(t_shell *data, char *line);
t_token	*ft_new_token(char *content);
void	ft_add_token(t_token **s, t_token *new);
void	delfirst(t_token **s);
void	free_str(char **str);
char	*find_path(char *cmd, char **envp, int i);
t_stack	*ft_new_stack(t_token *t);
void	ft_add_stack(t_stack **s, t_stack *new, int i);
void	delfirst_stack(t_stack **s);
int		init_stacks(t_shell *data);
void	free_tokens(t_token *t);
void	free_stack(t_stack *t);
void	handle_sigint(int sig);
bool	is_builtin(char *cmd);
void	exec_cmd(char *line);
void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_env(void);
void	ft_echo(char **cmd);
void	free_all(t_shell *data, char *line);
int		proc(t_shell *data);
int		execute(t_shell *data);

#endif