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
	   for(int i=0; i<83; i++){
		   drawPxlPCD8544(i,0);
		   delay(50);
	   }
	   for(int i=0; i<43; i++){
		   drawPxlPCD8544(0,i);
		   delay(200);
	   }
	   clearPCD8544();


   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
