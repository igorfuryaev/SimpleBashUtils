#ifndef SRC_GREP_S21_CAT_H_
#define SRC_GREP_S21_CAT_H_

#include <errno.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 1024

#define EQ_OR |=
#define EQUAL &

enum {
  OPTBIT_D = 0,
  OPTBIT_E = 0,
  OPTBIT_I,
  OPTBIT_V,
  OPTBIT_C,
  OPTBIT_L,
  OPTBIT_N,
  OPTBIT_H,
  OPTBIT_S,
  OPTBIT_F,
  OPTBIT_O
};

#define OPT_PR(_1) (opt->mutual _1(1 << OPTBIT_E))
#define OPT_IC(_1) (opt->mutual _1(1 << OPTBIT_I))
#define OPT_IM(_1) (opt->mutual _1(1 << OPTBIT_V))
#define OPT_CL(_1) (opt->mutual _1(1 << OPTBIT_C))
#define OPT_MF(_1) (opt->mutual _1(1 << OPTBIT_L))
#define OPT_NL(_1) (opt->mutual _1(1 << OPTBIT_N))
#define OPT_WN(_1) (opt->mutual _1(1 << OPTBIT_H))
#define OPT_SE(_1) (opt->mutual _1(1 << OPTBIT_S))
#define OPT_TR(_1) (opt->mutual _1(1 << OPTBIT_F))
#define OPT_MP(_1) (opt->mutual _1(1 << OPTBIT_O))

typedef struct {
  unsigned int mutual : 16;
  const char *const s_opt;
  regex_t pattern;
  regmatch_t match[1];
} g_opt;

void check_grep_options(int *argc, char ***argv, g_opt *opt);
void take_regexp_patterns(int *argc, char ***argv, g_opt *opt);
void grep_print_with_opt(int *argc, char ***argv, g_opt *opt);
void print_with_opt(int *const argc, char ***const argv, FILE *fp, g_opt *opt,
                    size_t index);
int search(char *buf, g_opt *opt);

#endif  // SRC_GREP_S21_CAT_H_