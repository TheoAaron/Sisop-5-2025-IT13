#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

char currentUser[64] = "user";
char serverName[64] = "";
int displayColor = 0x0F;

void userName(char *username);
void parseCommand(char *buffer, char *command, char params[2][64]);
void generateResponse(void);
void running(char *command, char *buffer, char params[2][64]);

bool isValidCommand(char *cmd);
void handleGrandCompany(char *company);
void handleYogurt();
void handleGurt(char *input);
int strlen(char *str);

void shell()
{
  char inputBuffer[128];
  char command[64];
  char params[2][64];

  printString("DOMAIN EXPANSION!\r\n");
  printString("Type 'help' to see what is within my domain\r\n\r\n");

  while (true) {
    userName(currentUser);
    readString(inputBuffer);
    parseCommand(inputBuffer, command, params);
    running(command, inputBuffer, params);
  }
}

void userName(char *username)
{
  printString(username);
  if (serverName[0] != '\0') {
    printString(serverName);
  }
  printString("$ ");
}

void parseCommand(char *buffer, char *command, char params[2][64])
{
    int index = 0, cmdPos = 0, paramPos = 0;
    int paramIndex = 0;
    while (buffer[index] != '\0' && (buffer[index] == '\r' || buffer[index] == '\n')) index++;
    while (buffer[index] != '\0' && buffer[index] != ' ' && buffer[index] != '\r' && buffer[index] != '\n') {
        command[cmdPos++] = buffer[index++];
    }
    command[cmdPos] = '\0';
    while (buffer[index] == ' ') index++;
    for (paramIndex = 0; paramIndex < 2; paramIndex++) {
        paramPos = 0;
        while (buffer[index] != '\0' && buffer[index] != ' ' && buffer[index] != '\r' && buffer[index] != '\n') {
            params[paramIndex][paramPos++] = buffer[index++];
        }
        params[paramIndex][paramPos] = '\0';

        while (buffer[index] == ' ') index++;
    }
}

void generateResponse()
{
    int randomValue = mod(getBiosTick(), 3);
    if (randomValue == 0) {
        printString("yo\r\n");
    } else if (randomValue == 1) {
        printString("sygau\r\n");
    } else {
        printString("ts unami gng </3\r\n");
    }
}

void running(char *command, char *buffer, char params[2][64])
{
    int num1, num2, result;
    char outputStr[32];

    if (strcmp(command, "yo")) {
        printString("gurt\r\n");

    } else if (strcmp(command, "gurt")) {
        printString("yo\r\n");

    } else if (strcmp(command, "user")) {
        if (params[0][0] == '\0') {
            strcpy(currentUser, "user");
        } else {
            strcpy(currentUser, params[0]);
        }
        printString("User changed to ");
        printString(currentUser);
        printString("\r\n");

    } else if (strcmp(command, "grandcompany")) {
        if (strcmp(params[0], "maelstorm")) {
          displayColor = 0x09;
          clearScreen(displayColor);
          strcpy(serverName, "@Storm");
        } else if (strcmp(params[0], "immortalflames")) {
          displayColor = 0x0c;
          clearScreen(displayColor);
          strcpy(serverName, "@Flame");
        } else if (strcmp(params[0], "twinadder")) {
          displayColor = 0x0e;
          clearScreen(displayColor);
          strcpy(serverName, "@Serpent");
        } else {
            printString("Available grandcompany: maelstorm, immortalflames, twinadder\r\n");
        }

    } else if (strcmp(command, "clear")) {
      strcpy(serverName, "");
      displayColor = 0x0F;
      clearScreen(displayColor);

    } else if (strcmp(command, "add")){
        if (params[0][0] == '\0' || params[1][0] == '\0') {
            printString("Adding <3333\r\n");
            return;
        }
        atoi(params[0], &num1);
        atoi(params[1], &num2);
        result = num1 + num2;
        itoa(result, outputStr);
        printString("Result: ");
        printString(outputStr);
        printString("\r\n");

    } else if (strcmp(command, "sub")) {
        if (params[0][0] == '\0' || params[1][0] == '\0') {
            printString("Subtarcting <3333\r\n");
            return;
        }
        atoi(params[0], &num1);
        atoi(params[1], &num2);
        result = num1 - num2;
        itoa(result, outputStr);
        printString("Result: ");
        printString(outputStr);
        printString("\r\n");

    } else if (strcmp(command, "mul")){
      if (params[0][0] == '\0' || params[1][0] == '\0') {
          printString("Multiplying >:DDD\r\n");
          return;
      }
      atoi(params[0], &num1);
      atoi(params[1], &num2);
      result = num1 * num2;
      itoa(result, outputStr);
      printString("Result: ");
      printString(outputStr);
      printString("\r\n");

    } else if (strcmp(command, "div")){
      if (params[0][0] == '\0' || params[1][0] == '\0') {
          printString("Divide (and conquer) =0\r\n");
          return;
      }
      atoi(params[0], &num1);
      atoi(params[1], &num2);
      if (num2 == 0) {
          printString("Error: You shall not divide by zero\r\n");
          return;
      }
      result = div(num1, num2);
      itoa(result, outputStr);
      printString("Result: ");
      printString(outputStr);
      printString("\r\n");

    } else if (strcmp(command, "info")){
      printString("System Information:\r\n");
      printString("ts pmo sybau\r\n");
      printString("User: ");
      printString(currentUser);
      printString("\r\n");

    } else if (strcmp(command, "yogurt")){
      userName("gurt");
      generateResponse();

    } else if (strcmp(command, "help")){
      printString("Available commands :\r\n");
      printString("yo, gurt, user <name>\r\n");
      printString("grandcompany <maelstrom|immortalflames|twinadder>\r\n");
      printString("add <n1> <n2>, sub <n1> <n2>\r\n");
      printString("mul <n1> <n2>, div <n1> <n2>\r\n");
      printString("info, yogurt, clear, help\r\n");

    } else {
        if (buffer[0] != '\0') {
        printString(buffer);
        printString("\r\n");
    }
  }
}
