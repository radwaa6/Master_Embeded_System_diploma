/*
 * Keypad.c
 *
 *  Created on: Sep 10, 2024
 *      Author: Younis
 */

#include "Keypad.h"

int Keypad_Rows 	[]	= {R0 , R1 , R2 , R3};
int Keypad_Columns	[]	= {C0 , C1 , C2 , C3};

void Keypad_Init()
{
	//Setting bits to zeros (Input)
	//	DataDirection_Keypad_Port &= ~((1<<R0) | (1<<R1) | (1<<R2) | (1<<R3));
	//	//Setting buts to ones (Output)
	//	DataDirection_Keypad_Port |= ((1<<C0) | (1<<C1) | (1<<C2) | (1<<C3));
	PinCnfg.GPIO_Pin_Num = R0;
	PinCnfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCnfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
	MCAL_GPIO_Init(Keypad_Port, &PinCnfg);


	PinCnfg.GPIO_Pin_Num = R1;
	PinCnfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCnfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
	MCAL_GPIO_Init(Keypad_Port, &PinCnfg);

	PinCnfg.GPIO_Pin_Num = R2;
	PinCnfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCnfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
	MCAL_GPIO_Init(Keypad_Port, &PinCnfg);

	PinCnfg.GPIO_Pin_Num = R3;
	PinCnfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCnfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
	MCAL_GPIO_Init(Keypad_Port, &PinCnfg);

	PinCnfg.GPIO_Pin_Num = C0;
	PinCnfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCnfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
	MCAL_GPIO_Init(Keypad_Port, &PinCnfg);

	PinCnfg.GPIO_Pin_Num = C1;
	PinCnfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCnfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
	MCAL_GPIO_Init(Keypad_Port, &PinCnfg);

	PinCnfg.GPIO_Pin_Num = C2;
	PinCnfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCnfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
	MCAL_GPIO_Init(Keypad_Port, &PinCnfg);

	PinCnfg.GPIO_Pin_Num = C3;
	PinCnfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCnfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
	MCAL_GPIO_Init(Keypad_Port, &PinCnfg);

	//Settig all port are VCC
	//	Keypad_Port = 0xFF;
	MCAL_GPIO_WritePort(Keypad_Port, 0xFF);
}


//Will loop in columns + rows as to see which button is trigerred
char Keypad_GetChar()
{
	int i,j;

	for(i = 0 ; i < 4 ; i++)
	{
		//Made all Columns are ones-->has volt
		//		Keypad_Port |= ((1<<Keypad_Columns[0]) | (1<<Keypad_Columns[1]) | (1<<Keypad_Columns[2]) | (1<<Keypad_Columns[3]));
		MCAL_GPIO_WritePin(Keypad_Port, Keypad_Columns[0] , GPIO_Pin_Set);
		MCAL_GPIO_WritePin(Keypad_Port, Keypad_Columns[1] , GPIO_Pin_Set);
		MCAL_GPIO_WritePin(Keypad_Port, Keypad_Columns[2] , GPIO_Pin_Set);
		MCAL_GPIO_WritePin(Keypad_Port, Keypad_Columns[3] , GPIO_Pin_Set);

		//		Keypad_Port &= ~(1<<Keypad_Columns[i]);
		MCAL_GPIO_WritePin(Keypad_Port, Keypad_Columns[i] , GPIO_Pin_Reset);


		//Loop in Rows
		for(j = 0 ; j < 4 ; j++)
		{
			if(MCAL_GPIO_ReadPin(Keypad_Port, Keypad_Rows[j]) == 0)
			{
				//It prevents multi-typing
				while(MCAL_GPIO_ReadPin(Keypad_Port, Keypad_Rows[j]) == 0);

				switch(i)
				{
				case(0) :

											if     (j == 0) return '7';
											else if(j == 1) return '4';
											else if(j == 2) return '1';
											else if(j == 3) return '?';//Whatever i want
				break;

				case(1) :

											if     (j == 0) return '8';
											else if(j == 1) return '5';
											else if(j == 2) return '2';
											else if(j == 3) return '0';//Whatever i want
				break;

				case(2) :

											if     (j == 0) return '9';
											else if(j == 1) return '6';
											else if(j == 2) return '3';
											else if(j == 3) return '=';//Whatever i want
				break;

				case(3) :

											if     (j == 0) return '/';
											else if(j == 1) return '*';
											else if(j == 2) return '-';
											else if(j == 3) return '+';//Whatever i want
				break;
				}
			}
		}
	}
	return 'N';
}
