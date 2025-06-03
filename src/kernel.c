#include "kernel.h"
#include "shell.h"

char username[32] = "user";
char company_suffix[16] = "";
byte current_color = 0x07;

void clearScreen(int colorScheme);

int main()
{
  clearScreen(0x0F);
  shell();
  return 0;
}

void printString(char *message)
{
    while (*message != '\0') {
        interrupt(0x10, 0x0E00 + *message, 0, 0, 0);
        message++;
    }
}

void readString(char *buffer)
{
    char keypress;
    int position = 0;
    int maxLength = 126;

    while (1) {
        keypress = interrupt(0x16, 0x0000, 0, 0, 0) & 0xFF;

        if (keypress == 0x0D) {
            break;
        } else if (keypress == 0x08) {
            if (position > 0) {
                position--;
                printString("\b \b");
            }
        } else if (keypress >= 32 && keypress <= 126 && position < maxLength) {
            buffer[position++] = keypress;
            interrupt(0x10, 0x0E00 + keypress, 0, 0, 0);
        }
    }

    buffer[position++] = 0x0D;
    buffer[position++] = 0x0A;
    buffer[position] = '\0';
    printString("\r\n");
}

void clearScreen(int colorScheme)
{
  int counter;
  int totalCells = 80 * 25 * 2;

  for (counter = 0; counter < totalCells; counter += 2) {
    putInMemory(0xB800, counter, ' ');
    putInMemory(0xB800, counter + 1, colorScheme);
  }

  interrupt(0x10, 0x0200, 0, 0, 0);
}
