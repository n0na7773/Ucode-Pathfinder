#include "../inc/pathfinder.h"

Queue* new_Queue(Node *node) { 
    Queue* new_node = (Queue*)malloc(sizeof(Queue)); 
    new_node->priority = node->full_dist;
    new_node->next = NULL;
    new_node->node = node;
    return new_node; 
} 
Node *new_Node(char *name, int all_way) {
    Node* new_node = (Node*)malloc(sizeof(Node)); 
    new_node->name = mx_strdup(name);
    new_node->parent = NULL; 
    new_node->full_dist = all_way; 
    return new_node; 
} 

void pop(Queue** head) {
    Queue* temp = *head; 
    (*head) = (*head)->next; 
    free(temp); 
} 

void push(Queue** head, Node *node) {
    Queue* start = (*head); 
    Queue* temp_node = new_Queue(node); 
    if((*head) == NULL) {
        (*head) = temp_node;
        return;
    }    
    if ((*head)->priority > node->full_dist) {         
        temp_node->next = *head; 
        (*head) = temp_node; 
    } else { 
        while (start->next != NULL && start->next->priority < node->full_dist)
            start = start->next; 
        temp_node->next = start->next; 
        start->next = temp_node; 
    }
} 

int isEmpty(Queue** queue) {
    if((*queue) == NULL) return 1; 
    return 0;
} 

Node **generate_successors(Node* parent, char **islands, int num, int **matrix) {
    int index = 0;

    while(mx_strcmp(islands[index], parent->name) != 0) index++;

    Node **successors = (Node **)malloc(sizeof(Node *) * num);
    for(int i = 0; i < num; i++) {
        successors[i] = (Node *)malloc(sizeof(Node));
        successors[i] = NULL;
    }

    for(int i = 0; i < num; i++) {
        if(i != index && matrix[index][i] != -1 && parent != NULL) {        
            Node *temp = parent;
            bool check = false;
            int j = 0;
            while(temp != NULL) {
                if(mx_strcmp(temp->name, islands[i]) == 0 || j > num) {
                    check = true;
                    break;
                }
                temp = temp->parent;  
                j++;              
            }
            if(j > num) break;
            if (check == false)
                successors[i] = new_Node(islands[i], parent->full_dist + matrix[index][i]);
        }
    }

    int lenght = 0;
    for(int i = 0; i < num; i++) {
        if(successors[i] != NULL) lenght++;
    }

    Node **successors_res = (Node **)malloc(sizeof(Node *) * (lenght + 1));
    for(int i = 0; i < lenght + 1; i++)
        successors_res[i] = NULL;

    lenght = 0;
    for(int i = 0; i < num; i++) {
        if(successors[i] != NULL) {
            successors_res[lenght] = (Node *)malloc(sizeof(Node));
            successors_res[lenght] = successors[i];
            lenght++;
        }
    }

    return successors_res;
}

Node **pathfinder(int **arr, char **islands, int a, int b, int num) {
    Node *island = new_Node(islands[a], 0);
    Queue *open = new_Queue(island);
    Queue *closed = new_Queue(island);
    int route_i = 0;

    Node **result = (Node **)malloc(sizeof(Node *) * mx_pow(num, 2));
    for(int i = 0; i < num; i++) {
        result[i] = (Node*)malloc(sizeof(Node));
        result[i] = NULL;
    }
    
    while (!isEmpty(&open)) {
        island = open->node;

        pop(&open);

        Node *temp = island;
        int j = 0;
        for(; temp->parent != NULL; j++) {
            if(j > num)
                break;
            temp = temp->parent;
        }
        if(j >= num) continue;

        bool in_islands = false;
        for(int h = 0; h < num; h++) {
            if(mx_strcmp(island->name, islands[h]) == 0) {
                in_islands = true;
            }
        }
        if(in_islands == false) continue;
        
        Node **successors = generate_successors(island, islands, num, arr);  

        for (int i = 0; successors[i] != NULL; i++)
            successors[i]->parent = island;
        for (int i = 0; successors[i] != NULL; i++) {
            if(mx_strcmp(successors[i]->name, islands[b]) == 0) {
                result[route_i++] = successors[i];
            }

            Queue *temp_open = open;
            bool in_open = false;
            while(temp_open != NULL) {
                if(mx_strcmp(temp_open->node->name, successors[i]->name) == 0) {
                    if(temp_open->node->full_dist < successors[i]->full_dist) {
                        in_open = true;
                        break;
                    }
                }
                temp_open = temp_open->next;
            }

            Queue *temp_closed = closed;
            bool in_closed = false;
            while(temp_closed != NULL) {
                if(mx_strcmp(temp_closed->node->name, successors[i]->name) == 0) {
                    if(temp_closed->node->full_dist < successors[i]->full_dist) {
                        in_closed = true;
                        break;
                    }
                }
                temp_closed = temp_closed->next;
            }
   
            if(in_open == false && in_closed == false) {
                push(&open, successors[i]);
                push(&closed, successors[i]);
            }  
        }
    }
    return result;
}
