#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

void list_files(const char* dirname) {
  DIR* dir = opendir(dirname);
  if (dir == NULL) {
    return;
  }
  struct dirent* ent = readdir(dir);
  while(ent != NULL) {
    if(ent->d_type == DT_DIR) {
      printf("%hhd, \033[1;32m%s\t\033[0m\n", ent->d_type, ent->d_name);
    } else {
      printf("%hhd, %s\n", ent->d_type, ent->d_name);
    }
    ent =readdir(dir);
  }
  closedir(dir);
}

void list_files_recursively(const char* dirname) {
  printf("\t\033[1;31m %s \t\033[0m\n", dirname);
  DIR* dir = opendir(dirname);
  if (dir == NULL) {
    return;
  }
  struct dirent* ent;
  ent = readdir(dir);
  while (ent != NULL) {
    if(ent->d_type == DT_DIR) {
      printf("%hhd, \033[1;32m%s\t\033[0m\n", ent->d_type, ent->d_name);
    } else {
      printf("%hhd, %s\n", ent->d_type, ent->d_name);
    }
    if (ent->d_type == DT_DIR && strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")) {
      char path[100] = { 0 };
      strcat(path, dirname);
      strcat(path, "/");
      strcat(path, ent->d_name);
      list_files_recursively(path);
    }
    ent = readdir(dir);
  }
  closedir(dir);
  printf("\n");
}

int main(int argc, char *argv[])
{
  int opt = 0;
  while ((opt = getopt(argc, argv, "hrt")) != EOF) {
    switch (opt) {
    case 'h':
      printf("Usage: li /path/to/list/ or -[hr]\n-h: Print help information\n-r: Run li in recursive mode (iterate in each folder)\n");
      exit(1);
      break;
    case 'r':
      list_files_recursively(".");
      exit(1);
      break;
    }
  }
  list_files(argv[1]);
  return 0;
}
