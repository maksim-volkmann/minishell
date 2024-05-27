#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct TokenNode {
    char *token;
    struct TokenNode *next;
} TokenNode;

typedef struct {
    TokenNode *head;
    TokenNode *tail;
    size_t size;
} TokenList;

void init_token_list(TokenList *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void add_token(TokenList *list, char *token) {
    TokenNode *new_node = malloc(sizeof(TokenNode));
    new_node->token = token;
    new_node->next = NULL;

    if (list->tail == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    list->size++;
}

void free_token_list(TokenList *list) {
    TokenNode *current = list->head;
    TokenNode *next;

    while (current != NULL) {
        next = current->next;
        free(current->token);
        free(current);
        current = next;
    }
}

char **token_list_to_array(TokenList *list) {
    char **tokens = malloc((list->size + 1) * sizeof(char *));
    TokenNode *current = list->head;
    size_t i = 0;

    while (current != NULL) {
        tokens[i++] = current->token;
        current = current->next;
    }
    tokens[i] = NULL; // Null-terminate the array

    return tokens;
}

char **tokenize(char *input) {
    TokenList token_list;
    init_token_list(&token_list);

    char *start;
    char quote_char;

    while (*input != '\0') {
        // Skip leading whitespace
        while (*input == ' ' || *input == '\t' || *input == '\r' || *input == '\n') {
            input++;
        }

        if (*input == '\0') break;

        if (*input == '"' || *input == '\'') {
            quote_char = *input;
            start = ++input;
            while (*input != quote_char && *input != '\0') {
                input++;
            }
            if (*input == quote_char) {
                *input = '\0';
                add_token(&token_list, strdup(start));
                input++;
            } else {
                fprintf(stderr, "Error: Unclosed quotes\n");
                free_token_list(&token_list);
                return NULL;
            }
        } else if (*input == '|') {
            add_token(&token_list, strdup("|"));
            input++;
        } else {
            start = input;
            while (*input != ' ' && *input != '\t' && *input != '\r' && *input != '\n' &&
                   *input != '"' && *input != '\'' && *input != '|' && *input != '\0') {
                input++;
            }
            if (*input != '\0') {
                *input = '\0';
                input++;
            }
            add_token(&token_list, strdup(start));
        }
    }

    char **tokens = token_list_to_array(&token_list);
    // We don't free the tokens here because they're being managed by the tokens array now
    return tokens;
}

int main(void) {
    char *input;
    char **tokens;

    while (1) {
        input = readline("minishell> ");
        if (input == NULL) {
            printf("exit\n");
            break;
        }

        if (*input) {
            add_history(input);
        }

        tokens = tokenize(input);
        if (tokens != NULL) {
            for (int i = 0; tokens[i] != NULL; i++) {
                printf("Token: %s\n", tokens[i]);
            }
            // Free the tokens array and the tokens themselves
            for (int i = 0; tokens[i] != NULL; i++) {
                free(tokens[i]);
            }
            free(tokens);
        }

        free(input);
    }

    return 0;
}


// cc -Wall -Wextra -Werror minishell.c -lreadline
