/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:01:25 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/11 16:22:47 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_stack
{
	char				**str;
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
}			t_shell;

int		main(int argc, char **argv, char **env);
int		init_tokens(t_shell *data, char *line);
t_token	*ft_new_token(char *content);
void	ft_add_token(t_token **s, t_token *new);
void	delfirst(t_token **s);
void	free_str(char **str);
char	*find_path(char *cmd, char **envp, int i);
t_stack	*ft_new_stack(char *content);
void	ft_add_stack(t_stack **s, t_stack *new);
void	delfirst_stack(t_stack **s);

#endif