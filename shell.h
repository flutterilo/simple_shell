#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


#define PROMPT "$ "
#define DELIM_PROMPT " \t"
extern char **environ;


/**
 * struct builtin_s - builtin command structure
 * @built: string command
 * @f: function to use it in command
 */

typedef struct builtin_s
{
	char *built;
	void (*f)(char **, char *);
} builtin_t;


/**
 * struct listint_s - singly linked list
 * @n: integer
 * @next: points to the next node
 * Description: singly linked list node structure
 */
typedef struct listint_s
{
	int n;
	struct listint_s *next;
} listint_t;


void parse_line(char **argv, char *line, size_t n, int command_count);
void print_char(char c);
void print_string(char *str);
int str_len(char *str);
char *_strdup(char *str);
char **tokenization(char *line);
int count_tokens(char *str_copy);
void execute_child(char **array_param, char **argv, int command_count);
char *_getenv(const char *name);
int is_exist(const char *file_name);
char *locate_path(const char *name);
char *join_strings(const char *first, const char *second, char sep);
int _strcmp(const char *s1, const char *s2);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_strcpy(char *dest, char *src);
void exit_built(char **array_param, char *line);
int built_in(char **array_param, char *line);
void env_built(char **array_param, char *line);
void print_int(int n);


void free_array_line(char **array_param, char *line);

#endif
