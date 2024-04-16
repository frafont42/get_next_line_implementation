int line_len(t_list *list)
{
        int len;
        int i;

        len = 0;
        while (list->next_node)
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
