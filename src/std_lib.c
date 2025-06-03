#include "std_lib.h"

int div(int dividend, int divisor)
{
    int quotientResult = 0;
    int isNegative = 0;
    int absDividend;
    int absDivisor;

    if (divisor == 0) {
        return 0;
    }

    if ((dividend < 0) != (divisor < 0)) {
        isNegative = 1;
    }

    absDividend = (dividend < 0) ? -dividend : dividend;
    absDivisor = (divisor < 0) ? -divisor : divisor;

    while (absDividend >= absDivisor) {
        absDividend -= absDivisor;
        quotientResult++;
    }

    return isNegative ? -quotientResult : quotientResult;
}

int safe_mod(int dividend, int divisor)
{
    while (dividend >= divisor) dividend -= divisor;
    return dividend;
}

int mod(int dividend, int divisor)
{
    int remainder;
    if (divisor == 0) {
        return 0;
    }
    remainder = dividend - div(dividend, divisor) * divisor;
    return remainder;
}

bool strcmp(char *firstStr, char *secondStr)
{
    int index = 0;

    while (firstStr[index] != '\0' && secondStr[index] != '\0') {
        if (firstStr[index] != secondStr[index]) {
            return false;
        }
        index++;
    }

    return (firstStr[index] == '\0' && secondStr[index] == '\0');
}

void strcpy(char *destination, char *source)
{
    int index = 0;

    while (source[index] != '\0') {
        destination[index] = source[index];
        index++;
    }

    destination[index] = '\0';
}

void clear(byte *buffer, unsigned int bufferSize)
{
    unsigned int counter;
    for (counter = 0; counter < bufferSize; counter++) {
        buffer[counter] = 0;
    }
}

void atoi(char *inputStr, int *resultNum)
{
    int result = 0;
    int isNegative = 0;
    int startIndex = 0;
    int digit;

    while (inputStr[startIndex] == ' ' || inputStr[startIndex] == '\t') {
        startIndex++;
    }

    if (inputStr[startIndex] == '-') {
        isNegative = 1;
        startIndex++;
    } else if (inputStr[startIndex] == '+') {
        startIndex++;
    }

    while (inputStr[startIndex] >= '0' && inputStr[startIndex] <= '9') {
        digit = inputStr[startIndex] - '0';
        result = (result * 10) + digit;
        startIndex++;
    }

    *resultNum = isNegative ? -result : result;
}

void itoa(int inputNum, char *outputStr)
{
    int digitCount = 0;
    int isNegative = 0;
    int tempNum = inputNum;
    int remainder;
    int start, end;
    char tempChar;

    if (inputNum == 0) {
        outputStr[0] = '0';
        outputStr[1] = '\0';
        return;
    }

    if (inputNum < 0) {
        isNegative = 1;
        tempNum = -inputNum;
    }

    while (tempNum > 0) {
    int div = tempNum / 10;
    remainder = tempNum - div * 10;
    outputStr[digitCount] = remainder + '0';
    tempNum = div;
    digitCount++;
}

    if (isNegative) {
        outputStr[digitCount] = '-';
        digitCount++;
    }

    outputStr[digitCount] = '\0';

    start = 0;
    end = digitCount - 1;
    while (start < end) {
        tempChar = outputStr[start];
        outputStr[start] = outputStr[end];
        outputStr[end] = tempChar;
        start++;
        end--;
    }
}