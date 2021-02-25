#include "main.h"

#define BTDataLen 38


extern UART_HandleTypeDef huart2;

/** 
 * @brief  Esta funci�n es la encargada de la gesti�n de transmisi�n discontinua
 * @note   None
 * @param  None
 * @retval None
 */
void BT_DTX(void);

/** 
 * @brief  Esta funci�n es la encargada de la transmisi�n de los datos
 * @note   None
 * @param  ALPHA: Angulo 1 de salida del giroscopio
 * @param  ALPHA: Angulo 2 de salida del giroscopio
 * @param  TEMP:  Temperatura de salida del giroscopio
 * @retval None
 */
void BT_Transmit(int alpha,int alpha1, int temp);
