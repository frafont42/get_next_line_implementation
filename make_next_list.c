void make_next_list(t_list **list)
{
    t_list *last_node;
    t_list *next_1st_node;
    char *first_buffer;

    last_node = find_last_node(list);
    next_1st_node = malloc(sizeof(t_list));
    while(last_node->buffer[i] && last_node->buffer[i]!= '/n')
        i++;
    if (last_node->buffer[++i])
    {
        while (last_node->buffer[i])
        {
            first_buffer = last_node->buffer[i];
            i++;
        }
    }
    next_1st_node->buffer = first_buffer;
    next_1st_node->next_node = NULL;
    free_list;
}