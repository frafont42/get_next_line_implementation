// #include "get_next_line.h"

// int check_nl(char *str)
// {
// 	int i;

// 	i = 0;
// 	if (str == NULL || *str == '\0')
// 		return (0);
//         while(str[i])
//         {
//                 if (str[i] == '\n')
//                         return (1);
//                 i++;
//         }
//         return (0);
// }

// t_list *find_last_node(t_list *list)
// {
//         if (!list)
//                 return (NULL);
//         else
//                 while (list->next_node)
//                         list = list->next_node;
//         return (list);
// }

// void free_list(t_list **list, char *str)
// {
//         t_list *z;

//         while (*list)
//         {
//                 z = (*list)->next_node;
//                 free((*list)->buffer);
// 		free(*list);
//                 *list = z;
//         }
//         *list = NULL;
//         if (str)
//         {
//                 (*list)->buffer = str;
//                 (*list)->next_node = NULL;
//         }
//         else
//                 free(str);
// }

// int line_len(t_list *list)
// {
//         int len;
//         int i;

//         len = 0;
// 	if (list == NULL)
// 		return (0);
// 	if (list->next_node == NULL)
// 		return (0);
//         while (list)
//         {
// 		if (list->buffer)
// 		{	
// 			i = 0;
//                 	while (list->buffer[i] != '\0')
//                 	{
//                         	len++;
//                         	i++;
//                 	}
// 		}
//                 list = list->next_node;
//         }
//         return (len);
// }

// char *cut(char *str)
// {
//         int i;
//         int j;
//         char *right_str;

//         i = 0;
//         j = 0;
//         while (str[i] != '\n')
//                 i++;
//         right_str = (char *)malloc(sizeof(char) * (i + 1));
//         while (str[j])
//         {
//                 right_str[j] = str[j];
//                 if (str[j] == '\n')
//                 {
//                         j++;
//                         break;
//                 }
//                 j++;
//         }
//         right_str[j] = '\0';
//         return (right_str);
// }

