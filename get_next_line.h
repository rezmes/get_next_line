/*
** EPITECH PROJECT, 2026
** get_next_line
** File description:
** Header file for get_next_line project
*/

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 4096
#endif

char *get_next_line(int fd);
char *ft_strdup(const char *s);
char *ft_strjoin(char *s1, char *s2);
size_t ft_strlen(const char *s);
char *ft_strchr(const char *s, int c);

#endif /* GET_NEXT_LINE_H */
