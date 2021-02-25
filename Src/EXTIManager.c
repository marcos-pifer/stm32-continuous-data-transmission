
/**
 * original author:  Joao Marcos Pifer da Silva
 * 16.01.2020 IIEIA UPC 

   ----------------------------------------------------------------------
   	
	
  

    
   ----------------------------------------------------------------------
 */

#include "EXTIManager.h"


#define SLEEPMODETIME 300
#define HLDBTONTIME 5

//---- Variables
bool SCREEN = true; // Variable que gestiona el cambio de pantalla.
int COFF = 0; // Contador que gestiona el tiempo de apagado por inactividad

//---- Variables



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) { // Función redirigida al pulsar el boton de control
		
	
	
	if(GPIO_Pin == CNTRLBUTTON_Pin){ // Si corresponde al pin del botón
		
		HAL_GPIO_WritePin(GPIOB,SENSVCC_Pin,1); //Enciende MPU6050 y SSD1306
		
		MPU6050_Init(); //Inicialización de componentes
		SSD1306_Init();
		
		HAL_GPIO_TogglePin(GPIOB, EXTILED_Pin); //Cambia de estado el ledo de control
		SSD1306_Clear(); //Borra el frame anterior
		COFF=0; // Contador de apagado en 0
		
		if (SCREEN == true){ SCREEN = false;} else if (SCREEN == false){ SCREEN = true;} //Función not que alterna la pantalla
		
		ScreenHandler(SCREEN); //Manejo de la pantalla seleccionada
		SSD1306_Clear(); // Borra el frame mostrado
		HAL_GPIO_WritePin(GPIOB,SENSVCC_Pin,0); //Apaga los componentes MPU6050 y SSD1306
		
	}
	
	else{
		
			HAL_GPIO_WritePin(GPIOB,EXTILED_Pin,0); //Apaga led de control
	}
	
}

void ScreenHandler(bool screen){
			
			COFF=0; //Contador de apagado a 0
			
			if (screen == true){ //Pantalla del giroscopio
				while(COFF<SLEEPMODETIME){ //Mientras sea inferior al tiempo de inactividad
					GyroScreen(); // Interfaz grafica de giroscopio
					COFF++; //Aumenta contador de inactividad
					if (HAL_GPIO_ReadPin(GPIOA,CNTRLBUTTON_Pin)==0 && COFF>HLDBTONTIME){
						// Si se pulsa el botón de control y contador de rebote
						HAL_GPIO_TogglePin(GPIOB,EXTILED_Pin ); // Cambio Led de estado.
						break; // Salida del bucle while
					}
				}
			}
			
			else if (screen==false){ //Pantalla de datos bluetooth
			
				while(COFF<SLEEPMODETIME){ //idem pantalla giroscopio
					
					DataScreen();
					COFF++;
					
					if (HAL_GPIO_ReadPin(GPIOA,CNTRLBUTTON_Pin)==0 && COFF>HLDBTONTIME){
						HAL_GPIO_TogglePin(GPIOB, EXTILED_Pin);
						break;
					}
				}
			}
			
			
}



