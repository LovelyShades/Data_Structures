#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"
#include "booleanEvaluation.h"
#include "booleanWithError.h"

void printName()
{
    printf("This solution was completed by:\n");
    printf("Alanna Matundan\n");
}

char *evaluatePostfix(char *str)
{
    int tokenCount;
    char **arrTokens = tokenizeString(str, &tokenCount);
    Stack *stack = createStack();
    char *token;
    char *operand1;
    char *operand2;
    char *result;
    char *finalResult;
    int i; /* Declare loop variable outside the loop */

    for (i = 0; i < tokenCount; i++)
    {
        token = arrTokens[i];

        if (strcmp(token, "T") == 0 || strcmp(token, "F") == 0)
        {
            /*Allocate memory for the token to avoid using static strings */
            char *newToken = malloc(strlen(token) + 1);
            strcpy(newToken, token);
            push(stack, newToken);
        }
        else if (strcmp(token, "NOT") == 0)
        {
            if (isEmpty(stack))
            {
                freeStack(stack);
                return booleanToString(ERROR);
            }
            operand1 = pop(stack);
            /* Allocate memory for result */
            result = malloc(2);
            strcpy(result, (strcmp(operand1, "T") == 0) ? "F" : "T");
            free(operand1); /* Free operand1 since it's no longer needed */
            push(stack, result);
        }
        else
        { /* Binary operators */
            if (isEmpty(stack))
            {
                freeStack(stack);
                return booleanToString(ERROR);
            }
            operand2 = pop(stack);
            if (isEmpty(stack))
            {
                free(operand2);
                freeStack(stack);
                return booleanToString(ERROR);
            }
            operand1 = pop(stack);
            /* Allocate memory for result */
            result = malloc(2);
            if (strcmp(token, "AND") == 0)
            {
                strcpy(result, (strcmp(operand1, "T") == 0 && strcmp(operand2, "T") == 0) ? "T" : "F");
            }
            else if (strcmp(token, "OR") == 0)
            {
                strcpy(result, (strcmp(operand1, "T") == 0 || strcmp(operand2, "T") == 0) ? "T" : "F");
            }
            else if (strcmp(token, "NAND") == 0)
            {
                strcpy(result, (strcmp(operand1, "T") == 0 && strcmp(operand2, "T") == 0) ? "F" : "T");
            }
            else if (strcmp(token, "NOR") == 0)
            {
                strcpy(result, (strcmp(operand1, "F") == 0 && strcmp(operand2, "F") == 0) ? "T" : "F");
            }
            else if (strcmp(token, "XOR") == 0)
            {
                strcpy(result, (strcmp(operand1, operand2) == 0) ? "F" : "T");
            }
            else if (strcmp(token, "COND") == 0)
            {
                strcpy(result, (strcmp(operand1, "F") == 0 || strcmp(operand2, "T") == 0) ? "T" : "F");
            }
            else if (strcmp(token, "BICOND") == 0)
            {
                strcpy(result, (strcmp(operand1, operand2) == 0) ? "T" : "F");
            }
            else
            {
                free(operand1);
                free(operand2);
                freeStack(stack);
                return booleanToString(ERROR);
            }
            free(operand1);
            free(operand2);
            push(stack, result);
        }
    }

    if (getStackSize(stack) != 1)
    {
        freeStack(stack);
        return booleanToString(ERROR);
    }

    finalResult = pop(stack);
    freeStack(stack);
    return finalResult; /* finalResult is dynamically allocated */
}

char *postfixToInfix(char *str)
{
    int tokenCount;
    char **arrTokens = tokenizeString(str, &tokenCount);
    Stack *stack = createStack();
    char *token;
    char *operand1;
    char *operand2;
    char *infixExpr;
    char *finalInfix;
    int i; /* Declare loop variable outside the loop */

    for (i = 0; i < tokenCount; i++)
    {
        token = arrTokens[i];

        if (strcmp(token, "T") == 0 || strcmp(token, "F") == 0)
        {
            /* Allocate memory for the token to avoid using static strings */
            char *newToken = malloc(strlen(token) + 1);
            strcpy(newToken, token);
            push(stack, newToken);
        }
        else
        {
            if (isEmpty(stack))
            {
                freeStack(stack);
                return booleanToString(ERROR);
            }
            operand2 = pop(stack);
            if (isEmpty(stack))
            {
                free(operand2);
                freeStack(stack);
                return booleanToString(ERROR);
            }
            operand1 = pop(stack);

            /* Allocate enough space for the new infix expression */
            infixExpr = (char *)malloc(strlen(operand1) + strlen(operand2) + strlen(token) + 10);
            if (!infixExpr)
            { /* Check for successful allocation */
                free(operand1);
                free(operand2);
                freeStack(stack);
                return booleanToString(ERROR);
            }

            sprintf(infixExpr, "( %s %s %s )", operand1, token, operand2);
            push(stack, infixExpr);
            free(operand1); /* Free the operands after using them */
            free(operand2);
        }
    }

    if (getStackSize(stack) != 1)
    {
        freeStack(stack);
        return booleanToString(ERROR);
    }

    finalInfix = pop(stack);
    freeStack(stack);
    return finalInfix; /* finalInfix is dynamically allocated */
}
