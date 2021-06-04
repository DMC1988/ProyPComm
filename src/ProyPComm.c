/*=============================================================================
 * Author: Damian Caputo <damcapu@gmail.com>
 * Date: 2021/05/19
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "ProyPComm.h"
#include "PCD8544.h"
#include "sapi.h"

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


   while( true ) {
		   for(int i=0; i<MAXNCOLS; i++){
			   PCD8544_DrawChar('D');
			   PCD8544_DrawChar('o');
			   PCD8544_DrawChar('g');
			   PCD8544_DrawChar('e');
			   PCD8544_DrawChar(' ');
			   PCD8544_DrawChar('S');
			   PCD8544_DrawChar('h');
			   PCD8544_DrawChar('i');
			   PCD8544_DrawChar('b');
			   PCD8544_DrawChar('a');
			   updateScrnPCD8544();
			   delay(100);
		   }


   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
