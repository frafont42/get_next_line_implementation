#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
	char *buffer;
	struct s_list *next_node;
} t_list;

int line_len(t_list *list)
{
	int len;
	int i;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->buffer[i] != '\0')
		{
			len++;
			i++;
		}
		list = list->next_node;
	}
	return (len);
}

char *join_list(t_list *list)
{
	char *line;
	int len;
	int i;
	int j;

	len = line_len(list);
	printf("%d\n", len);
	i = 0;
	line = (char *)malloc(sizeof(char) * len + 1);
	if (!line)
		return (NULL);
	while (list)
	{
		j = 0;
		while (list->buffer[j])
		{
			line[i] = list->buffer[j];
			i++;
			j++;
		}
		list = list->next_node;
	}
	line[i] = '\0';
	return (line);
}

int main()
{
	t_list *n1;
	t_list *n2;
	t_list *n3;
	t_list *n4;
	t_list *head;
	char *str;

	n1 = (t_list *)malloc(sizeof(t_list));
	n2 = (t_list *)malloc(sizeof(t_list));
	n3 = (t_list *)malloc(sizeof(t_list));
	n4 = (t_list *)malloc(sizeof(t_list));

	n1->buffer = "ciao";
	n2->buffer = "sono";
	n3->buffer = "francesco";
	n4->buffer = "bella";

	n1->next_node = n2;
	n2->next_node = n3;
	n3->next_node = n4;
	n4->next_node = NULL;
	head = n1;

	str = join_list(head);

	free(n1);
	free(n2);
	free(n3);
	free(n4);

	printf("%s\n", str);
}
