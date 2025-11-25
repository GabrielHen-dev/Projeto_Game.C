#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "keyboard.h"
#include "minigame_roleta.h"
#include "musica.h"


typedef struct {
    const char* enunciado;
    char respostaCorreta; 
} Pergunta;

typedef enum {
    ATIRADOR_JOGADOR,
    ATIRADOR_PROFESSOR
} Atirador;

typedef enum {
    TURNO_JOGADOR,
    TURNO_PROFESSOR
} Turno;

typedef struct {
    int balaRealIndex; // posição da bala real (0..5)
    int tiroAtual;     // quantos tiros ja foram dados (0..5)
} Revolver;

static Revolver revJogador;
static Revolver revProfessor;

//Revolveres e tiros

static void initRevolver(Revolver* r)
{
    r->balaRealIndex = rand() % 6; // uma das 6 camaras tem a bala real
    r->tiroAtual = 0;
}

static int executarTiro(Atirador quem,Revolver* r, NPC* prof)
{
    if (r->tiroAtual >= 6) {
        return 0; // ja passou das 6 camaras, ninguem morre aqui
    }

    int morreu = (r->tiroAtual == r->balaRealIndex);

    screenClearInside();
    screenSetColor(WHITE, BLACK);

    if (morreu) {
        if (quem == ATIRADOR_JOGADOR) {
            screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 6);
            printf("CLICK... BANG! Voce tomou o tiro.");
        } else {
            screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 6);
            printf("CLICK... BANG! %s tomou o tiro.", prof->nome);
        }
    } else {
        if (quem == ATIRADOR_JOGADOR) {
            screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 6);
            printf("CLICK! Voce sobreviveu.");
        } else {
            screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 6);
            printf("CLICK! %s sobreviveu.", prof->nome);
        }
    }

    screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 8);
    screenSetColor(LIGHTGRAY, BLACK);
    printf("Pressione ENTER para continuar.");
    screenUpdate();

    while (1)
    {
        if (keyhit()) {
            int c = readch();
            if (c == '\n' || c == '\r')
                break;
        }
    }

    r->tiroAtual++;   // esse revolver gastou uma câmara

    return morreu;
}


