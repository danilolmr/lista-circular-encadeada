#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct node {
    char *data;
    struct node *next;
};

void add_node(struct node **head, char *data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = (char *)malloc(strlen(data) + 1);
    strcpy(new_node->data, data);

    if (*head == NULL) {
        new_node->next = new_node;
        *head = new_node;
        return;
    }

    struct node *last = (*head)->next;
    while (last->next != (*head)->next) {
        last = last->next;
    }

    last->next = new_node;
    new_node->next = *head;
}

void remove_node(struct node **head, char *data) {
    if (*head == NULL) {
        return;
    }

    struct node *current = (*head)->next, *prev = NULL;
    while (strcmp(current->data, data) != 0 && current != (*head)) {
        prev = current;
        current = current->next;
    }

    if (strcmp(current->data, data) == 0) {
        if (current == (*head)->next && current->next == (*head)) {
            free(current->data);
            free(current);
            *head = NULL;
            return;
        }

        if (current == (*head)->next) {
            struct node *last = (*head)->next;
            while (last->next != (*head)->next) {
                last = last->next;
            }

            (*head)->next = current->next;
            last->next = current->next;
            free(current->data);
            free(current);
            return;
        }

        prev->next = current->next;
        free(current->data);
        free(current);
    }
}

int count_nodes(struct node **head) {
    int count = 0;
    if (*head == NULL) {
        return count;
    }

    struct node *current = (*head)->next;
    while (current != (*head)) {
        count++;
        current = current->next;
    }
    return count + 1;
}

void search_node(struct node **head, char *data) {
    if (*head == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    struct node *current = (*head)->next;
    while (current != (*head)) {
        if (strcmp(current->data, data) == 0) {
            printf("Encontrado: %s\n", data);
            return;
        }
        current = current->next;
    }
    printf("Não encontrado: %s\n", data);
}

void print_list(struct node **head) {
    if (*head == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    struct node *current = (*head)->next;
    while (current != (*head)) {
        printf("%s\n", current->data);
        current = current->next;
    }
    printf("%s\n", current->data);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    struct node* head = NULL;
    char movie[100];
    int choice;

    while (1) {
        printf("Escolha uma opção:\n");
        printf("1. Adicionar filme\n");
        printf("2. Remover filme\n");
        printf("3. Buscar filme\n");
        printf("4. Contar filmes\n");
        printf("5. Imprimir lista de filmes\n");
        printf("6. Sair\n");

        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Insira o nome do filme: ");
                scanf("%s", movie);
                add_node(&head, movie);
                break;
            case 2:
                printf("Insira o nome do filme: ");
                scanf("%s", movie);
                remove_node(&head, movie);
                break;
            case 3:
                printf("Insira o nome do filme: ");
                scanf("%s", movie);
                search_node(&head, movie);
                break;
            case 4:
                printf("Número de filmes na lista: %d\n", count_nodes(&head));
                break;
            case 5:
                print_list(&head);
                break;
            case 6:
                exit(0);
            default:
                printf("Opção inválida.\n");
        }
    }
    return 0;
}
