/*=============================================================================
 * Author: Damian Caputo <damcapu@gmail.com>
 * Date: 2021/05/19
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "ProyPComm.h"
#include "PCD8544.h"
#include "sapi.h"
#include "font.h"


/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
   // ----- Setup -----------------------------------
   boardInit();
   initPCD8544();

   clearPCD8544();

   //Dibuja logo de FIUBA
   drawImgPCD8544(&logoFIUBA);

   setTxtPosPCD8544(1,0);
   wrtStrPCD8544("Univ. Bs. As.");

   updateScrnPCD8544();
   delay(2000);

   clearPCD8544();

   while( true ) {
	   /*Mostrar todos los caracteres*/
	   setTxtPosPCD8544(0,0);
	   wrtStrPCD8544("Caracteres");
	   updateScrnPCD8544();
	   delay(2000);
	   wrtStrPCD8544("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwzyz0123456789!#$%&'()*+/:;<=>?@{}[]");
	   updateScrnPCD8544();
	   delay(2000);
	   clearPCD8544();

	   /*Borrar un bloque de texto*/
	   setTxtPosPCD8544(0,0);
	   wrtStrPCD8544("Borrar 3 charsfila 3 pos 4");
	   updateScrnPCD8544();
	   delay(2000);


	   setTxtPosPCD8544(0,0);
	   wrtStrPCD8544("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwzyz0123456789!#$%&'()*+/:;<=>?@{}[]");
	   updateScrnPCD8544();
	   clrTxtPosPCD8544(3,2,3);
	   updateScrnPCD8544();
	   delay(2000);
	   clearPCD8544();

	   /*Encender un pixel*/
	   setTxtPosPCD8544(0,0);
	   wrtStrPCD8544("Encender pixel(41,23)");
	   updateScrnPCD8544();
	   delay(2000);
	   clearPCD8544();
	   drawPxlPCD8544(41,23);
	   updateScrnPCD8544();
	   delay(2000);
	   clearPCD8544();

	   /*Encender todos los pixels*/
	   setTxtPosPCD8544(0,0);
	   wrtStrPCD8544("Encender todoslos pixels");
	   updateScrnPCD8544();
	   delay(2000);
	   setAllPxlPCD8544(SETALLTRUE);
	   delay(2000);
	   setAllPxlPCD8544(SETALLFALSE);
	   clearPCD8544();

	   /*Invertir colores*/
	   setTxtPosPCD8544(0,0);
	   wrtStrPCD8544("Invertir color");
	   updateScrnPCD8544();
	   delay(2000);
	   invClrPCD8544(INVTRUE);
	   delay(2000);
	   invClrPCD8544(INVFALSE);
	   delay(2000);
	   clearPCD8544();

	   /*Mostrar imagen*/
	   setTxtPosPCD8544(0,0);
	   wrtStrPCD8544("Mostrar imagen");
	   updateScrnPCD8544();
	   delay(2000);
	   drawImgPCD8544(&Zelda);
	   updateScrnPCD8544();
	   delay(2000);
	   clearPCD8544();

   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