//bloco de perguntas
static Pergunta perguntas[] = {
    {
        "1) Se todo programador da Cali gosta de C e Heitor e programador da Cali,\n"
        "o que podemos concluir?\n"
        "A) Heitor odeia C\n"
        "B) Heitor pode gostar ou nao gostar de C\n"
        "C) Heitor gosta de C\n"
        "D) Nenhum programador da Cali gosta de C\n",
        'C'
    },
    {
        "2) Se alguns alunos sao jogadores de xadrez e todo jogador de xadrez gosta de logica,\n"
        "entao:\n"
        "A) Todos os alunos gostam de logica\n"
        "B) Nenhum aluno gosta de logica\n"
        "C) Alguns alunos gostam de logica\n"
        "D) Ninguem gosta de logica\n",
        'C'
    },
    {
        "3) Hoje e quarta-feira. Daqui a 10 dias sera:\n"
        "A) Sabado\n"
        "B) Domingo\n"
        "C) Segunda-feira\n"
        "D) Terca-feira\n",
        'B' // 10 % 7 = 3 -> quarta + 3 = domingo
    },
    {
        "4) Se A implica B (Se A entao B) e A e falso,\n"
        "o que podemos dizer sobre B?\n"
        "A) B e verdadeiro\n"
        "B) B e falso\n"
        "C) Nao podemos concluir nada sobre B\n"
        "D) A e B sao verdadeiros\n",
        'C'
    },
    {
        "5) Em uma fila estao: Ana, Bruno, Carla e Diego nessa ordem.\n"
        "Se Diego ficar na frente de Ana, a ordem pode ser:\n"
        "A) Diego, Ana, Bruno, Carla\n"
        "B) Ana, Diego, Bruno, Carla\n"
        "C) Bruno, Diego, Ana, Carla\n"
        "D) Carla, Ana, Bruno, Diego\n",
        'A'
    },
    {
        "6) Uma proposicao e:\n"
        "\"Se chove, entao levo guarda-chuva\".\n"
        "Qual das opcoes torna a proposicao falsa?\n"
        "A) Chove e eu levo guarda-chuva\n"
        "B) Chove e eu NAO levo guarda-chuva\n"
        "C) Nao chove e eu levo guarda-chuva\n"
        "D) Nao chove e eu nao levo guarda-chuva\n",
        'B'
    },
    {
        "7) Uma serie: 2, 4, 8, 16, ... O proximo numero e:\n"
        "A) 20\n"
        "B) 24\n"
        "C) 30\n"
        "D) 32\n",
        'D'
    },
    {
        "8) Se todos os professores gostam de explicar e alguns professores gostam de jogos,\n"
        "entao:\n"
        "A) Todos que gostam de jogos sao professores\n"
        "B) Nenhum professor gosta de jogos\n"
        "C) Alguns professores gostam de explicar e de jogos\n"
        "D) Ninguem gosta de jogos\n",
        'C'
    },
    {
        "9) Em um baralho reduzido ha cartas numeradas 1,2,3,4.\n"
        "A probabilidade de tirar uma carta par e:\n"
        "A) 1/4\n"
        "B) 1/3\n"
        "C) 1/2\n"
        "D) 3/4\n",
        'C'
    },
    {
        "10) Se \"Todo aluno da Cali joga Habbo\" e falso,\n"
        "entao isso significa que:\n"
        "A) Nenhum aluno da Cali joga Habbo\n"
        "B) Alguns alunos da Cali nao jogam Habbo\n"
        "C) Todos alunos da Cali jogam Habbo\n"
        "D) Nao ha alunos na Cali\n",
        'B'
    },
    {
        "11) Serie: 5, 10, 20, 40, ... O proximo numero e:\n"
        "A) 45\n"
        "B) 60\n"
        "C) 80\n"
        "D) 100\n",
        'C'
    },
    {
        "12) Se uma frase e: \"P ou Q\" (P OU Q) e sabemos que P e falsa,\n"
        "para a frase ser verdadeira e necessario que:\n"
        "A) Q seja verdadeira\n"
        "B) Q seja falsa\n"
        "C) P seja verdadeira\n"
        "D) P e Q sejam falsas\n",
        'A'
    },
    {
        "13) Em uma sala, todos que usam oculos gostam de livros.\n"
        "Joao gosta de livros, mas nao usa oculos.\n"
        "Logo:\n"
        "A) Joao nao pode gostar de livros\n"
        "B) Joao e obrigado a usar oculos\n"
        "C) Joao e um contra-exemplo da regra\n"
        "D) Joao nao contradiz a regra\n",
        'D'
    },
    {
        "14) Serie: 1, 1, 2, 3, 5, 8, ... O proximo numero e:\n"
        "A) 11\n"
        "B) 12\n"
        "C) 13\n"
        "D) 15\n",
        'C'
    },
    {
        "15) Se \"Se eu estudo, entao passo\" e verdadeiro,\n"
        "e eu NAO passei,\n"
        "entao:\n"
        "A) Eu estudei\n"
        "B) Eu nao estudei\n"
        "C) Estudei e passei\n"
        "D) A frase e falsa\n",
        'B'
    },
    {
        "16) Numa turma, alguns alunos sao brasileiros e todos os brasileiros gostam de ferias.\n"
        "Logo:\n"
        "A) Todos alunos gostam de ferias\n"
        "B) Nenhum aluno gosta de ferias\n"
        "C) Alguns alunos gostam de ferias\n"
        "D) Ninguem e brasileiro\n",
        'C'
    },
    {
        "17) Serie: 9, 7, 5, 3, ... O proximo numero e:\n"
        "A) 0\n"
        "B) 1\n"
        "C) 2\n"
        "D) -1\n",
        'B' // -2 cada vez: 9,7,5,3,1...
    },
    {
        "18) Se nenhum professor falta as aulas e hoje um professor faltou,\n"
        "podemos concluir que:\n"
        "A) A afirmacao \"nenhum professor falta\" era falsa\n"
        "B) A afirmacao continua verdadeira\n"
        "C) Todos professores faltaram\n"
        "D) Nada pode ser concluido\n",
        'A'
    },
    {
        "19) A negacao de \"Todos os alunos passaram\" e:\n"
        "A) Nenhum aluno passou\n"
        "B) Alguns alunos nao passaram\n"
        "C) Todos os alunos reprovaram\n"
        "D) Nao ha alunos\n",
        'B'
    },
    {
        "20) Serie: 3, 6, 9, 12, 15, ... O proximo numero e:\n"
        "A) 17\n"
        "B) 18\n"
        "C) 19\n"
        "D) 21\n",
        'B'
    },
    {
        "21) Se P: \"Chove\" e Q: \"Levo guarda-chuva\",\n"
        "a frase \"Nao chove E levo guarda-chuva\" corresponde a:\n"
        "A) ~P E Q\n"
        "B) P E ~Q\n"
        "C) P OU Q\n"
        "D) ~P OU Q\n",
        'A'
    },
    {
        "22) Um numero e multiplo de 6 se for multiplo de 2 e de 3.\n"
        "O numero 18 e:\n"
        "A) Multiplo de 2, mas nao de 3\n"
        "B) Multiplo de 3, mas nao de 2\n"
        "C) Multiplo de 2 e de 3\n"
        "D) Nao e multiplo de 2 nem de 3\n",
        'C'
    },
    {
        "23) Serie: 2, 5, 10, 17, 26, ... O proximo numero e:\n"
        "A) 31\n"
        "B) 35\n"
        "C) 37\n"
        "D) 38\n",
        'D' // +3,+5,+7,+9,+11...
    },
    {
        "24) Se todo jogador de poker e calmo e alguns jogadores de poker sao professores,\n"
        "entao:\n"
        "A) Todos professores sao calmos\n"
        "B) Alguns professores podem ser calmos\n"
        "C) Nenhum professor e calmo\n"
        "D) Ninguem e calmo\n",
        'B'
    },
    {
        "25) A negacao de \"P OU Q\" e logicamente equivalente a:\n"
        "A) Nao P OU nao Q\n"
        "B) Nao P E nao Q\n"
        "C) P E Q\n"
        "D) P implica Q\n",
        'B'
    },
    {
        "26) Num grupo, todos que jogam Habbo usam computador.\n"
        "Luis usa computador.\n"
        "Podemos concluir que:\n"
        "A) Luis joga Habbo\n"
        "B) Luis nao joga Habbo\n"
        "C) Luis pode ou nao jogar Habbo\n"
        "D) Ninguem joga Habbo\n",
        'C'
    },
    {
        "27) Serie: 100, 90, 81, 73, ... O proximo numero e:\n"
        "A) 66\n"
        "B) 65\n"
        "C) 64\n"
        "D) 63\n",
        'A' // -10,-9,-8,-7...
    },
    {
        "28) Se \"Se estudo, entao tiro nota boa\" e falso,\n"
        "entao aconteceu o que?\n"
        "A) Estudei e tirei nota boa\n"
        "B) Nao estudei e tirei nota boa\n"
        "C) Estudei e NAO tirei nota boa\n"
        "D) Nao estudei e nao tirei nota boa\n",
        'C'
    },
    {
        "29) Em um enigma, sabemos que:\n"
        "\"Se a porta 1 e verdadeira, a porta 2 e falsa\".\n"
        "Se a porta 2 for verdadeira, entao:\n"
        "A) A porta 1 e verdadeira\n"
        "B) A porta 1 e falsa\n"
        "C) As duas sao verdadeiras\n"
        "D) As duas sao falsas\n",
        'B'
    },
    {
        "30) Serie: 4, 9, 16, 25, ... O proximo numero e:\n"
        "A) 30\n"
        "B) 35\n"
        "C) 36\n"
        "D) 49\n",
        'C' // quadrados perfeitos: 2^2,3^2,4^2,5^2,6^2
    }
}; 

