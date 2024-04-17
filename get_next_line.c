char *get_next_line.c(int fd)
{
	static t_list *list;
	char *next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &list, BUFFER_SIZE) < 0)
		return (NULL);
	list_maker(list, fd);
	store(next_line, list);
	cut(next_line);
	free_list(list);
	return (next_line);
}
