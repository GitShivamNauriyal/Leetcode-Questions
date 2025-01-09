#include <stdio.h>
int divide(int dividend, int divisor)
{
    static int out = 0;
    static int neg = 0;
    printf("%d_%d\n", dividend, divisor);
    if (dividend < 0 || divisor < 0)
    {
        if (dividend < 0 && divisor < 0)
        {
            neg = 0;
        }
        else
        {
            if (dividend < 0)
                dividend = -dividend;
            if (divisor < 0)
                divisor = -divisor;
            neg = 1;
        }
    }

    if (dividend < divisor)
    {
        if (neg == 1)
            out = -out;
        return out;
    }
    printf("%d__%d\n", dividend, divisor);
    out++;
    out = divide(dividend - divisor, divisor);
    return out;
}

int main(void)
{
    printf("\nans = %d\n", divide(7, -3));
}