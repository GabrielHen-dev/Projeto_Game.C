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
    screenInit(1);   

    cenaIntro();
    cenaRua();
    cenaBar();

    screenDestroy();
    keyboardDestroy();
    return 0;
}
