/**
 * keyboard.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/


#include "keyboard.h"
/*win*/
#ifdef _WIN32
#include <conio.h>

void keyboardInit() {}
void keyboardDestroy() {}

int keyhit() {
    return _kbhit();
}

int readch() {
    return _getch();
}
/*linux e macOS*/
#else
// Usando POSIX termios para controle de terminal no Linux
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <errno.h>

static struct termios original_termios;
static int initialized = 0;

void keyboardInit() {
    if (initialized) return;
    
    struct termios new_termios;

    // Salva as configurações originais do terminal
    tcgetattr(STDIN_FILENO, &original_termios);
    new_termios = original_termios;

    // Configura o terminal para modo cbreak (sem buffer de linha e sem eco)
    new_termios.c_lflag &= ~(ICANON | ECHO); 
    
    // Ler pelo menos 1 caractere (VMIN=1) para evitar leituras "vazias"
    // quando select() reportou dados mas read() retorna 0.
    new_termios.c_cc[VMIN] = 1;
    new_termios.c_cc[VTIME] = 0;

    // Aplica as novas configurações imediatamente
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    initialized = 1;
}

void keyboardDestroy() {
    if (!initialized) return;
    
    // Restaura as configurações originais ao sair
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
    
    initialized = 0;
}

int keyhit() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    
    // Prepara para checar o STDIN
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    
    // select verifica se há dados disponíveis para leitura (non-blocking)
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

int readch() {
    char ch = 0;
    ssize_t n;
    do {
        n = read(STDIN_FILENO, &ch, 1);
    } while (n == -1 && errno == EINTR);

    if (n == 1) return (int)(unsigned char)ch;
    return -1;
}

#endif // FIM DO BLOCO LINUX (que usa termios)
