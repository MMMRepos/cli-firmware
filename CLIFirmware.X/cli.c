/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include <stdint.h>
#include <string.h>
#include "mcc_generated_files/drivers/uart.h"

#define MAX_COMMAND_SIZE    (100U)

static bool isCommandReceived = false;
static char command[MAX_COMMAND_SIZE];  
static const char hello[] = "Received Hello";
static const char goodBye[] = "Received Good Bye";
static const char holdPlease[] = "Received Hold Please";  
static uint8_t index = 0;

static void sendHelloCmdResponse(char *pArg);
static void sendGoodByeCmdResponse(char *pArg);
static void sendHoldPleaseCmdResponse(char *pArg);
static void processCommand(char *commandText);

struct cmd
{
    const char * const command;
    void (* const handler)(char *argument);
};

const struct cmd commands[] =
{
    {"Hello, it is nice to meet you.",                 sendHelloCmdResponse},
    {"I need to run; but it has been great talking.",  sendGoodByeCmdResponse},
    {"Excuse me a moment, someone else is here.",      sendHoldPleaseCmdResponse}
};

static void sendHelloCmdResponse(char *pArg)
{
    (void)pArg;
    uint8_t length = strlen(hello);
    uint8_t i = 0;
    
    for(i = 0; i < length; i++)
    {
        uart[CLI].Write(hello[i]);
    }
    uart[CLI].Write('\n');
}

static void sendGoodByeCmdResponse(char *pArg)
{
    (void)pArg;
    uint8_t length = strlen(goodBye);
    uint8_t i = 0;
    
    for(i = 0; i < length; i++)
    {
        uart[CLI].Write(goodBye[i]);
    }
    uart[CLI].Write('\n');
}

static void sendHoldPleaseCmdResponse(char *pArg)
{
    (void)pArg;
    uint8_t length = strlen(holdPlease);
    uint8_t i = 0;
    
    for(i = 0; i < length; i++)
    {
        uart[CLI].Write(holdPlease[i]);
    }
    uart[CLI].Write('\n');
}

static void processCommand(char *commandText)
{   
    uint8_t comparison;
    uint8_t commandTextLength;
    uint8_t storedCommandLength;
    uint8_t cmdIndex = 0;
    
    for (cmdIndex = 0; cmdIndex < sizeof(commands)/sizeof(*commands); cmdIndex++)
    {
        comparison = strcmp(commandText, commands[cmdIndex].command);
        commandTextLength = strlen(commandText);        
        storedCommandLength = strlen(commands[cmdIndex].command);

        if (comparison == 0 && commandTextLength == storedCommandLength)
        {
            if (commands[cmdIndex].handler != NULL)
            {
                commands[cmdIndex].handler(commandText);
                return;
            }
        }
    }
}

void cliHandler(void)
{
    char c = 0;

    while(uart[CLI].DataReady() && !isCommandReceived)
    {
        c = uart[CLI].Read();
        if((c == '\r') || (c == '\n'))
        {
            // process the command
            if((c == '\r') || (c == '\n'))
            {
                command[index] = 0;
                processCommand((char*)command);
                index = 0;
            }
        }
        else
        {
            // store the characters in a command in the comand buffer
            if(index < MAX_COMMAND_SIZE)
            {
               command[index++] = c;
            }
        }
    }
}
