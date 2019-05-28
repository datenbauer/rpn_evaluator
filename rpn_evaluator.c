/* myexpr.c
 *
 * Evaluates command line paramters as mathematical expression in RPN.
 */

#include <stdio.h>
#include <stdlib.h> # for strtod()
#include <math.h>   # for pow()
#include <string.h> # for strcmp()

#define STACKSIZE 3

enum {
    FAILURE,
    SUCCESS,
    ADD,
    SUB,
    MUL,
    DIV,
    POW
};

double stack[STACKSIZE];
const double *bot = &stack[STACKSIZE];    // points to one slot beyond last element
double *top = &stack[STACKSIZE];          // points to top of stack

/*
 * Puts val on top of the stack.
 */
int push(double val) {
    if(top <= &stack[0]) {
        return FAILURE;
    }
    top--;
    *top = val;
    return SUCCESS;
}

/*
 * Takes one element from top of stack and stores it in res.
 */
int pop(double *res) {
    if(top >= &stack[STACKSIZE]) {
        return FAILURE;
    }
    *res = *top;
    top++;
    return SUCCESS;
}

/*
 * Returns 1 if stack is empty, else 0.
 */
int is_empty(void) {
    if(top == bot)
        return 1;
    return 0;
}

/*
 * Returns number of elements on stack.
 */
int size(void) {
    return bot-top;
}

/*
 * Prints error message and exits.
 */
void err_msg(char *msg) {
    printf("%s\n", msg);
    exit(EXIT_FAILURE);
}

/*
 * Takes two operands from stack, evaluates them according to parameter and
 * pushes the result onto the stack.
 */
void eval(int op) {
    double op1, op2, res;

    if(pop(&op1)==FAILURE || pop(&op2)==FAILURE)
        err_msg("Error: stack underflow!");
    switch (op) {
    case ADD:
        res = op2 + op1;
        break;
    case SUB:
        res = op2 - op1;
        break;
    case MUL:
        res = op2 * op1;
        break;
    case DIV:
        if(op1 == 0)
            err_msg("Error: division by zero.");
        res = op2 / op1;
        break;
    case POW:
        if(fabs(round(op1)-op1) >= 0.0001)
            err_msg("Error: pow should have a whole number as exponent.");
        res = pow(op2, op1);
    }
    if(push(res)==FAILURE)
        err_msg("Error: stack overflow!");
}

int main(int argc, char *argv[]) {
    
    double d;
    
    for(int i=1; i<argc; i++) { // loop over all arguments
        if(!strcmp(argv[i], "+"))
            eval(ADD);
        else if(!strcmp(argv[i], "-"))
            eval(SUB);
        else if(!strcmp(argv[i], "*"))
            eval(MUL);
        else if(!strcmp(argv[i], "/"))
            eval(DIV);
        else if(!strcmp(argv[i], "^"))
            eval(POW);
        else {
            d = strtod(argv[i], NULL);
            if(d==0 && strcmp(argv[i], "0")){   // parsing error
                printf("Error: invalid operand %s.\n", argv[i]);
                exit(EXIT_FAILURE);
            }
            if(push(d)==FAILURE)
                err_msg("Error: stack overflow!");
        }
    }
    if(is_empty())
        err_msg("Error: no input given!\n");
    if(size() > 1)
        err_msg("Error: unused operands on stack.");
    pop(&d);
    printf("%g\n", d);

    return 0;
}