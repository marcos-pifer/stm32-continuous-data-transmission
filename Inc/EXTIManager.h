#include "main.h"
#include "SSD1306.h"
#include "MPU6050.h"

/** 
 * @brief  Esta funci�n gestiona el cambio de pantallas segun el valor de la variable de entrada
 * @note   None
 * @param  SCREEN: Esta variable cambia de estado al pulsar el boton (dentro de la interrupci�n)
 * @retval None
 */

void ScreenHandler(bool screen);