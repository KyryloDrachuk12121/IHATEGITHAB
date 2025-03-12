#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

typedef void* Item;


typedef struct StackNode {
    Item item;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
} *StackPtr;

StackPtr StackInit() {
    StackPtr s = (StackPtr)malloc(sizeof(struct Stack));
    if (s == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    s->top = NULL;
    return s;
}

int StackEmpty(StackPtr s) {
    return (s->top == NULL);
}

void push(StackPtr s, Item item) {
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->item = item;
    node->next = s->top;
    s->top = node;
}

Item pop(StackPtr s) {
    if (StackEmpty(s)) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    StackNode* temp = s->top;
    Item item = temp->item;
    s->top = temp->next;
    free(temp);
    return item;
}

void StackDestroy(StackPtr s) {
    while (!StackEmpty(s)) {
        pop(s);
    }
    free(s);
}
int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <expression_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char expr[256];
    if (fgets(expr, sizeof(expr), file) == NULL) {
        fprintf(stderr, "Error reading file\n");
        fclose(file);
        return EXIT_FAILURE;
    }
    fclose(file);

    StackPtr vals = StackInit();
    StackPtr ops = StackInit();

    for (int i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];
        if (c == ' ' || c == '\n') {
            continue;
        }
        if (c == '(') {
        }
        else if (isdigit((unsigned char)c)) {
            double* num = (double*)malloc(sizeof(double));
            if (!num) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            *num = (double)(c - '0');
            push(vals, num);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            push(ops, (void*)(intptr_t)c);
        }
        else if (c == ')') {
            char op = (char)(intptr_t)pop(ops);
            double* v_ptr = (double*)pop(vals);
            double* u_ptr = (double*)pop(vals);

            double v = *v_ptr;
            double u = *u_ptr;
            free(v_ptr);
            free(u_ptr);

            double res;
            switch (op) {
            case '+': res = u + v; break;
            case '-': res = u - v; break;
            case '*': res = u * v; break;
            case '/': res = u / v; break;
            default:
                fprintf(stderr, "Unknown operator: %c\n", op);
                exit(EXIT_FAILURE);
            }
            double* res_ptr = (double*)malloc(sizeof(double));
            if (!res_ptr) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            *res_ptr = res;
            push(vals, res_ptr);
        }
    }

    double* result_ptr = (double*)pop(vals);
    double result = *result_ptr;
    free(result_ptr);

    printf("Result: %.2f\n", result);

    StackDestroy(vals);
    StackDestroy(ops);
    return EXIT_SUCCESS;
}
