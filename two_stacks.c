#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

double evaluateExpression(const char* expr) {
    Stack* vals = StackInit();
    Stack* ops = StackInit();

    for (int i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];
        if (c == ' ' || c == '\n') {
            continue; 
        }
        if (c == '(') {

        }
        else if (isdigit((unsigned char)c)) {
            double num = 0;
            while (isdigit((unsigned char)expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            i--;
            double* num_ptr = (double*)malloc(sizeof(double));
            if (!num_ptr) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            *num_ptr = num;
            push(vals, num_ptr);
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
            case '/':
                if (v == 0) {
                    fprintf(stderr, "Division by zero\n");
                    exit(EXIT_FAILURE);
                }
                res = u / v;
                break;
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
        else {
            fprintf(stderr, "Invalid character: %c\n", c);
            exit(EXIT_FAILURE);
        }
    }

    double* result_ptr = (double*)pop(vals);
    double result = *result_ptr;
    free(result_ptr);

    StackDestroy(vals);
    StackDestroy(ops);

    return result;
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

    double result = evaluateExpression(expr);
    printf("Result: %.2f\n", result);

    return EXIT_SUCCESS;
}