#include "get_next_line.h"

void	list_maker(t_list **list, int fd)
{
	char	*buffer;
	int		char_read;

	while (!check_nl(*list))
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[char_read] = '\0';
		concatenate(list, buffer);
	}
}

char	*join_list(t_list *list)
{
	char	*line;
	int		len;
	int		i;
	int		j;

	i = 0;
	len = line_len(list);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	while (list)
	{
		j = 0;
		while (list->string[j])
		{
			if (list->string[j] == '\n')
			{
				line[i++] = list->string[j];
				break ;
			}
			line[i++] = list->string[j++];
		}
		list = list->next;
	}
	return (line[i] = '\0', line);
}

void	prepare_next_list(t_list **list)
{
	t_list	*last_node;
	t_list	*first_node;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return ;
	first_node = (t_list *)malloc(sizeof(t_list));
	if (!first_node)
		return ;
	last_node = find_last_node((*list));
	while (last_node->string[i] && last_node->string[i] != '\n')
		i++;
	if (last_node->string[i] == '\n')
		i++;
	while (last_node->string[i])
		str[j++] = last_node->string[i++];
	str[j] = '\0';
	first_node->string = str;
	first_node->next = NULL;
	free_list(list, first_node, str);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*line;

	if (BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	list_maker(&list, fd);
	if (list == NULL)
		return (NULL);
	line = join_list(list);
	prepare_next_list(&list);
	return (line);
}
