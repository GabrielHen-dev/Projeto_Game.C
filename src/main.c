#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "cena_intro.h"
#include "cena_rua.h"
#include "cena_bar.h"
#include "dialogo_dealer.h"


int main()
{
    keyboardInit();

    screenInit(1);     //limpa tudo
    cenaIntro();       

    screenInit(1);     
    cenaRua();         

    screenInit(1);
    cenaBar();

    keyboardDestroy();
    screenDestroy();
    return 0;
}
