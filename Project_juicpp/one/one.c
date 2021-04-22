#include "one.h"
#include "scanner.h"
static void help(void) {
  printf("Usage: one [command | file] [arguments...]\n");
  printf("\n");
  printf("Commands:\n");
  printf("  help     Show command line usage\n");
  printf("  version  Show version\n");
  printf("\n");
}
int main(int argc, char *argv[]) {
  if (argc == 2 && strcmp(argv[1], "help") == 0) {
    help();
  } else if (argc == 1) {
    help();
  } else if (argc == 2 && strcmp(argv[1], "version") == 0) {
    printf("One %s\n", ONE_VERSION_STRING);
    return 0;
  } else {
    compileFile(argv[1]);
  }
}
