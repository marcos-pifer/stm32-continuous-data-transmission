

// caracteristicas geom�tricas de GyroScreen 

#define c1r 21 // Radio circulo 1
#define c1x0 32 // Posicion xo del circulo 1
#define c1y0 24 // Posicion yo del circulo 1

#define c2r 21 // Idem a las 3 constantes anteriores.
#define c2x0 96
#define c2y0 24


#define downline (64-15) // Linea horizontal inferior
#define dtxt1 (64-2) // Posicion x de texto [P]
#define txtpx2 (84+txtpy) // Posici�n x de texto [Y]
#define txtpy 2 // Posici�n y de los textos [P] e [Y]

#define tlen 0.4 // Tama�o del lado del triangulo central

/** 
 * @brief  Esta funci�n muestra la pantalla correspondiente a la interfaz gr�fica del giroscopio
 * @note   None
 * @param  None
 * @retval None
 */
 
void GyroScreen(void);

/** 
 * @brief  Esta funci�n muestra la pantalla correspondiente a la interfaz gr�fica de los datos del bluetooth
 * @note   None
 * @param  None
 * @retval None
 */
 
void DataScreen(void);

/** 
 * @brief  Esta funci�n muestra la pantalla correspondiente a la interfaz gr�fica de inicializaci�n.
 * @note   None
 * @param  None
 * @retval None
 */
void InitScreen(void);


