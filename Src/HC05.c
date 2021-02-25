#include "HC05.h"



void BT_Transmit(int alpha,int alpha1, int temp){
	
		uint8_t buffTX[BTDataLen] = "                    ";
		
		char buffTX1[BTDataLen] = "";
		sprintf(buffTX1,"\nPitch: %d Yaw: %d \n Temperature: %d \n",-alpha,-alpha1,temp);

		for(int i=0;i<BTDataLen;i++){
			buffTX[i] = buffTX1[i];
		}
		
		HAL_UART_Transmit(&huart2,buffTX,BTDataLen,100);
		
}

void BT_DTX(){
	
	
	int alpha,alpha1;
	int temp;
	int DTX_time=3*1000000;
	int time=0;
	
	
	HAL_GPIO_WritePin(GPIOB,SENSVCC_Pin,1);
	MPU6050_Init();
	
	int c=0;
	while(c<10){
		
		MPU6050_Init();
		temp = MPU6050_Read_Temp();
		alpha = MPU6050_Orientation(MPU6050_Read_Accel())[0];
		alpha1 = MPU6050_Orientation(MPU6050_Read_Accel())[1];
		BT_Transmit(alpha,alpha1,temp);
		
		c++;
	
	}
	
	HAL_GPIO_WritePin(GPIOB,SENSVCC_Pin,0);

	while (time<DTX_time){ time++;}
}