#define QTD_PERGUNTAS ( (int)(sizeof(perguntas) / sizeof(perguntas[0])) )

static int ordemPerguntas[QTD_PERGUNTAS];

static void embaralharPerguntas(void)
{
    for (int i = 0; i < QTD_PERGUNTAS; i++) {
        ordemPerguntas[i] = i;
    }

    for (int i = QTD_PERGUNTAS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = ordemPerguntas[i];
        ordemPerguntas[i] = ordemPerguntas[j];
        ordemPerguntas[j] = tmp;
    }
}


// auxiliares de perguntas
static char lerRespostaAlternativa(void)
{
    while (1)
    {
        if (keyhit())
        {
            int c = readch();
            if (c >= 'a' && c <= 'z') c -= 32; // minuscula -> maiuscula

            if (c == 'A' || c == 'B' || c == 'C' || c == 'D')
                return (char)c;
        }
    }
}

static void pausarMensagemAposPergunta(void)
{
    screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 20);
    screenSetColor(LIGHTGRAY, BLACK);
    printf("Pressione ENTER para ver o tiro...");
    screenUpdate();
    
    while (1)
    {
        if (keyhit())
        {
            int c = readch();
            if (c == '\n' || c == '\r')
                break;
        }
    }
}

static void printMultilineAt(int x, int y, const char* text)
{
    int cx = x;
    int cy = y;

    for (const char* p = text; *p; p++)
    {
        if (*p == '\n')
        {
            cy++;          // proxima linha
            cx = x;        // volta para a coluna inicial
        }
        else
        {
            screenGotoxy(cx, cy);
            putchar(*p);
            cx++;
        }
    }
}

// função principal do minigame

