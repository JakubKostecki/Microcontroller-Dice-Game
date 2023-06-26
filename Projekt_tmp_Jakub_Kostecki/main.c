/*-------------------------------------------------------------------------
					Technika Mikroprocesorowa 2 - Projekt
					Temat pracy - gra w kości
					autor: Jakub Kostecki
					data: 22.01.2023r.
----------------------------------------------------------------------------*/
	
#include "MKL05Z4.h"
#include "frdm_bsp.h"
#include "lcd1602.h"
#include "klaw.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DISPLAY_LIMIT	10	// Stała, która umożliwia przejście kursora w stan początkowy(naliczanie mod 10) 
#define Start_limit 2

volatile uint8_t S1_press=0;
volatile uint8_t S2_press=0;
volatile uint8_t S3_press=0;
volatile uint8_t S4_press=0;
uint8_t kostka_1=0;						///////////////////////////////////
uint8_t kostka_2=0;						// Zmienne do trzymania wartości //
uint8_t kostka_3=0;						// na wszystkich 6 Kościach do	 //
uint8_t kostka_4=0;						// gry													 //
uint8_t kostka_5=0;						//															 //
uint8_t kostka_6=0;						///////////////////////////////////
uint8_t pozycja = 0;					// Pozycja kursora
uint8_t pozycja_1 = 20;				///////////////////////////////////
uint8_t pozycja_2 = 20;				// Zmienne pozycja_x są					 //
uint8_t pozycja_3 = 20;				// potrzebne aby móc zapisać		 //
uint8_t pozycja_4 = 20;				// zatwierdzoną pozycję kursora	 //
uint8_t pozycja_5 = 20;				// aby odrzucic do 6 kości			 //
uint8_t pozycja_6 = 20;				///////////////////////////////////
uint8_t start = 0;						// Zmienna, która umożliwia wykorzystanie przerwania przyciskiem s3 do rozpoczęcia gry oraz do zatwierdzania odrzuconych kosci

void PORTA_IRQHandler(void)	// Podprogram obslugi przerwania od klawiszy S2, S3 i S4
{
	uint32_t buf;
	buf=PORTA->ISFR & (S2_MASK | S3_MASK | S4_MASK);

	switch(buf)
	{
		//////////////////////////////////////////////////////
		//Przerwanie odpowiedzialne za przypisanie wartości	//
		//pozzycja do pierwszej wolnej zmiennej pozycjax		//
		//////////////////////////////////////////////////////
		case S2_MASK:	DELAY(10)
									if(!(PTA->PDIR&S2_MASK))		// Minimalizacja drgan zestykow
									{
										if(!(PTA->PDIR&S2_MASK))	
										{
											if(!S2_press)
											{
												if(pozycja_1 == 20){
												pozycja_1 = pozycja;
												}else if(pozycja_2 == 20){
												pozycja_2 = pozycja;
												}else if(pozycja_3 == 20){
												pozycja_3 = pozycja;
												}else if(pozycja_4 == 20){
												pozycja_4 = pozycja;
												}else if(pozycja_5 == 20){
												pozycja_5 = pozycja;
												}else if(pozycja_6 == 20){
													pozycja_6 = pozycja;
											}
										}
									}
								}
									break;
								
			////////////////////////////////////////////////////////////
			//Przerwanie, ktore w zaleznosci od wartosci start, albo	//
			//losuje 6 kosci dla gracza albo losuje nowe wartosci dla	// 
			//wybranych przez gracza kosci														//
			////////////////////////////////////////////////////////////
		case S3_MASK:	DELAY(10)
									if(!(PTA->PDIR&S3_MASK))		// Minimalizacja drgan zestykow
									{
										if(!(PTA->PDIR&S3_MASK))	// Minimalizacja drgan zestykow (c.d.)
										{
											if(!S3_press)
											{
												if(start == 0){
												kostka_1 = rand() % 6;
												kostka_1 = kostka_1 + 1;
												
												kostka_2 = rand() % 6;
												kostka_2 = kostka_2 + 1;
												
												kostka_3 = rand() % 6;
												kostka_3 = kostka_3 + 1;
												
												kostka_4 = rand() % 6;
												kostka_4 = kostka_4 + 1;
												
												kostka_5 = rand() % 6;
												kostka_5 = kostka_5 + 1;
												
												kostka_6 = rand() % 6;
												kostka_6 = kostka_6 + 1;
													
												start += 1;
												pozycja_1 = 20;
												pozycja_2 = 20;
												pozycja_3 = 20;
												pozycja_4 = 20;
												pozycja_5 = 20;
												pozycja_6 = 20;
												
												}else{
												start += 1;
												
												if(pozycja_1 == 0 || pozycja_2 == 0 || pozycja_3 == 0 || pozycja_4 == 0 || pozycja_5 == 0 || pozycja_6 == 0){
												kostka_1 = rand() % 6;
												kostka_1 = kostka_1 + 1;
												}
												if(pozycja_1 == 2 || pozycja_2 == 2 || pozycja_3 == 2 || pozycja_4 == 2 || pozycja_5 == 2 || pozycja_6 == 2){
												kostka_2 = rand() % 6;
												kostka_2 = kostka_2 + 1;												
												}
												if(pozycja_1 == 4 || pozycja_2 == 4 || pozycja_3 == 4 || pozycja_4 == 4 || pozycja_5 == 4 || pozycja_6 == 4){
												kostka_3 = rand() % 6;
												kostka_3 = kostka_3 + 1;												
												}
												if(pozycja_1 == 6 || pozycja_2 == 6 || pozycja_3 == 6 || pozycja_4 == 6 || pozycja_5 == 6 || pozycja_6 == 6){
												kostka_4 = rand() % 6;
												kostka_4 = kostka_4 + 1;												
												}
												if(pozycja_1 == 8 || pozycja_2 == 8 || pozycja_3 == 8 || pozycja_4 == 8 || pozycja_5 == 8 || pozycja_6 == 8){
												kostka_5 = rand() % 6;
												kostka_5 = kostka_5 + 1;												
												}
												if(pozycja_1 == 10 || pozycja_2 == 10 || pozycja_3 == 10 || pozycja_4 == 10 || pozycja_5 == 10 || pozycja_6 == 10){
												kostka_6 = rand() % 6;
												kostka_6 = kostka_6 + 1;	
												
												}
												if(start>Start_limit)
												start=0;
												
												pozycja_1 = 20;
												pozycja_2 = 20;
												pozycja_3 = 20;
												pozycja_4 = 20;
												pozycja_5 = 20;
												pozycja_6 = 20;
											}
												
												S3_press=1;
											}
										}
									}
									break;
									
			////////////////////////////////////////////////////////////
			//Przerwanie przyciskiem s4 odpowiada za przesuwanie 			//
			//kursora, czyli w zasadzie za inkrementowanie wartosci		//
			//pozycja																									//
			////////////////////////////////////////////////////////////
			
		case S4_MASK: DELAY(10);
			
			if(!S4_press)
									{
										if(!(PTA->PDIR&S4_MASK))
										{
											if(!(PTA->PDIR&S4_MASK))
											{
										pozycja+=1;
										if(pozycja>DISPLAY_LIMIT)
											pozycja=0;
										S4_press=1;
									}
								}
							}
									break;
		default:			break;
	}	
	PORTA->ISFR |=  S2_MASK | S3_MASK | S4_MASK;	// Kasowanie wszystkich bitow ISF
	NVIC_ClearPendingIRQ(PORTA_IRQn);
}

