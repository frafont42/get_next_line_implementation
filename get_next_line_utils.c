#include "get_next_line.h"

t_list	*find_last_node(t_list *list)
{
	t_list	*current;

	if (!list)
	{
		return (NULL);
	}
	current = list;
	while (current->next)
	{
		current = current->next;
	}
	return (current);
}

int	check_nl(t_list *list)
{
	int	i;

	i = 0;
	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->string[i] && i < BUFFER_SIZE)
		{
			if (list->string[i] == '\n' || list->string[i] == '\0')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	concatenate(t_list **list, char *str)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = (t_list *)malloc(sizeof(t_list));
	new_node->string = str;
	new_node->next = NULL;
	if ((*list) == NULL)
	{
		(*list) = new_node;
		return ;
	}
	else
		last_node->next = new_node;
}

int	line_len(t_list *list)
{
	int	len;
	int	i;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->string[i])
		{
			if (list->string[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

void	free_list(t_list **list, t_list *first_node, char *str)
{
	t_list	*z;

	while (*list)
	{
		z = (*list)->next;
		free((*list)->string);
		free((*list));
		(*list) = z;
	}
	*list = NULL;
	if (first_node->string[0])
	{
		(*list) = first_node;
	}
	else
	{
		free(str);
		free(first_node);
	}
}
