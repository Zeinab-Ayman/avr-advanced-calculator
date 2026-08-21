/*
 * OP.c
 *
 *  Created on: Aug 18, 2026
 *      Author: Zeinab
 */

#include "../Serv/BIT_MATH.h"
#include "../Serv/STD_TYPES.h"

f32 EvaluateExpression(f32 numbers[], uint8 num_count, uint8 ops[], uint8 op_count, uint8* err)
{
    uint8 i, j;

    for (j = 0; j < op_count; j++)
    {
        if (ops[j] == '*' || ops[j] == '/')
        {
            if (ops[j] == '*')
            {
                numbers[j] = numbers[j] * numbers[j + 1];
            }
            else if (ops[j] == '/')
            {
                if (numbers[j + 1] != 0.0)
                {
                    numbers[j] = numbers[j] / numbers[j + 1];
                }

                else
                {
                	*err = 1;
                    return 0;
                }
            }

            for (i = j + 1; i < num_count - 1; i++)
            {
                numbers[i] = numbers[i + 1];
            }
            num_count--;

            for (i = j; i < op_count - 1; i++)
            {
                ops[i] = ops[i + 1];
            }
            op_count--;

            j--;
        }
    }

    for (j = 0; j < op_count; j++)
    {
        if (ops[j] == '+' || ops[j] == '-')
        {
            if (ops[j] == '+')
            {
                numbers[j] = numbers[j] + numbers[j + 1];
            }
            else if (ops[j] == '-')
            {
                numbers[j] = numbers[j] - numbers[j + 1];
            }

            for (i = j + 1; i < num_count - 1; i++)
            {
                numbers[i] = numbers[i + 1];
            }
            num_count--;

            for (i = j; i < op_count - 1; i++)
            {
                ops[i] = ops[i + 1];
            }
            op_count--;

            j--;
        }
    }

    return numbers[0];
}

