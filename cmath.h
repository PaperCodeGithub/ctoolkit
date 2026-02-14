#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int rows;
    int cols;
    double **data;
} matrix;

matrix* create_matrix(int rows, int cols) {
    matrix *m = (matrix*)malloc(sizeof(matrix));
    m->rows = rows;
    m->cols = cols;
    m->data = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        m->data[i] = (double*)calloc(cols, sizeof(double));
    }
    return m;
}

void free_matrix(matrix *m) {
    for (int i = 0; i < m->rows; i++) free(m->data[i]);
    free(m->data);
    free(m);
}

matrix* matrix_from_input(int rows, int cols) {
    matrix *m = create_matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Enter (%d, %d): ", i , j);
            scanf("%lf", &m->data[i][j]);
        }
    }
    return m;
}

matrix* matrix_rand(int rows, int cols, int min, int max) {
    matrix *m = create_matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m->data[i][j] = (rand() % (max - min + 1)) + min;
        }
    }
    return m;
}

matrix* matrix_add(matrix *a, matrix *b) {
    if (a->rows != b->rows || a->cols != b->cols) return NULL;
    matrix *res = create_matrix(a->rows, a->cols);
    for (int i = 0; i < a->rows; i++)
        for (int j = 0; j < a->cols; j++)
            res->data[i][j] = a->data[i][j] + b->data[i][j];
    return res;
}

matrix* matrix_sub(matrix *a, matrix *b) {
    if (a->rows != b->rows || a->cols != b->cols) return NULL;
    matrix *res = create_matrix(a->rows, a->cols);
    for (int i = 0; i < a->rows; i++)
        for (int j = 0; j < a->cols; j++)
            res->data[i][j] = a->data[i][j] - b->data[i][j];
    return res;
}

matrix* matrix_mult(matrix *a, matrix *b) {
    if (a->cols != b->rows) return NULL;
    matrix *res = create_matrix(a->rows, b->cols);
    for (int i = 0; i < a->rows; i++)
        for (int j = 0; j < b->cols; j++)
            for (int k = 0; k < a->cols; k++)
                res->data[i][j] += a->data[i][k] * b->data[k][j];
    return res;
}

matrix* matrix_transpose(matrix *m) {
    matrix *res = create_matrix(m->cols, m->rows);
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
            res->data[j][i] = m->data[i][j];
    return res;
}

typedef struct {
    int r, c;
    double val;
} sparse_element;

sparse_element* to_sparse(matrix *m, int *count) {
    int k = 0;
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
            if (m->data[i][j] != 0) k++;
    
    sparse_element *sparse = (sparse_element*)malloc(k * sizeof(sparse_element));
    int idx = 0;
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            if (m->data[i][j] != 0) {
                sparse[idx].r = i;
                sparse[idx].c = j;
                sparse[idx].val = m->data[i][j];
                idx++;
            }
        }
    }
    *count = k;
    return sparse;
}

void matrix_print(matrix *m) {
    if (m == NULL) return;
    for (int i = 0; i < m->rows; i++) {
        printf("| ");
        for (int j = 0; j < m->cols; j++) {
            printf("%8.2lf ", m->data[i][j]);
        }
        printf(" |\n");
    }
    printf("\n");
}

int math_gcd(int a, int b) {
    while (b) {
        a %= b;
        int t = a; a = b; b = t;
    }
    return a;
}

long long math_factorial(int n) {
    if (n <= 1) return 1;
    return n * math_factorial(n - 1);
}

int math_is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

double math_clamp(double val, double min, double max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}


static double apply_op(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

static int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double evaluate_expression(const char* exp) {
    double values[100];
    char ops[100];
    int v_top = -1, o_top = -1;

    for (int i = 0; exp[i] != '\0'; i++) {
        if (isspace(exp[i])) continue;

        if (isdigit(exp[i])) {
            double val = 0;
            while (i < strlen(exp) && (isdigit(exp[i]) || exp[i] == '.')) {
                if (exp[i] == '.') {
                    double decimal = 10;
                    i++;
                    while (isdigit(exp[i])) {
                        val += (exp[i] - '0') / decimal;
                        decimal *= 10;
                        i++;
                    }
                    break;
                }
                val = (val * 10) + (exp[i] - '0');
                i++;
            }
            values[++v_top] = val;
            i--;
        } 
        else if (exp[i] == '(') {
            ops[++o_top] = '(';
        } 
        else if (exp[i] == ')') {
            while (o_top != -1 && ops[o_top] != '(') {
                double val2 = values[v_top--];
                double val1 = values[v_top--];
                char op = ops[o_top--];
                values[++v_top] = apply_op(val1, val2, op);
            }
            o_top--; 
        } 
        else {
            while (o_top != -1 && precedence(ops[o_top]) >= precedence(exp[i])) {
                double val2 = values[v_top--];
                double val1 = values[v_top--];
                char op = ops[o_top--];
                values[++v_top] = apply_op(val1, val2, op);
            }
            ops[++o_top] = exp[i];
        }
    }

    while (o_top != -1) {
        double val2 = values[v_top--];
        double val1 = values[v_top--];
        char op = ops[o_top--];
        values[++v_top] = apply_op(val1, val2, op);
    }

    return values[v_top];
}