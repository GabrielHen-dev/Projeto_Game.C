#include "dialogo_dealer.h"

#include <stdio.h>
#include <string.h>

#include "screen.h"
#include "keyboard.h"

#include "cena_selecao.h"


static void limparDialogo()
{
    for (int y = SCRSTARTY + 1; y < SCRENDY; y++)
    {
        screenGotoxy(SCRSTARTX + 1, y);
        for (int x = SCRSTARTX + 1; x < SCRENDX; x++)
            putchar(' ');
    }
}

static void esperarEnter()
{
    while (1)
    {
        if (keyhit() && readch() == 10)
            return;
    }
}

static char esperarOpcao()
{
    while (1)
    {
        if (keyhit())
        {
            int c = readch();
            if (c == 'a' || c == 'A') return 'A';
            if (c == 'b' || c == 'B') return 'B';
            if (c == 'c' || c == 'C') return 'C';
            if (c == 'd' || c == 'D') return 'D';
        }
    }
}

char dialogoDealer()
{
    limparDialogo();

    screenSetColor(YELLOW, BLACK);
    screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 2);
    printf("=== Araujo, o Dealer ===");

    screenSetColor(WHITE, BLACK);
    screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 4);
    printf("Opa meu jovem...");

    screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 6);
    printf("E ai, qual vai ser hoje?");

    screenSetColor(CYAN, BLACK);
    screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 8);
    printf("A) Jogar");

    screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 9);
    printf("B) Beber");

    screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 10);
    printf("C) Conversar");

    screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 11);
    printf("D) Ir embora");

    screenUpdate();

    char escolha = esperarOpcao();

    switch (escolha)
    {
        case 'A':
            limparDialogo();

            screenSetColor(LIGHTGREEN, BLACK);
            screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 3);
            printf("Araujo: Hehe... gosto assim, espirito competitivo.");

            screenSetColor(WHITE, BLACK);
            screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 5);
            printf("Escolha sua mesa, cada uma tem um mestre diferente:");
            screenUpdate();

            int escolhaIdx = cenaSelecao();
            if (escolhaIdx < 0)
            {
                limparDialogo();
                screenSetColor(LIGHTGRAY, BLACK);
                screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 4);
                printf("Ok, volta pro bar.");
                screenUpdate();
                esperarEnter();
                return 'X';
            }

            char mesa = 'A' + (char)escolhaIdx;
            limparDialogo();

            screenSetColor(LIGHTGREEN, BLACK);

            switch (mesa)
            {
                case 'A':
                    screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 4);
                    printf("Araujo: Vai encarar o Guilherme? Corajoso, hein.");
                    break;

                case 'B':
                    screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 4);
                    printf("Araujo: Diego e ligeiro... boa escolha.");
                    break;

                case 'C':
                    screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 4);
                    printf("Araujo: Baudel joga calado, mas acerta pesado.");
                    break;

                case 'D':
                    screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 4);
                    printf("Araujo: Lucas e frio... cuidado.");
                    break;
            }

            screenSetColor(LIGHTGRAY, BLACK);
            screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 7);
            printf("Pressione ENTER para seguir.");

            screenUpdate();
            esperarEnter();
            return mesa;

        case 'B':
            limparDialogo();

            screenSetColor(LIGHTBLUE, BLACK);
            screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 3);
            printf("Araujo: Bebida sempre cai bem... depende do humor.");

            screenSetColor(CYAN, BLACK);
            screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 5);
            printf("A) Cerveja");

            screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 6);
            printf("B) Refrigerante");

            screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 7);
            printf("C) Agua");

            screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 8);
            printf("D) Melhor deixar quieto");

            screenUpdate();

            char drink = esperarOpcao();

            limparDialogo();
            screenSetColor(LIGHTBLUE, BLACK);

            screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 4);

            switch (drink)
            {
                case 'A': 
                    printf("Araujo: Cerveja gelada na faixa. Aproveita!"); 
                    break;
                case 'B': 
                    printf("Araujo: Refri docinho, estilo retro."); 
                    break;
                case 'C': 
                    printf("Araujo: Água... saúde em primeiro lugar."); 
                    break;
                case 'D': 
                    printf("Araujo: Beleza. Sem pressao."); 
                    break;
            }

            screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 7);
            screenSetColor(LIGHTGRAY, BLACK);
            printf("ENTER para voltar.");

            screenUpdate();
            esperarEnter();
            return 'X';

        case 'C':
            limparDialogo();

            screenSetColor(LIGHTMAGENTA, BLACK);
            screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 3);
            printf("Araujo: Conversar? Haha... normalmente a galera so joga.");

            screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 5);
            printf("Mas manda ai... se apresenta, guerreiro.");

            screenSetColor(LIGHTGRAY, BLACK);
            screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 8);
            printf("ENTER para voltar.");

            screenUpdate();
            esperarEnter();
            return 'X';

        case 'D':
            limparDialogo();
            screenSetColor(WHITE, BLACK);

            screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 5);
            printf("Araujo: Tranquilo... porta é logo ali. Volte sempre!");

            screenSetColor(LIGHTGRAY, BLACK);
            screenGotoxy(SCRSTARTX + 3, SCRSTARTY + 8);
            printf("ENTER para sair.");

            screenUpdate();
            esperarEnter();
            return 'X';

        default:
            return 'X';
    } 
}