#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 7
#endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

typedef struct s_list
{
	char *buffer;
	struct s_list *next_node;
}	t_list;

int check_nl(char *str);
t_list *find_last_node(t_list **list);
void free_list(t_list **list, char *str);
int line_len(t_list *list);
char *cut(char *str);
t_list *list_maker(int fd);
char *join_list(t_list *list);
void make_next_list(t_list **list);
void concatenate(t_list **list, char *str);
char *get_next_line(int fd);

#endif