int main (void) 
{
	char display[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
	
	Klaw_Init();								// Inicjalizacja klawiatury
	Klaw_S2_4_Int();						// Klawisze S2, S3 i S4 zglaszaja przerwanie
	LCD1602_Init();		 					// Inicjalizacja LCD
	LCD1602_Backlight(TRUE);  	// Wlaczenie podswietlenia
	
	LCD1602_ClearAll();								// Wyczysc ekran
	LCD1602_Print("Wcisnij s1");			//Linie wyswietlajace sekwencje powitalna
	LCD1602_SetCursor(0,1);						//z instrukcjami dla uzytkownika
	LCD1602_Print("aby kontynuowac");		
	
	while(PTA->PDIR&S1_MASK);  	// oczekiwanie na wcisniecie klawisza S1
	
	LCD1602_ClearAll();					
	LCD1602_Print("Wcisnij s3");		
	LCD1602_SetCursor(0,1);			
	LCD1602_Print("aby wylosowac");		
	
	while(PTA->PDIR&S1_MASK);  	
	
	LCD1602_ClearAll();					
	LCD1602_Print("Wcisnij s4");		
	LCD1602_SetCursor(0,1);			
	LCD1602_Print("aby wybierac...");		
	
	while(PTA->PDIR&S1_MASK);  	
	
	LCD1602_ClearAll();					
	LCD1602_Print("liczby do");		
	LCD1602_SetCursor(0,1);			
	LCD1602_Print("odrzucenia");		
	
	while(PTA->PDIR&S1_MASK);  	
	
	LCD1602_ClearAll();					
	LCD1602_Print("Wcisnij S2 aby");		
	LCD1602_SetCursor(0,1);			
	LCD1602_Print("zatwierdzic wybor");		
	
	while(PTA->PDIR&S1_MASK);  	
	
	LCD1602_ClearAll();					
	LCD1602_Print("Wcisnij s3 aby");		
	LCD1602_SetCursor(0,1);			
	LCD1602_Print("wymienic wybrane");	
	
	while(PTA->PDIR&S1_MASK);  
	
	LCD1602_ClearAll();				
	LCD1602_Print("Liczby");	
	LCD1602_SetCursor(0,1);			
	LCD1602_Print("Milej Zabawy");		
	
	while(PTA->PDIR&S1_MASK);  	
	
	LCD1602_ClearAll();									
	LCD1602_SetCursor(0,0);							//Wyswietlanie zer w odpowienich miejscach
	sprintf(display,"%01d",kostka_1);		//stan poczatkowy, przed rozpoczeciem losowania
	LCD1602_Print(display);
	LCD1602_SetCursor(2,0);
	sprintf(display,"%01d",kostka_2);	
	LCD1602_Print(display);
	LCD1602_SetCursor(4,0);
	sprintf(display,"%01d",kostka_3);	
	LCD1602_Print(display);
	LCD1602_SetCursor(6,0);
	sprintf(display,"%01d",kostka_4);	
	LCD1602_Print(display);
	LCD1602_SetCursor(8,0);
	sprintf(display,"%01d",kostka_5);	
	LCD1602_Print(display);
	LCD1602_SetCursor(10,0);
	sprintf(display,"%01d",kostka_6);	
	LCD1602_Print(display);
	
	
  while(1)		// Poczatek petli glownej
	{
		
		if(S2_press)
		{
			S2_press=0;
		}
		if(S3_press)							// zmien wskazanie wyswietlacza po wykonaniu akcji
		{
			LCD1602_ClearAll();
			
			LCD1602_SetCursor(0,0);
			sprintf(display,"%01d",kostka_1);
			LCD1602_Print(display);
			
			LCD1602_SetCursor(2,0);
			sprintf(display,"%01d",kostka_2);
			LCD1602_Print(display);
			
			LCD1602_SetCursor(4,0);
			sprintf(display,"%01d",kostka_3);
			LCD1602_Print(display);
			
			LCD1602_SetCursor(6,0);
			sprintf(display,"%01d",kostka_4);
			LCD1602_Print(display);
			
			LCD1602_SetCursor(8,0);
			sprintf(display,"%01d",kostka_5);
			LCD1602_Print(display);
			
			LCD1602_SetCursor(10,0);
			sprintf(display,"%01d",kostka_6);
			LCD1602_Print(display);
			
			S3_press=0;
		}
		if(S4_press)							// zmien wskazanie wyswietlacza po wykonaniu akcji
		{
						LCD1602_ClearAll();
			
			LCD1602_SetCursor(0,0);						///////////////////////////
			sprintf(display,"%01d",kostka_1);	//
			LCD1602_Print(display);						//
																				//
			LCD1602_SetCursor(2,0);						//
			sprintf(display,"%01d",kostka_2); //
			LCD1602_Print(display);						//
																				//
			LCD1602_SetCursor(4,0);						//			wyswietlanie 
			sprintf(display,"%01d",kostka_3);	//				  kosci
			LCD1602_Print(display);						//
																				//			
			LCD1602_SetCursor(6,0);						//
			sprintf(display,"%01d",kostka_4);	//
			LCD1602_Print(display);						//
																				//
			LCD1602_SetCursor(8,0);						//
			sprintf(display,"%01d",kostka_5);	//
			LCD1602_Print(display);						//
																				//
			LCD1602_SetCursor(10,0);					//
			sprintf(display,"%01d",kostka_6);	//
			LCD1602_Print(display);						/////////////////////////////
			
			LCD1602_SetCursor(pozycja,1);
			sprintf(display,"%c",'^');				// Wyswietlanie kursora
			LCD1602_Print(display);
			
			LCD1602_SetCursor(pozycja_1,1);		/////////////////////////////
			sprintf(display,"%c",'^');				//
			LCD1602_Print(display);						//
																				//
			LCD1602_SetCursor(pozycja_2,1);		//
			sprintf(display,"%c",'^');				//
			LCD1602_Print(display);						//
																				//
			LCD1602_SetCursor(pozycja_3,1);		//		wyswietlanie kursorow
			sprintf(display,"%c",'^');				//		pod wybranymi przez
			LCD1602_Print(display);						//		gracza koscmi
																				//
			LCD1602_SetCursor(pozycja_4,1);		//
			sprintf(display,"%c",'^');				//
			LCD1602_Print(display);						//
																				//
			LCD1602_SetCursor(pozycja_5,1);		//
			sprintf(display,"%c",'^');				//
			LCD1602_Print(display);						//
																				//
			LCD1602_SetCursor(pozycja_6,1);		//
			sprintf(display,"%c",'^');				//
			LCD1602_Print(display);						/////////////////////////////
			S4_press=0;												
		}
		
	}
}
