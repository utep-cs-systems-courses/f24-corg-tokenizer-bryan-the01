#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"
#include "history.h"

int space_char(char c) {
  if (c == '\t' || c == ' ')
    return 1;
  else
    return 0;
}

int non_space_char(char c) {
  if (c == '\t' || c == ' ')
    return 0;
  else
    return 1;
}

char *token_start(char *s) {
  while (*s != '\0') {
    if (non_space_char(*s))
      return s;
    s++;
  }
  return s;
}

char *token_terminator(char *s) {
  while (*s != '\0') {
    if (space_char(*s))
      return s;
    s++;
  }
  return s;
}

int count_tokens(char *str) {
  int tokens = 0;
  while (*str != '\0') {
    str = token_start(str);
    if (*str != '\0') {
      tokens++;
      str = token_terminator(str);
    }
  }
  return tokens;
}

char *copy_str(char *inStr, short len) {
  char *copy = (char *)malloc((len + 1) * sizeof(char));
  if (copy == NULL)
    return NULL;
  for (int i = 0; i < len; i++) {
    copy[i] = inStr[i];
  }
  copy[len] = '\0';
  return copy;
}

char **tokenize(char *s) {
  int num_tokens = count_tokens(s);
  char **tokens = (char **)malloc((num_tokens + 1) * sizeof(char *));
  int i = 0;
  while (*s != '\0') {
    s = token_start(s);
    char *temp = token_terminator(s);
    int len = temp - s;
    tokens[i] = copy_str(s, len);
    s = temp;
    i++;
  }
  tokens[i] = NULL;
  return tokens;
}

void print_tokens(char **tokens) {
  int i = 0;
  while (tokens[i] != NULL) {
    printf("t[%d] = %s\n", i, tokens[i]);
    i++;
  }
}

void free_tokens(char **tokens) {
  int i = 0;
  while (tokens[i] != NULL) {
    free(tokens[i]);
    i++;
  }
  free(tokens);
}

int strLen(const char *str) {
  int length = 0;
  while (*str++) {
    length++;
  }
  return length;
}

void rmNewline(char *str) {
  int len = strLen(str);
  if (len > 0 && str[len - 1] == '\n') {
    str[len - 1] = '\0';
  }
}


int strToInt(const char *str) {
  int num = 0;
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] >= '0' && str[i] <= '9') {
      num = num * 10 + (str[i] - '0');
    } else {
      return num;
    }
    i++;
  }
  return num;
}

int main() {
  char input[100];
  List *history = init_history();
  while (1) {
    printf("1. Enter 'a' to add a token\n");
    printf("2. Enter 't' to view a specific token in history\n");
    printf("3. Enter 'h' to see ALL your history\n");
    printf("4. Enter 'f' to free history\n");
    printf("> ");
    fgets(input, 100, stdin);
    rmNewline(input);
    switch (input[0]) {
    case 'a':{
      printf("Please enter your string (max 100 characters):\n");
      printf("> ");
      char token[100];
      fgets(token, 100, stdin);
      rmNewline(token);
      char **tokens = tokenize(token);
      print_tokens(tokens);
      add_history(history, token);
      free_tokens(tokens);
      break;
    }
    case 't': {
      printf("Which specific token ID would you like to recall?\n");
      printf("> ");
      fgets(input, 100, stdin);
      int id = strToInt(input);  // Manual atoi replacement
      char *tknHistory = get_history(history, id);
      if (tknHistory) {
	printf("The token with ID %d is: %s\n", id, tknHistory);
      } else {
	printf("No token found with ID %d\n", id);
      }
      break;
    }
    case 'h': {
      printf("Printing all history...\n");
      print_history(history);
      break;
    }
    case 'f': {
      printf("Freeing up your history...\n");
      free_history(history);
      break;
      }
      default:
      printf("Unknown command. Please enter a valid option.\n");
    }
  }
  return 0;
}
