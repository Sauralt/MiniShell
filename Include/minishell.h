/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:01:25 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/18 16:28:31 by cfleuret         ###   ########.fr       */
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

// typedef struct s_stack
// {
// 	char				*str;
// 	int					infile;
// 	int					outfile;
// 	int					id;
// 	struct s_stack		*prev;
// 	struct s_stack		*next;
// }						t_stack;

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	// t_stack	*stack;
	t_token	*token;
	int		exit_code;
	int		fd[2];
	char	**env;
}			t_shell;

int		main(int argc, char **argv, char **env);
int		init_tokens(t_shell *data, char *line);
t_token	*ft_new_token(char *content);
void	ft_add_token(t_token **s, t_token *new);
void	delfirst(t_token **s);
void	free_str(char **str);
char	*find_path(char *cmd, char **envp, int i);
int		init_stacks(t_shell *data);
void	free_tokens(t_token *t);
void	handle_sigint(int sig);
bool	is_builtin(char *cmd);
void	exec_cmd(char *line);
int		ft_cd(char *path);
int		ft_pwd(t_shell *data);
int		ft_env(void);
int		ft_echo(char **cmd);
void	free_all(t_shell *data, char *line);
int		proc(t_shell *data);
int		execute(t_shell *data);

#endif