void minigameRoleta(NPC* prof)
{
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }

    initRevolver(&revJogador);
    initRevolver(&revProfessor);
    embaralharPerguntas();


    int rodada = 0;
    int jogoAtivo = 1;
    Turno turno = (rand() % 2 == 0) ? TURNO_JOGADOR : TURNO_PROFESSOR;

    while(jogoAtivo &&
       revJogador.tiroAtual < 6 &&
       revProfessor.tiroAtual < 6)
    {
        int idxPerg = ordemPerguntas[rodada % QTD_PERGUNTAS];
        Pergunta* q = &perguntas[idxPerg];

        screenClearInside();
        screenSetColor(YELLOW, BLACK);
        screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 2);
        printf("ROLETA RUSSA DE LOGICA - Contra %s", prof->nome);

        screenSetColor(WHITE, BLACK);
        screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 5);
        printf("Rodada %d  |  Seus tiros: %d/6  |  Tiros de %s: %d/6",
                rodada + 1,
                revJogador.tiroAtual,
                prof->nome,
                revProfessor.tiroAtual
              );


        screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 7);
        if (turno == TURNO_JOGADOR) {
            printf("SUA VEZ de responder.");
        } else {
            printf("Vez de %s responder (voce escolhe a resposta).", prof->nome);
        }

        if(turno == TURNO_JOGADOR){
            screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 3);
            printf("Acertou: %s puxa o gatilho.", prof->nome);
            screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 4);
            printf("Errou: VOCÊ puxa o gatilho.");

        }else{
            screenSetColor(WHITE, BLACK);
            screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 3);
            printf("Acertou: O player puxa o gatilho.");
            screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 4);
            printf("Errou: VOCÊ puxa o gatilho.");
        }

        int baseX = SCRSTARTX + 4;    
        int baseY = SCRSTARTY + 9;

        screenSetColor(LIGHTGRAY, BLACK);
        screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 9);
        printMultilineAt(baseX,baseY,q->enunciado);

        screenSetColor(CYAN, BLACK);
        screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 16);
        printf("Alternatinas(A, B, C ou D): ");
        screenUpdate();
        
        char resp = lerRespostaAlternativa();

        screenSetColor(WHITE, BLACK);
        screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 17);
        printf("Sua resposta: %c", resp);

        int acertou = (resp == q->respostaCorreta);

        // Mensagem de acerto/erro levando em conta de quem é a vez
        screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 18);
        if (turno == TURNO_JOGADOR) {
            if (acertou) {
                screenSetColor(LIGHTGREEN, BLACK);
                printf("Acertou! %s vai puxar o gatilho.", prof->nome);
            } else {
                screenSetColor(RED, BLACK);
                printf("Errou! VOCE vai puxar o gatilho.");
            }
        } else {
            if (acertou) {
                screenSetColor(LIGHTGREEN, BLACK);
                printf("Acertou! VOCE vai puxar o gatilho.");
            } else {
                screenSetColor(RED, BLACK);
                printf("Errou! %s vai puxar o gatilho.", prof->nome);
            }
        }

        screenUpdate();
        pausarMensagemAposPergunta();

        Atirador quem;
        if (turno == TURNO_JOGADOR) {
            // sua vez de responder
            quem = acertou ? ATIRADOR_PROFESSOR : ATIRADOR_JOGADOR;
        } else {
            // vez do professor responder
            quem = acertou ? ATIRADOR_JOGADOR : ATIRADOR_PROFESSOR;
        }

        //É aqui que entra a lógica dos 2 revolveres
        Revolver* revUsado;
        if (quem == ATIRADOR_JOGADOR)
            revUsado = &revJogador;   // se quem atira é você -> usa seu revólver
        else
            revUsado = &revProfessor; // se quem atira é o prof -> usa o revólver dele

        int morreu = executarTiro(quem, revUsado, prof);

        if (morreu) {
            jogoAtivo = 0;
        } else {
            rodada++;
            // alterna a vez de responder
            turno = (turno == TURNO_JOGADOR) ? TURNO_PROFESSOR : TURNO_JOGADOR;
        }

    }

    if (jogoAtivo &&
       revJogador.tiroAtual >= 6 &&
       revProfessor.tiroAtual >= 6)
    {
        screenClearInside();
        screenSetColor(LIGHTGREEN, BLACK);
        screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 6);
        printf("O tambor girou 6 vezes e a bala real nunca disparou!");

        screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 8);
        screenSetColor(WHITE, BLACK);
        printf("Vocês dois sobreviveram a roleta russa.");

        screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 10);
        screenSetColor(LIGHTGRAY, BLACK);
        printf("Pressione ENTER para voltar ao bar.");
        screenUpdate();

        while (1)
        {
            if (keyhit())
            {
                int c = readch();
                if (c == '\n' || c == '\r')
                    break;
            }
        }
    }

}
