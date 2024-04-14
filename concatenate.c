void concatenate(t_list **list, char *str)
{
	t_list *new_node;
	t_list *last node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	last_node = find_last_node(list);
	if (last_node == NULL)
	{
		new_node->buffer = str;
		new_node->next_node = NULL;
		last_node->next_node = new_node;
		return ;
	}
	new_node->buffer = str;
	new_node->next_node = NULL;
	last_node->next_node = new_node;
}
