/*
 * PCD8544.c
 *
 *  Created on: 19 may. 2021
 *      Author: Damián Captuo
 */

#include <PCD8544.h>
#include <font.h>

// @var Memoria cache 6*84 = 504
static uint8_t cacheMemLcd[SIZEMEM];


// @var Indice de la memoeria cache
uint16_t cacheMemIndex = 0;

/*
 * @brief Inicializar los puertos necesarios y el display
 */
void initPCD8544(){

	//Inicializo los pines
	gpioInit(RST_PCD8544, GPIO_OUTPUT);
	gpioInit(DC_PCD8544, GPIO_OUTPUT);
	gpioInit(CE_PCD8544, GPIO_OUTPUT);

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
 */
void resetPCD8544(){
	delay(1);

	//Reset
	gpioWrite(CE_PCD8544, OFF);
	gpioWrite(RST_PCD8544, OFF);
	delay(1);
	gpioWrite(RST_PCD8544, ON);
	gpioWrite(CE_PCD8544, ON);
}

/*
 * @brief Enviar datos/comandos.
 * @param data El comando o el dato a enviar al LCD.
 * @param isData Booleano para indicar si es dato(1) o comando(0).
 * @return void
 */
void writeToPCD8544(uint8_t data, bool_t isData){

	gpioWrite(CE_PCD8544, OFF);
	if(isData){
		//Si enviamos un dato.
		gpioWrite(DC_PCD8544, ON); //1 al pin de D/negC

		spiWrite(SPI0, &data, 1 );
	}
	else{
		//Si enviamos un comando.
		gpioWrite(DC_PCD8544, OFF); //0 al pin de D/negC
		spiWrite(SPI0, &data, 1 );
	}
	gpioWrite(CE_PCD8544, ON);
}

/*
 * @brief Borra toda la pantalla.
 */
void clearPCD8544(void){
	//Posicion (0,0)
	setTxtPosPCD8544(0,0);

	//Recorre pxl por pxl reseteandolo
	for (uint16_t pixel=(SIZEMEM); pixel > 0; pixel--) {
		cacheMemLcd[pixel] = 0x00;
	    writeToPCD8544(0x00, isDATA);
	  }

	 writeToPCD8544(0x40, isCMD);
	 writeToPCD8544(0x80, isCMD);
}

/*
 * @brief Actualiza la pantalla del display con lo cargado en la memoria cache
 * */
void updateScrnPCD8544(void){
	uint16_t i;

	//Posisción (0,0) del LCD.
	setTxtPosPCD8544(0,0);

	//Pasa lo que tengo en la memoria cache al LCD
	for(i=0; i<SIZEMEM; i++){
		writeToPCD8544(cacheMemLcd[i], isDATA);
	}

}

/*
 * @brief Setea la posición del texto
 * @param x entero indicando la posicion x del pixel 0 <= x <= 5 filas
 * @param y entero indicando la posicion x del pixel 0 <= y <= 14 columnas
 * */
void setTxtPosPCD8544(uint8_t x, uint8_t y){

	//set de instrucciones normal
	//direccionamiento horizontal
	writeToPCD8544(0x20,isCMD);

	//Posición x
	writeToPCD8544(0x80 | x,isCMD);
	//Posición y
	writeToPCD8544(0x20 | (y*6),isCMD);

	cacheMemIndex = (y*6) + (x*MAXNCOLS);
}

/*
 * @brief Setea la posición del pixel..
 * @param x entero indicando la posicion x del pixel 0 < x < 83
 * @param y entero indicando la posicion x del pixel 0 < y < 47
 **/
void setPxlPosPCD8544(uint8_t x, uint8_t y){

	//set de instrucciones normal
	//direccionamiento horizontal
	writeToPCD8544(0x20,isCMD);

	//Posición x
	writeToPCD8544(0x80 | y, isCMD);
	//Posición x
	writeToPCD8544(0x20 | (x/6), isCMD);

	cacheMemIndex = x + ((y / 8)*MAXNCOLS);
}

/*
 *@brief Dibuja un pixel individual.
 *@param x entero indicando la posición x del pixel a setear.
 *@param y entero indicando la posición y del pixel a setear.
 */
void drawPxlPCD8544(uint8_t x, uint8_t y){
	setPxlPosPCD8544(x,y);
	cacheMemLcd[cacheMemIndex] |= 1<<(y % 8);
}

/*
 *@brief Escribe un caracter en pantalla.
 *@param character caracter a escribir.
 * */
uint8_t wrtCharPCD8544(char character)
{
  uint8_t i = 0;
  // check if character is out of range
  if ((character < 0x20) &&
      (character > 0x7f)) {
    // out of range
    return 0;
  }

  // loop through 5 bytes
  for (i = 0; i < 5; i++) {
    // read from ROM memory
    cacheMemLcd[cacheMemIndex++] = (FONTS[character - 32][i]);
  }
  //
  cacheMemIndex++;
  // return exit
  return 0;
}

/*
 *@brief Escribe una cadena de caracteres en pantalla.
 *@param str Puntero al array de caracteres.
 */
void wrtStrPCD8544(char *str){
	uint8_t i = 0;

	while(str[i] != 0){
		wrtCharPCD8544(str[i++]);
	}
}

void invClrPCD8544(bool_t inv){
	//Set de instrucciones reducido
	writeToPCD8544(0x20,isCMD);
	if(inv){writeToPCD8544(0x0D, isCMD);}
	else{writeToPCD8544(0x0C, isCMD);}
}

void setAllPxlPCD8544(bool_t all){
	writeToPCD8544(0x20,isCMD);

	if(all){writeToPCD8544(0x09, isCMD);}
	else{writeToPCD8544(0x08, isCMD);}
}

/*
 *@brief Dibuja una imagen cargada en font.c
 *@param img Puntero a la imagen cargada en font.c
 */

void drawImgPCD8544(uint8_t *img){
	uint16_t i;

	//Posiciona el puntero de memoria de LCd en posicion 0.
	writeToPCD8544(0x40, isCMD);
	writeToPCD8544(0x80, isCMD);

	for (i = 0; i < SIZEMEM; i++){
			cacheMemLcd[i] = img[i];
	}

	//Posiciona el puntero de memoria de LCd en posicion 0.
	writeToPCD8544(0x80, isCMD);
	writeToPCD8544(0x40, isCMD);
}
