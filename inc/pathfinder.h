#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"

typedef struct node{
    int full_dist;
    char *name;
    struct node* parent;
}               Node;

typedef struct queue { 
    int priority; 
    Node *node;
    struct queue* next;   
}              Queue;

void pop(Queue** head);
void push(Queue **head, Node *node);
int isEmpty(Queue** head);

Queue *new_Queue(Node *node);
Node *new_Node(char *isl, int full_dist);
Node **generate_successors(Node *parent, char **islands, int num, int **matrix);
Node **pathfinder(int **matrix, char **islands, int a, int b, int num);

bool checknum(const char *num);
bool checkword(const char *word);
bool checkline(const char *from, const char *to, const char *dist);
void checklast(char *str);

void sorting(char **path, char **islands, int **arr, unsigned long size);

int string_amount(char **arr);

void convert(Node **ways, char **path, int s);
int get_index_in_strarr(char **arr, char *sub);
void print_path(char *path, int **matrix, char **islands);

void parse(const char *filename);

#endif
