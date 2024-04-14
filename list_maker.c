typedef struct s_list
{
        char *buffer;
        struct s_list *next_node;
} t_list

void list_maker(t_list list, int fd)
{
	char *string_buffer;
	int char_read;

	string_buffer = NULL;
	while (check_nl(string_buffer) == 0)
	{
		string_buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
		char_read = read(fd, string_buffer, BUFFER_SIZE);
		string_buffer[char_read] = '\0';
		concatenate(list, string_buffer);
	}
	return ;
}
