/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:01:25 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/06 16:33:08 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	char	**cmd;
	int		infile;
	int		outfile;
	cmd		*prev;
	cmd		*next;
}			t_cmd;

typedef struct s_token
{
	int		type;
	char	*token;
	t_token	*prev;
	t_token	*next;
}			t_token;


typedef struct s_hist
{
	char	*typed;
	t_hist	*prev;
	t_hist	*next;
}			t_hist;

typedef struct s_shell
{
	t_hist	*hist;
	t_cmd	*cmd;
	t_token	*token;
	int		exit_code;
	int		fd[2];
	char	**env;
}			t_shell;

int		main(int argc, char **argv, char **env);
int		init_tokens(t_shell *data, char *line);
void	set_token_type(t_shell *data, char *line, int type);
t_token	*ft_stacknew(char *content);
void	ft_stackadd(t_token **s, t_token *new);
void	delfirst(t_stack **s);

#endif