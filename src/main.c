/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/


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
