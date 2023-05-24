#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <signal.h>
#define PROMPT "$ "


/**
 * struct builtin_d - Represents a built-in command
 * @built: Name of the built-in command
 * @f: Function pointer to the corresponding built-in function
 */
typedef struct builtin_d
{
	char *built;
	void (*f)(char *);
} builtin_t;

extern char **environ;

void parse_line(char *line, size_t n, int command_count, char **argv);
char **tokenization(char *line, const char *delim, int token_count);
int count_token(char *line, const char *delim);
char **tokenize_line(int token_count, char *line, const char *delim);
void create_child(char **param_array, char *line, int count, char **argv);
char *find_path_command(char *command);
int str_len(char *str);
int find_path(char *str);
char **tokenize_path(int index, char *str);
char *search_directories(char **path_tokens, char *command);
char *build_path(char *directory, char *command);
void free_array(char **arr);
void free_f(int n, ...);

int built_in(char **command, char *line);
void (*check_builtin(char *str))(char *str);
void env_function(__attribute__((unused))char *line);
void exit_function(char *line);
void cd_function(char *line);

int _strcmp(char *s1, char *s2);
char *_strdup(char *src);
void print_string(char *str, int new_line);
void print_int(int n);
int print_char(char c);

void printing_error(char *av, int count, char *command);
void error_execute(char *av, int count, char *tmp_command);

#endif
