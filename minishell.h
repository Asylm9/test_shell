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

typedef struct s_redirect	t_redirect;
typedef struct s_command	t_command;
typedef struct s_sh		    t_sh;

typedef enum e_redir_type
{
	IN,      // <
	OUT,     // >
	APPEND,  // >>
	HEREDOC  // <<
}			t_redir_type;

typedef struct s_redirect
{
	t_redir_type	type;
	char			*target; // file name or delimiter
	int 			fd;      // after redirection?
	t_redirect		*next;   // next redirection
}			t_redirect;

typedef struct s_command
{
	char		*cmd_name;
	char		**args;
	t_redirect	*redirections;
	t_command	*next;
}			t_command;

typedef struct s_sh
{
	char		**env;
	t_command	*cmd_list;
	char		*current_dir;
	int			exit_status;
}			t_sh;

/* execution */
int		execute(t_command *cmd_list, t_sh *shell);
int		execute_command(t_command *cmd, t_sh *shell);
int		execute_pipeline(t_command *cmds, t_sh *shell);
int		execute_external_command(t_command *cmd, char **env);

/* Path and environment handling */
char	*get_env_var(char *name, char **env);
char	*find_cmd_path(char *cmd, char **env);

/* Redirections */
int		apply_redirections(t_command *cmd);
int		setup_heredoc(t_redirect *redir);

/* Pipe handling */
void	get_pipe_count(t_command *cmd_list, int *nb_pipes);
int		**create_pipes(int nb_pipes);
void	close_pipes(int **pipes, int nb_pipes);

/* Builtin commands */
bool	is_builtin(char *cmd_name);
int		execute_builtin(t_command *cmd, t_sh *shell);

/* Builtin implementations */
int		builtin_echo(char **args, t_sh *shell);
int		builtin_cd(char **args, t_sh *shell);
int		builtin_pwd(t_sh *shell);
int		builtin_export(char **args, t_sh *shell);
int		builtin_unset(char **args, t_sh *shell);
int		builtin_env(t_sh *shell);
int		builtin_exit(char **args, t_sh *shell);

/* Utils */
void	error_message(const char *msg);
void	free_array(char **array);
//char	*ft_strdup(const char *s);
//char	**ft_split(const char *s, char c);
//char	*ft_strjoin(const char *s1, const char *s2);
//int		ft_strcmp(const char *s1, const char *s2);
//int		ft_strncmp(const char *s1, const char *s2, size_t n);
//size_t	ft_strlen(const char *s);
//void	ft_putendl_fd(const char *s, int fd);

#endif