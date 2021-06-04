/*
 * PCD8544.h
 *
 *  Created on: 19 may. 2021
 *      Author: damian
 */
#include <sapi.h>

#ifndef PRE_INGRESO_PROYPCOMM_INC_PCD8544_H_
#define PRE_INGRESO_PROYPCOMM_INC_PCD8544_H_

//Pines
#define PCD8544_RST GPIO0
#define	PCD8544_CE GPIO1
#define	PCD8544_DC GPIO2
/*El resto de los pines son los del SPI*/

//
#define PCD8544_SUCCESS   0
#define PCD8544_ERROR     1
#define isDATA 1
#define isCMD 0

//Constantes del display
#define MAXNROWS      6
#define MAXNCOLS      84
#define SIZEMEM (MAXNROWS * MAXNCOLS)

//Comandos
#define	PCD8544_NOP	0
#define PCD8544_FUNCTIONSET (1<<5)
#define PCD8544_POWERDOWN (1<<2)
#define PCD8544_HORIZONTALADDR 0
#define PCD8544_VERTICALADDR (1<<1)
#define PCD8544_EXTNDINSTRUCTION (1<<0)


/*************Prototipos de funciones*******************/

/*
 *@breif Inicializa el display
 *
 * */
void initPCD8544(void);


/*
 *@brief Resetea el display completamente.
 * */
void resetPCD8544(void);

/**
 * @brief Enviar datos/comandos.
 * @param char
 * @param bool
 * @return void
 */
void writeToPCD8544(uint8_t, bool_t);

/**
 *@brief Borra toda la pantalla
 * */
void clearPCD8544(void);

/*
 *@brief Setea la posición de un pixel.
 * */
void setTxtPosPCD8544(uint8_t, uint8_t);

/*
 * @brief Activa un pixel en una posicion (x,y)
 * */
void drawPxlPCD8544(uint8_t, uint8_t);

void updateScrnPCD8544(void);

void setPxlPosPCD8544(uint8_t, uint8_t);

uint8_t PCD8544_DrawChar(char);


//clearPxlPCD8544(x1,y1,); Borra un pixel
//clearBlockPCD8544(x,y); Borra un bloque
//writeCharPCD8544();
//writeStrPCD8544();
//setCursorPosPCD8544();

//drawLinePCD8544();
//drawCirclePCD8544();
//drawSqaurePCD8544();



#endif /* PRE_INGRESO_PROYPCOMM_INC_PCD8544_H_ */
