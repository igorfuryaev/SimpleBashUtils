#ifndef SRC_S21_CAT_H_
#define SRC_S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flags {
  int b;
  int e;
  int s;
  int t;
  int n;
  int v;
} t_flag;

int parser_f(int argc, char **argv, t_flag *flag);
void open_file(char *file_name, const int cases[10]);
int read_file(char **argv, t_flag *flag, int i);

#endif
