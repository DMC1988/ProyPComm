/*
 * PCD8544.c
 *
 *  Created on: 19 may. 2021
 *      Author: damian
 */

#include <PCD8544.h>

// @var array Chache memory Lcd 6 * 84 = 504 bytes
static char cacheMemLcd[SIZEMEM];

// @var array Chache memory char index
int cacheMemIndex = 0;

/*
 * @brief Inicializar los puertos necesarios y el displai
 * */
void initPCD8544(/*Ver si dsps pongo algun argumento*/){

	//Inicializo los pines
	gpioInit(PCD8544_RST, GPIO_OUTPUT);
	gpioInit(PCD8544_DC, GPIO_OUTPUT);
	gpioInit(PCD8544_CE, GPIO_OUTPUT);

	//Inicializo el SP
	spiConfig( SPI0 );

	//Reset del LCD.
	resetPCD8544();

	//Set de instrucciones extendido
	//Direccionamiento horizontal
	writeToPCD8544(0x21,isCMD);	//0b00100001

	//Seteo de temperatura - coeficiente de temperatura del IC
	writeToPCD8544(0x06,isCMD);

	//Valor de polarizacion bias 1:48
	writeToPCD8544(0x13,isCMD);

	// for mux 1:48 optimum operation voltage is Ulcd = 6,06.Uth
	// Ulcd = 3,06 + (Ucp6 to Ucp0).0,06
	// 6 < Ulcd < 8,05
	// command for operation voltage = 0x1 Ucp6 Ucp5 Ucp4 Ucp3 Ucp2 Ucp1 Ucp0
	// Ulcd = 0x11000010 = 7,02 V
	writeToPCD8544(0xC2,isCMD);

	// normal instruction set
	// horizontal adressing mode
	writeToPCD8544(0x20,isCMD);

	// normal mode
	writeToPCD8544(0x0C,isCMD);

}

/*
 * @brief Reset del display LCD
 * */
void resetPCD8544(){
	delay(1);

	//Reset
	gpioWrite(PCD8544_CE, OFF);
	gpioWrite(PCD8544_RST, OFF);
	delay(1);
	gpioWrite(PCD8544_RST, ON);
	gpioWrite(PCD8544_CE, ON);
}

/*
 * @brief Enviar datos/comandos.
 * @param data El comando o el dato a enviar al LCD.
 * @param isData Booleando para indicar si es dato(1) o comando(0).
 * @return void
 */
void writeToPCD8544(uint8_t data, bool_t isData){ //Esta ya funciona. Comprobada con el SOFT envia lo que corresponde.

	gpioWrite(PCD8544_CE, OFF);
	if(isData){
		//Si enviamos un dato.
		gpioWrite(PCD8544_DC, ON); //1 al pin de D/negC

		spiWrite(SPI0, &data, 1 );
	}
	else{
		//Si enviamos un comando.
		gpioWrite(PCD8544_DC, OFF); //0 al pin de D/negC
		spiWrite(SPI0, &data, 1 );
	}
	gpioWrite(PCD8544_CE, ON);
}

/*
 * @brief Borra toda la pantalla.
 */
void clearPCD8544(void){
	//Posicion (0,0)
	setPxlPosPCD8544(0,0);

	//Recorre pxl por pxl reseteandolo
	for (int pixel=(SIZEMEM); pixel > 0; pixel--) {
	    writeToPCD8544(0x00, isDATA);
	  }
}

/*
 * @bried Setea la posición de un pixel.
 * */
void setPxlPosPCD8544(uint8_t x, uint8_t y){

	//set de instrucciones normal
	//direccionamiento horizontal
	writeToPCD8544(0x20,isCMD);

	//Posición y
	writeToPCD8544((0x40 | (y%8)),isCMD);
	//Posición x
	writeToPCD8544((0x80 | x),isCMD);

}


/*
 *
 * */
void drawPxlPCD8544(uint8_t x, uint8_t y){
	uint8_t banco;

	//determina el banco vertical.
	banco = y/8;

	//set de instrucciones normal
	//direccionamiento horizontal
	writeToPCD8544(0x20,isCMD);

	//Posición y
	writeToPCD8544((0x40 | banco),isCMD);
	//Posición x
	writeToPCD8544((0x80 | x),isCMD);

	//determina que pixel setear dentro del banco vertical
	writeToPCD8544(1<<(y-(8*banco-1)), isDATA);

}
