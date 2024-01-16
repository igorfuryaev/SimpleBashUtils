#include "s21_grep.h"

int main(int argc, char **argv) {
  g_opt opt = {OPTBIT_D, "e:ivclnhsf:o", {}, {}};

  check_grep_options(&argc, &argv, &opt);
  if (!(opt.mutual & (1 << OPTBIT_E)) && !(opt.mutual & (1 << OPTBIT_F)))
    take_regexp_patterns(&argc, &argv, &opt);
  grep_print_with_opt(&argc, &argv, &opt);
  return EXIT_SUCCESS;
}

void check_grep_options(int *argc, char ***argv, g_opt *opt) {
  int opt_val = 0;
  while ((opt_val = getopt(*argc, *argv, opt->s_opt)) != EOF) {
    switch (opt_val) {
      case 'e':
        OPT_PR(EQ_OR);
        take_regexp_patterns(argc, argv, opt);
        break;
      case 'i':
        OPT_IC(EQ_OR);
        break;
      case 'v':
        OPT_IM(EQ_OR);
        break;
      case 'c':
        OPT_CL(EQ_OR);
        break;
      case 'l':
        OPT_MF(EQ_OR);
        break;
      case 'n':
        OPT_NL(EQ_OR);
        break;
      case 'h':
        OPT_WN(EQ_OR);
        break;
      case 's':
        OPT_SE(EQ_OR);
        break;
      case 'f':
        OPT_TR(EQ_OR);
        take_regexp_patterns(argc, argv, opt);
        break;
      case 'o':
        OPT_MP(EQ_OR);
        break;
    }
  }

  *argc -= optind;
  *argv += optind;
}

void take_regexp_patterns(int *argc, char ***argv, g_opt *opt) {
  int cflags = REG_EXTENDED | (OPT_IC(EQUAL) ? REG_ICASE : 0);
  if (OPT_PR(EQUAL) && !OPT_TR(EQUAL)) {
    regcomp(&(opt->pattern), optarg, cflags);
  } else if (OPT_TR(EQUAL) && !OPT_PR(EQUAL)) {
    FILE *fp_t = fopen(optarg, "r");
    char temp_str[128];
    fgets(temp_str, 128, fp_t);
    regcomp(&(opt->pattern), temp_str, cflags);
    fclose(fp_t);
  } else if (regcomp(&(opt->pattern), *(*argv), cflags) == 0) {
    *argc -= 1;
    *argv += 1;
  }
}

void grep_print_with_opt(int *argc, char ***argv, g_opt *opt) {
  for (int i = 0; i < *argc; ++i) {
    FILE *fp = fopen(*(*argv + i), "r");
    if (fp == NULL && !OPT_SE(EQUAL))
      fprintf(stderr, "%s: %s: %s\n", *(*argv - optind), *(*argv + i),
              strerror(errno));

    if (fp != NULL) {
      print_with_opt(argc, argv, fp, opt, i);
      fclose(fp);
    }
  }
  regfree(&(opt->pattern));
}

void print_with_opt(int *const argc, char ***const argv, FILE *fp, g_opt *opt,
                    size_t index) {
  char buffer[BUF_SIZE];
  long count_of_matching = 0;
  bool if_match_file = false;
  for (int line = 1; fgets(buffer, BUF_SIZE, fp) != NULL; ++line) {
    if (strlen(buffer) == BUF_SIZE - 1)
      fprintf(stderr, "%s: Line too long\n", *(*argv + index));
    if (search(buffer, opt) == 0) {
      if_match_file = true;
      if (!OPT_CL(EQUAL) && !OPT_MF(EQUAL)) {
        if (*argc > 1 && !OPT_WN(EQUAL)) printf("%s:", *(*argv + index));
        if (OPT_NL(EQUAL)) printf("%d:", line);
        if (OPT_MP(EQUAL)) {
          regoff_t off = 0, len = 0;
          do {
            off += opt->match[0].rm_so + len;
            len = opt->match[0].rm_eo - opt->match[0].rm_so;
            fprintf(stdout, "%.*s\n", (int)len, buffer + off);
          } while (!regexec(&(opt->pattern), buffer + off + len, (size_t)1,
                            opt->match, 0));
        } else {
          printf("%s", buffer);
        }
      }
      ++count_of_matching;
    }
  }
  if (OPT_MF(EQUAL) && if_match_file)
    printf("%s%s\n", index > 0 ? "\n" : "", *(*argv + index));
  if (OPT_CL(EQUAL)) printf("%ld\n", count_of_matching);
}

int search(char *buf, g_opt *opt) {
  int flag = regexec(&(opt->pattern), buf, (size_t)1, opt->match, 0);
  return OPT_IM(EQUAL) ? !flag : flag;
}
