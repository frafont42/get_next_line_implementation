#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int check_nl(char *str)
{
        int i;

        i = 0;
        if (str == NULL || *str == '\0')
                return (0);
        while(str[i])
        {
                if (str[i] == '\n')
                        return (1);
                i++;
        }
        return (0);
}

t_list *find_last_node(t_list *list) {
    if (list == NULL) {
        write(1, "fln2\n", 5);
        return NULL;
    }
    t_list *current;
    current = list;
    while (current->next_node != NULL) {
        current = current->next_node;
    }
    return current;
}

void free_list(t_list *list, char *str)
{
        t_list *z;

        while (list)
        {
                z = list->next_node;
                free(list->buffer);
                free(list);
                list = z;
        }
        list = NULL;
        if (str)
        {
                list->buffer = str;
                list->next_node = NULL;
        }
        else
                free(str);
}

int line_len(t_list *list)
{
        int len;
        int i;

        len = 0;
	printf("prima degli if di linelen");
        if (list == NULL)
                return (0);
        if (list->next_node == NULL)
                return (0);
	printf("prima del while di linelen");
        while (list)
        {
                if (list->buffer)
                {
                        i = 0;
                        while (list->buffer[i] != '\0')
                        {
                                len++;
                                i++;
                        }
                }
                list = list->next_node;
        }
        return (len);
}

char *cut(char *str)
{
        int i;
        int j;
        char *right_str;

        i = 0;
        j = 0;
        while (str[i] != '\n')
                i++;
        right_str = (char *)malloc(sizeof(char) * (i + 1));
        while (str[j])
        {
                right_str[j] = str[j];
                if (str[j] == '\n')
                {
                        j++;
                        break;
                }
                j++;
        }
        right_str[j] = '\0';
        return (right_str);
}

t_list* list_maker(int fd)
{
        char *string_buffer;
        int char_read;
        t_list* list = (t_list *)malloc(sizeof(t_list));
        list->next_node = NULL;
        list->buffer = NULL;
        string_buffer = NULL;
        int found_newline = 0;
	int i = 0;
        while (found_newline==0)
        {
                string_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
                if (!string_buffer)
                        return NULL ;
                char_read = read(fd, string_buffer, BUFFER_SIZE);
                if (!char_read)
                {
                        free(string_buffer);
                        return NULL;
                }
                string_buffer[char_read] = '\0';
                i = 0;
		while (i < char_read)
		{
			if (string_buffer[i] == '\n')
				found_newline = 1;
			i++;
		}
                concatenate(list, string_buffer);
                free(string_buffer);
        }
        return list;
}

char *join_list(t_list *list)
{
        char *line;
        int len;
        int i;
        int j;

        len = line_len(list);
        i = 0;
        line = (char *)malloc(sizeof(char) * (len + 1));
        if (!line)
                return (NULL);
	printf("prima del while di joinlist");
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

void make_next_list(t_list *list)
{
    t_list *last_node;
    char *first_buffer;
    int i;
    int j;

    i = 0;
    j = 0;
    last_node = find_last_node(list);
    first_buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    while(last_node->buffer[i] && last_node->buffer[i] != '\n')
        i++;
    if (last_node->buffer[++i])
    {
        while (last_node->buffer[i])
        {
            first_buffer[j] = last_node->buffer[i];
            i++;
	    j++;
        }
        first_buffer[j] = '\0';
    }
    free_list(list, first_buffer);
}

void concatenate(t_list *list, char *str)
{
        t_list *new_node;
        t_list *last_node;

        if(list->buffer==NULL){
                list->buffer = (char*)malloc(sizeof(char)*(BUFFER_SIZE + 1));
                int i = 0;
                while(str[i]!= '\0'){
                        list->buffer[i] = str[i];
                        i++;
                }
                list->next_node = NULL;
        }
        else{
                new_node = (t_list *)malloc(sizeof(t_list));
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
                new_node->buffer = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1));
                int i = 0;
                while(str[i]!= '\0'){
                        new_node->buffer[i] = str[i];
                        i++;
                }
                new_node->next_node = NULL;
                last_node->next_node = new_node;
        }
}

char *get_next_line(int fd)
{
        static t_list *list;
        char *next_line;

	list = (t_list *)malloc(sizeof(t_list));
        if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &list, BUFFER_SIZE) < 0)
                return (NULL);
        list = list_maker(fd);
	if (list == NULL)
		return (NULL);
        next_line = join_list(list);
        next_line = cut(next_line);
        make_next_list(list);
        return (next_line);
}

int main()
{
	char *str;
	int fd = open("file.txt", O_RDONLY);

	str = get_next_line(fd);
	printf("%s\n", str);
}
