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
#define RST_PCD8544 GPIO0
#define	CE_PCD8544 GPIO1
#define	DC_PCD8544 GPIO2
/*El resto de los pines son los del SPI*/

//
#define PCD8544_SUCCESS   0
#define PCD8544_ERROR     1
#define isDATA 1
#define isCMD 0
#define INVTRUE 1
#define INVFALSE 0
#define SETALLTRUE 1
#define SETALLFALSE 0

//Constantes del display
#define MAXNROWS      6
#define MAXNCOLS      84
#define SIZEMEM (MAXNROWS * MAXNCOLS)


/*************Prototipos de funciones*******************/

/*
 *@breif Inicializa el display.
 */
void initPCD8544(void);

/*
 *@brief Resetea el display.
 */
void resetPCD8544(void);

/*
 * @brief Enviar datos/comandos.
 * @param char
 * @param bool
 * @return void
 */
void writeToPCD8544(uint8_t, bool_t);

/*
 *@brief Borra toda la pantalla.
 */
void clearPCD8544(void);

/*
 *@brief Setea la posición de un caracter.
 */
void setTxtPosPCD8544(uint8_t, uint8_t);
/*
 *@brief Setea la posición de un pixel.
 */
void setPxlPosPCD8544(uint8_t, uint8_t);

/*
 * @brief Activa un pixel en una posicion (x,y)
 */
void drawPxlPCD8544(uint8_t, uint8_t);

/*
 *@brief Actualiza la pantalla con los datos presentes en la memoria cache
 */
void updateScrnPCD8544(void);

/*
 *@brief Escribe un caracter en pantalla
 */
uint8_t wrtCharPCD8544(char);

/*
 *@brief Escribe un string en pantalla
 */
void wrtStrPCD8544(char *);

/*
 *@brief Invierte los colores de la pantalla
 */
void invClrPCD8544(bool_t);

/*
 *@brief Enciende todos los pixels
 */
void setAllPxlPCD8544(bool_t);

/*
 *@brief Dibuja una imagen en pantalla
 */
void drawImgPCD8544(uint8_t*);


//clearPxlPCD8544(x1,y1,); Borra un pixel
//clearBlockPCD8544(x,y); Borra un bloque

//drawLinePCD8544();
//drawCirclePCD8544();
//drawSqaurePCD8544();



#endif /* PRE_INGRESO_PROYPCOMM_INC_PCD8544_H_ */
