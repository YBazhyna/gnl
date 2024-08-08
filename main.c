#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int fd;
    //char *line;
    int fd2;

    if (argc != 3)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return (1);
    }

    fd = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }
    if (fd2 < 0)
    {
        perror("Error opening file");
        return (1);
    }

   /*  while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    } */
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd2));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd2));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd2));

    close(fd);
    close(fd2);
    return (0);
}
