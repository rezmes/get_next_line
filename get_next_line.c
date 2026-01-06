/*
** EPITECH PROJECT, 2026
** get_next_line
** File description:
** Function that returns a line read from a file descriptor
*/

#include "get_next_line.h"

static char *extract_line(char *buffer) {
  char *newline;
  char *line;
  char *temp;
  size_t len;
  size_t i;

  newline = ft_strchr(buffer, '\n');
  if (!newline) {
    line = ft_strdup(buffer);
    buffer[0] = '\0';
    return (line);
  }
  len = newline - buffer + 1;
  line = malloc(len + 1);
  if (!line)
    return (NULL);
  i = 0;
  while (i < len) {
    line[i] = buffer[i];
    i++;
  }
  line[i] = '\0';
  temp = ft_strdup(newline + 1);
  if (!temp) {
    free(line);
    return (NULL);
  }
  i = 0;
  while (temp[i]) {
    buffer[i] = temp[i];
    i++;
  }
  buffer[i] = '\0';
  free(temp);
  return (line);
}

static int read_to_buffer(int fd, char *buffer, char *temp) {
  ssize_t bytes_read;
  size_t len;
  size_t i;

  bytes_read = read(fd, temp, BUFFER_SIZE);
  if (bytes_read < 0)
    return (-1);
  if (bytes_read == 0)
    return (0);
  len = ft_strlen(buffer);
  i = 0;
  while (i < (size_t)bytes_read) {
    buffer[len + i] = temp[i];
    i++;
  }
  buffer[len + i] = '\0';
  return (1);
}

char *get_next_line(int fd) {
  static char buffer[70000];
  char temp[BUFFER_SIZE + 1];
  char *line;
  int read_status;

  if (fd < 0 || BUFFER_SIZE <= 0)
    return (NULL);
  while (1) {
    if (ft_strchr(buffer, '\n'))
      return (extract_line(buffer));
    read_status = read_to_buffer(fd, buffer, temp);
    if (read_status < 0)
      return (NULL);
    if (read_status == 0) {
      if (buffer[0] == '\0')
        return (NULL);
      line = ft_strdup(buffer);
      buffer[0] = '\0';
      return (line);
    }
  }
  return (NULL);
}
