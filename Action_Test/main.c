#include "main.h"

int main()
{
    int input = 0;
    unsigned char buff[256];

    user_uart_open("ttySAC1");
    user_uart_config(4800);

    while (1) {
        printf("Enter a number to choice action(1~16).\n");
        printf("Enter -1 for exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &input);

        if (input == -1) {
            break;
        } else if (input < -1 || input > 16) {
            printf("No no.%d action.\n", input);
            continue;
        }

        Send_Command(input);

        while (!Receive_Command(buff)) ;

        printf("Action over!\n\n");
    }

    user_uart_close();

    return 0;
}
