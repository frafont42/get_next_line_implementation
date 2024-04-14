char *join_list(t_list **list)
{
	char *line;
	int len;
	int i;

	len = line_len(list);
	i = 0;
	line = malloc(sizeof(char) * len + 1);
	while (list->next_node)
	{
		j = 0;
		while (list->buffer)
		{
			line[i] = list->buffer[j];
			i++;
			j++;
		}
		list = list->next_node;
	}
}

