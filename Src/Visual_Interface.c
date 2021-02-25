#include "Visual_Interface.h"
#include "SSD1306.h"
#include "MPU6050.h"
#include "UPCbitmap.h"



void GyroScreen(void){
	
	char buff[20] = {0}; // Buffer donde se guarda pitch
	char buff2[20] = {0}; // Buffer donde se guarda yaw
	char temp_buff[20] = {0}; // Buffer donde se guarda la temperatura
	
	int temp; // Variable de temperatura
	temp = MPU6050_Read_Temp(); //Recibir la temperatura del sensor
	
	
	//En las siguientes lineas se dibuja el nombre de la pantalla y la temperatura en 
	//los extremos
	SSD1306_GotoXY (1,1); 
	SSD1306_Puts ("GY", &Font_7x10, 1);
	SSD1306_GotoXY (113,1); 
	sprintf(temp_buff,"%d",temp);
	SSD1306_Puts (temp_buff, &Font_7x10, 1);
	
	
	int theta[2]; //Vector donde se guarda la lectura del sensor
	theta[0] = MPU6050_Orientation(MPU6050_Read_Accel())[0];
	theta[1] = MPU6050_Orientation(MPU6050_Read_Accel())[1];
	
	
	int x1,y1,x2,y2,tx1,tx3,ty1,ty3,t1x1,t1x3,t1y1,t1y3; //Variables geometricas de la pantalla
	//char sx[4];
	//char sy[4];
	
	SSD1306_DrawCircle(c1x0,c1y0,c1r,1); // Circulo de Pitch
	SSD1306_DrawCircle(c2x0,c2y0,c2r,1); // Circulo de Yaw
	SSD1306_DrawLine(0,downline,SSD1306_WIDTH,downline,1); //Horizontal downline
	SSD1306_DrawLine(SSD1306_WIDTH/2,0,SSD1306_WIDTH/2,SSD1306_HEIGHT,1); // Vertical downline
	
	float alpha1; //Variable donde se guarda lectura de angulo
	float alpha; // Variable donde se guarda lectura de angulo
	
	alpha = theta[0];
	alpha1 = theta[1];
	
	//Impresión de pantalla del valor de pitch
	SSD1306_GotoXY (5,SSD1306_HEIGHT-12);
	SSD1306_Puts ("        ", &Font_7x10, 1); //Espacio en blanco para borrar la lectura anterior
	SSD1306_GotoXY (5,SSD1306_HEIGHT-12); 
	sprintf(buff,"[P]: %0.0f",-alpha); // Conversión a tipo caracter
	SSD1306_Puts (buff, &Font_7x10, 1); // Escribir en las cordenadas el valor de angulo correspontiente

	// Idem al grupo anterior en diferentes coordenadas para Yaw
	SSD1306_GotoXY (SSD1306_WIDTH/2+5,SSD1306_HEIGHT-12);
	SSD1306_Puts ("              ", &Font_7x10, 1);
	SSD1306_GotoXY (SSD1306_WIDTH/2+5,SSD1306_HEIGHT-12); 
	sprintf(buff2,"[Y]: %0.0f",-alpha1);
	SSD1306_Puts (buff2, &Font_7x10, 1); 
	
	
	//Puntos geometricos variables de los triangulos centrales
	tx1 = tlen*c1r*cos(alpha*1/57.29);
	ty1 = tlen*c1r*sin(alpha*1/57.29);
	tx3 = tlen*c1r*cos(alpha*1/57.29+3.1415/2);
	ty3 = tlen*c1r*sin(alpha*1/57.29+3.1415/2);
	
	
	t1x1 = tlen*c1r*cos(alpha1*1/57.29);
	t1y1 = tlen*c1r*sin(alpha1*1/57.29);
	t1x3 = tlen*c1r*cos(alpha1*1/57.29+3.1415/2);
	t1y3 = tlen*c1r*sin(alpha1*1/57.29+3.1415/2);
	
	//Puntos geometricos variables de las lineas que representan los angulos
	x1 = c1r*cos(alpha*1/57.29);
	y1 = c1r*sin(alpha*1/57.29);
	x2 = c2r*cos(alpha1*1/57.29);
	y2 = c2r*sin(alpha1*1/57.29);
	
	//Dibujar las lineas correspondientes a los angulos
	SSD1306_DrawLine(-x1+c1x0,-y1+c1y0,x1+c1x0,y1+c1y0,1);
	SSD1306_DrawLine(-x2+c2x0,-y2+c2y0,x2+c2x0,y2+c2y0,1);
	
	//Dibujar triangulos centrales
	SSD1306_DrawTriangle(-tx1+c1x0,-ty1+c1y0,tx1+c1x0,ty1+c1y0,tx3+c1x0,ty3+c1y0,1);
	SSD1306_DrawTriangle(-t1x1+c2x0,-t1y1+c2y0,t1x1+c2x0,t1y1+c2y0,t1x3+c2x0,t1y3+c2y0,1);

	//Actualizar pantalla
	SSD1306_UpdateScreen();
	
	//Las siguientes lineas corresponden a borrar los pixeles variables para el siguiente frame
	SSD1306_DrawLine(-x1+c1x0,-y1+c1y0,x1+c1x0,y1+c1y0,0);
	SSD1306_DrawTriangle(tx1+c1x0,ty1+c1y0,-tx1+c1x0,-ty1+c1y0,tx3+c1x0,ty3+c1y0,0);
	SSD1306_DrawTriangle(-t1x1+c2x0,-t1y1+c2y0,t1x1+c2x0,ty1+c2y0,t1x3+c2x0,t1y3+c2y0,0);
	SSD1306_DrawCircle(c1x0,c1y0,c1r,1);
	SSD1306_DrawFilledCircle(c1x0,c1y0,c1r,0);
	SSD1306_DrawLine(-x2+c2x0,-y2+c2y0,x2+c2x0,y2+c2y0,0);
	SSD1306_DrawCircle(c2x0,c2y0,c2r,1);
	SSD1306_DrawFilledCircle(c2x0,c2y0,c2r,0);
	
	// Redibujar la linea vertical, se borran algunos pixeles por el buffer de Pitch
	SSD1306_DrawLine(SSD1306_WIDTH/2,0,SSD1306_WIDTH/2,SSD1306_HEIGHT,1); // Vertical downline
	
		
		//Se transmiten los datos por bluetooth
		BT_Transmit(alpha,alpha1,temp);
		
}



void DataScreen(){ //Pantalla correspondiende a los datos del bluetooth
	
	
	char* txt[3] = {"BT Name: BTHECTOR","BT Key: 1234","BaudRate: 9600 "}; //Datos del bluetooth
	
	// Imprimir los datos del bluetooth
	SSD1306_GotoXY (5,5); 
	SSD1306_Puts (txt[0], &Font_7x10, 1);
	SSD1306_GotoXY (5,20); 
	SSD1306_Puts (txt[1], &Font_7x10, 1);
	SSD1306_GotoXY (5,35); 
	SSD1306_Puts (txt[2], &Font_7x10, 1);
	SSD1306_UpdateScreen();
	
	
}

void InitScreen(){ //Pantalla de inicio con logo UPC y Bluetooth
	
	int c = 0;
	int cycles = 100*10000;
	
	SSD1306_DrawBitmap(0,0,BMP2,128,64,1);
	SSD1306_UpdateScreen();
	
	while(c<cycles){c++;} //Contador para mantener la pantalla de inicio duante un tiempo.
}

