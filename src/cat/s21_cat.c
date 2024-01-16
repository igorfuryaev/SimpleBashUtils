/*"Copyright [2022] <creenorm>"*/
#include "./s21_cat.h"

int main(int argc, char** argv) {
  t_flag flag = {0, 0, 0, 0, 0, 0};
  int ret = 0;
  ret = parser_f(argc, argv, &flag);
  if (ret != -1) {
    for (int i = 1; i < argc; i++) {
      ret = read_file(argv, &flag, i);
    }
  }
  return ret;
}

int parser_f(int argc, char** argv, t_flag* flag) {
  int option_index = 0;
  char symbol = 0;
  int ret = 0;
  const struct option long_options[] = {{"--squezee-blank", 0, NULL, 'S'},
                                        {"--number-nonblank", 0, NULL, 'B'},
                                        {"--number", 0, NULL, 'N'},
                                        {NULL, 0, NULL, 0}};

  while ((symbol = getopt_long(argc, argv, "bestnETv", long_options,
                               &option_index)) != -1) {
    switch (symbol) {
      case 'b':
        flag->b = 1;
        break;
      case 'e':
        flag->e = 1;
        flag->v = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 't':
        flag->t = 1;
        flag->v = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'E':
        flag->e = 1;
        break;
      case 'T':
        flag->t = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case '?':
        ret = -1;  // обработка ошибок
        break;
    }
  }
  if (flag->b) flag->n = 0;
  return ret;
}

int read_file(char** argv, t_flag* flag, int i) {
  FILE* file = NULL;
  if ((file = fopen(argv[i], "r"))) {
    while (1) {
      int read = getc(file);
      if (read == EOF) break;
      // s
      static int currentEmptyLine = 1;
      if (read == '\n') {
        static int previousEmptyLine = 0;
        if (currentEmptyLine && previousEmptyLine && flag->s) {
          continue;
        } else if (currentEmptyLine) {
          previousEmptyLine = 1;
        } else {
          previousEmptyLine = 0;
          currentEmptyLine = 1;
        }
      } else {
        currentEmptyLine = 0;
      }

      // b
      static int newLine = 1;
      if (flag->b && read != '\n' && newLine) {
        static int sline = 1;
        printf("%6d\t", sline);
        sline++;
        newLine = 0;
      }
      // n
      if (newLine && flag->n) {
        static int sline = 1;
        printf("%6d\t", sline);
        sline++;
        newLine = 0;
      }
      if (flag->e && read == '\n') {
        printf("$");
      }
      if (flag->t && read == '\t') {
        printf("^I");
        continue;
      }
      if ((flag->v && read < 32 && read != '\t' && read != '\n' &&
           read != '\r') ||
          read == 127) {
        printf("^");
        read += 64;
      }
      if (read == '\n') {
        newLine = 1;
      }
      printf("%c", read);
    }
    fclose(file);
  }
  return 0;
}
