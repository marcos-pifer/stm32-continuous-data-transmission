#include "main.h"
#include "SSD1306.h"
#include "MPU6050.h"

/** 
 * @brief  Esta función gestiona el cambio de pantallas segun el valor de la variable de entrada
 * @note   None
 * @param  SCREEN: Esta variable cambia de estado al pulsar el boton (dentro de la interrupción)
 * @retval None
 */

void ScreenHandler(bool screen);