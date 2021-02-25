#include "main.h"

#define BTDataLen 38


extern UART_HandleTypeDef huart2;

/** 
 * @brief  Esta función es la encargada de la gestión de transmisión discontinua
 * @note   None
 * @param  None
 * @retval None
 */
void BT_DTX(void);

/** 
 * @brief  Esta función es la encargada de la transmisión de los datos
 * @note   None
 * @param  ALPHA: Angulo 1 de salida del giroscopio
 * @param  ALPHA: Angulo 2 de salida del giroscopio
 * @param  TEMP:  Temperatura de salida del giroscopio
 * @retval None
 */
void BT_Transmit(int alpha,int alpha1, int temp);
