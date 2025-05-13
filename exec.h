#ifndef EXEC_H
# define EXEC_H

//-lreadline
//-lhistory
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <string.h>
# include <signal.h>

typedef struct	s_command	t_command;
typedef struct	s_redirect	t_redirect;
typedef struct	s_sh		t_sh;

typedef enum	e_redir_type
{
	IN, // <
	OUT, // >
	APPEND, // >>
	HEREDOC // <<
}			t_redir_type;

typedef struct s_redirect
{
	t_redir_type	type;
	char			*target; // nom du fichier ou delimiteur
	int 			fd; // apres redirection
	//t_redirect		next; ??

}			t_redirect;

typedef struct s_command
{
	char		*cmd_name;
	char		**args;
	t_redirect	*redirections;
	bool		is_builtin;
	t_command	*next;
}			t_command;

typedef struct s_sh
{
	char		**env;
	t_command	*cmd_list;
	char		*current_dir;
	int			exit_status;

}			t_sh;

char	*find_cmd_path(char *cmd, char **env);
int		execute_ast(t_command *cmd_list, t_sh *shell);
int		execute_command(t_command *cmd, char **env);
int		execute_pipeline(t_command *cmds, char **env);

int		setup_redirections(t_command *cmd, int fd);
int		restore_redirections(t_command *cmd, int fd);


bool	is_builtin(t_command *cmd, t_sh *shell, int fd);
int		execute_builtin(t_command *cmd, t_sh *shell, int fd);

char	*get_env_var(char *name, char **env); // generalisation de get_path() de pipex a tout type de var d'environnement

void	error_message(const char *msg);
void	free_array(char **array);
int		get_exit_status(void);

/*process*/

/*utils*/

/*builtins*/

#endif
