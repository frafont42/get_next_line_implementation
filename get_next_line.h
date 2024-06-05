#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H 
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 41
# endif

typedef struct s_list
{
	char			*string;
	struct s_list	*next;
}	t_list;

t_list	*find_last_node(t_list *list);
int		check_nl(t_list *list);
void	concatenate(t_list **list, char *str);
void	list_maker(t_list **list, int fd);
int		line_len(t_list *list);
char	*join_list(t_list *list);
void	free_list(t_list **list, t_list *first_node, char *str);
void	prepare_next_list(t_list **list);
char	*get_next_line(int fd);

#endif