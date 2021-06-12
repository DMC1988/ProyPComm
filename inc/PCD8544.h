/*
 * PCD8544.h
 *
 *  Created on: 19 may. 2021
 *      Author: damian
 */
#include <sapi.h>
#include <font.h>

#ifndef PRE_INGRESO_PROYPCOMM_INC_PCD8544_H_
#define PRE_INGRESO_PROYPCOMM_INC_PCD8544_H_

//Pines
#define RST_PCD8544 GPIO0
#define	CE_PCD8544 GPIO1
#define	DC_PCD8544 GPIO2
/*El resto de los pines son los del SPI*/

//Definiciones para el uso de funciones.
#define SUCCESS   0
#define ERROR     1
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
 *@brief Inicializa el display.
 */
void initPCD8544(void);

/*
 *@brief Resetea el display.
 */
void resetPCD8544(void);

/*
 * @brief Enviar datos/comandos.
 * @param uint8_t
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
 *@param uint8_t
 *@param uint8_t
 */
uint8_t setTxtPosPCD8544(uint8_t, uint8_t);

/*
 *@brief Setea la posición de un pixel.
 *@param uint8_t
 *@param uint8_t
 */
uint8_t setPxlPosPCD8544(uint8_t, uint8_t);

/*
 * @brief Activa un pixel en una posicion (x,y)
 * @param uint8_t
 * @param uint8_t
 */
void drawPxlPCD8544(uint8_t, uint8_t);

/*
 *@brief Actualiza la pantalla con los datos presentes en la memoria cache
 */
void updateScrnPCD8544(void);

/*
 *@brief Escribe un caracter en pantalla
 *@param char
 *@param uint8_t
 */
uint8_t wrtCharPCD8544(char);

/*
 *@brief Escribe un string en pantalla
 *@param char*
 */
void wrtStrPCD8544(char *);

/*
 *@brief Invierte los colores de la pantalla
 *@param bool_t
 */
void invClrPCD8544(bool_t);

/*
 *@brief Enciende todos los pixels
 *@param bool_t
 */
void setAllPxlPCD8544(bool_t);

/*
 *@brief Dibuja una imagen en pantalla
 *@param uint8_t*
 */
void drawImgPCD8544(uint8_t*);

/*
 *@brief Borra un bloque de la pantalla
 *@param uint8_t
 *@param uint8_t
 *@param uint8_t
 */
void clrTxtPosPCD8544(uint8_t, uint8_t, uint8_t);


#endif /* PRE_INGRESO_PROYPCOMM_INC_PCD8544_H_ */
