#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	clean_list(t_list **list, t_list *new_head, char *buffer)
{
	t_list	*temp;

	if (!*list)
		return ;
	while (*list)
	{
		temp = (*list)->next_node;
		free((*list)->buffer);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (new_head->buffer[0])
		(*list) = new_head;
	else
	{
		free(buffer);
		free(new_head);
	}

}

// int check_nl(char *str)
// {
//         int i;

//         i = 0;
//         if (str == NULL || *str == '\0')
//                 return (0);
//         while(str[i])
//         {
//                 if (str[i] == '\n')
//                         return (1);
//                 i++;
//         }
//         return (0);
// }

t_list *find_last_node(t_list *list) {
    if (list == NULL)
    {
        // write(1, "fln2\n", 5);
        return NULL;
    }
    t_list *current;
    current = list;
    while (current->next_node != NULL) {
        current = current->next_node;
    }
    return current;
}

void free_list(t_list **list)
{
        t_list	*temp;

	if (!*list)
		return ;
	while (*list)
	{
		temp = (*list)->next_node;
		free((*list)->buffer);
		free(*list);
		*list = temp;
	}
	*list = NULL;
}

int line_len(t_list *list)
{
        int len;
        int i;

        len = 0;
        if (list == NULL)
                return (0);
        // if (list->next_node == NULL)
        //         return (0);
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
        while (str[i] != '\n' && str[i])
                i++;
        right_str = (char *)malloc(sizeof(char) * (i + 1));
        while (str[j])
        {
                right_str[j] = str[j];
                if (str[j] == '\n')
                {
                        j++; //ritorna la riga con il /n
                        break;
                }
                j++;
        }
        right_str[j] = '\0';
        return (right_str);
}

void list_maker(t_list **list, int fd)
{
        char *string_buffer;
        int char_read;
        //t_list *list = (t_list *)malloc(sizeof(t_list));
        // 
        string_buffer = NULL;
        int found_newline = 0;
	int i = 0;
        while (found_newline==0 )
        {
                string_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
                if (!string_buffer)
                        return ;
                char_read = read(fd, string_buffer, BUFFER_SIZE);
                // printf("%d\n", char_read);
                if (!char_read)
                {
                        free(string_buffer);
                        free_list(list);
                        return ;
                }
                string_buffer[char_read] = '\0';
                i = 0;
		while (i < char_read)
		{
			if (string_buffer[i] == '\n')
				found_newline = 1;
			i++;
                        if (string_buffer[i] == '\0')
                                found_newline = 1;
		}
                // printf("buffer: %s\tlist: %p\n", string_buffer, list);
                // printf("nl %d\n", found_newline);
                concatenate(list, string_buffer);
                //free(string_buffer);
        }
        return ;
}

char *join_list(t_list *list)
{
        char *line;
        int len;
        int i;
        int j;

        // printf("Join_list inside\n");
        len = line_len(list);
        i = 0;
        line = (char *)malloc(sizeof(char) * (len + 1));
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

void make_next_list(t_list **list)
{
    t_list *last_node;
    t_list *first_next_node;

    char *first_buffer;
    int i;
    int j;

    i = 0;
    j = 0;
    last_node = find_last_node(*list);
    first_next_node = (t_list *)malloc(sizeof(t_list));
    first_buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    while (last_node->buffer[i] && last_node->buffer[i] != '\n')
        i++;
    if (last_node->buffer[i]) // Found a newline, create next list node
    {
        i++; // Skip the newline character
        while (last_node->buffer[i])
        {
            first_buffer[j] = last_node->buffer[i];
            i++;
            j++;
        }
        first_buffer[j] = '\0';
        first_next_node->buffer = first_buffer;
        first_next_node->next_node = NULL;
        clean_list(list, first_next_node, first_buffer);
    }
}

void concatenate(t_list **list, char *str)
{
        t_list *new_node;
        t_list *last_node;

        new_node = malloc(sizeof(t_list));
        new_node->buffer = str;
        new_node->next_node = NULL;
        last_node = find_last_node(*list);
        if (!last_node)
                *list = new_node;
        else
                last_node->next_node = new_node;

        // printf("concatenate: %s\n", new_node->buffer);
        // printf("concatenate list: %p\n", *list);


        // if(list->buffer==NULL){
        //         list->buffer = (char*)malloc(sizeof(char)*(BUFFER_SIZE + 1));
        //         int i = 0;
        //         while(str[i]!= '\0'){
        //                 list->buffer[i] = str[i];
        //                 i++;
        //         }
        //         list->next_node = NULL;
        // }
        // else{
        //         new_node = (t_list *)malloc(sizeof(t_list));
        //         if (!new_node)
        //                 return ;
        //         last_node = find_last_node(list);
        //         if (last_node == NULL)
        //         {
        //                 new_node->buffer = str;
        //                 new_node->next_node = NULL;
        //                 last_node->next_node = new_node;
        //                 return ;
        //         }
        //         new_node->buffer = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1));
        //         int i = 0;
        //         while(str[i]!= '\0'){
        //                 new_node->buffer[i] = str[i];
        //                 i++;
        //         }
        //         new_node->next_node = NULL;
        //         last_node->next_node = new_node;
        // }
}

char *get_next_line(int fd)
{
        static t_list *list;
        char *next_line;

        if (fd < 0 || BUFFER_SIZE <= 0)
                return (NULL);
        list_maker(&list, fd);
        // printf("list: %p\n", list);
	if (list == NULL)
        {
		return (NULL);
        }
        // printf("join_list call\n");
        next_line = join_list(list);
        printf("next line is: %s\n", next_line);
        next_line = cut(next_line);
        printf("cut line: %s\n", next_line);
        t_list *current_node = list;
        make_next_list(&list);
        return (next_line);
}


// int main()
// {
//     int fd = open("file.txt", O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Errore nell'apertura del file");
//         return 1;
//     }

//     char *line;
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("RISULTATO GNL: %s\n", line);
//         free(line); // Liberiamo la memoria allocata per la linea
//     }

//     close(fd);
//     return 0;
// }

int main()
{
        int fd = open("file.txt", O_RDONLY);
        char *str = get_next_line(fd);
        printf("RISULTATO GNL: %s\n", str);
        str = get_next_line(fd);
        printf("RISULTATO GNL: %s\n", str);
        str = get_next_line(fd);
        printf("RISULTATO GNL: %s\n", str);
}