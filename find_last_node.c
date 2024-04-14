t_list *find_last_node(t_list **list)
{
	if (!list)
		return (NULL);
	else
		while (list->next_node)
			*list = list->next_node;
	return (list);
}
