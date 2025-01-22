/*
 * LCD.c
 *
 *  Created on: Sep 4, 2024
 *      Author: Younis
 */

#include "LCD.h"

GPIO_Pin_Config_t PinCnfg;


uint16_t GPIO_Pins_Array[] = {GPIO_Pin_0 , GPIO_Pin_1 , GPIO_Pin_2 , GPIO_Pin_3 , GPIO_Pin_4 , GPIO_Pin_5 , GPIO_Pin_6 , GPIO_Pin_7 };


//void my_wait(int x)
//{
//	unsigned int i,j;
//	for(i=0; i<x ; i++)
//	{
//		for(j=0; j<255 ; j++)
//		{
//
//		}
//	}
//}

void LCD_En_Kick()
{
	//	LCD_Ctrl &= ~(1<<EN_Switch);
	MCAL_GPIO_WritePin(LCD_Ctrl, EN_Switch, GPIO_Pin_Set);

	my_wait(50);// using Enable Cycle time in Bus timing characteristics in data sheet
	//	LCD_Ctrl |= (1<<EN_Switch);
	MCAL_GPIO_WritePin(LCD_Ctrl, EN_Switch, GPIO_Pin_Reset);
}

void LCD_GOTO_XY(int line , int position)
{
	if(line == 1)
	{
		if(position < 16 && position >= 0)
		{
			LCD_Write_Command(LCD_BEGIN_AT_FIRST_ROW + position);//Ely howa ht7rko be character 0x80+
		}
	}
	else if(line == 2)
	{
		if(position < 32 && position >= 0)
		{
			LCD_Write_Command(LCD_BEGIN_AT_SECOND_ROW + position);//Ely howa ht7rko be character 0xC0+
		}
	}
}

void LCD_Clear_Screen()
{
	LCD_Write_Command(LCD_CLEAR_SCREEN);
}

void LCD_Is_Busy(void)
{
	//	DataDirection_LCD_PORT &= ~(0xFF<<DATA_Shift);//To make it input
	for(int i = GPIO_Pin_0; i<GPIO_Pin_7 ; i++)
	{
		PinCnfg.GPIO_Pin_Num = GPIO_Pins_Array[i];
		PinCnfg.GPIO_Mode = GPIO_Mode_Input_Flo;
		MCAL_GPIO_Init(LCD_PORT, &PinCnfg);
	}


	//	LCD_Ctrl |= (1<<RW_Switch); //Read mode
	MCAL_GPIO_WritePin(LCD_Ctrl, RW_Switch, GPIO_Pin_Set);

	//	LCD_Ctrl &= ~(1<<RS_Switch); //RS off
	MCAL_GPIO_WritePin(LCD_Ctrl, RS_Switch, GPIO_Pin_Reset);

	LCD_En_Kick();
	//	DataDirection_LCD_PORT |= (0xFF<<DATA_Shift);



	//	LCD_Ctrl &= ~(1<<RW_Switch);
	MCAL_GPIO_WritePin(LCD_Ctrl, RW_Switch, GPIO_Pin_Reset);

	//Kan mbwzlli el denyaaa
	//	LCD_Clear_Screen();
}


void LCD_Init(void)
{
	my_wait(20);

	//	LCD_Ctrl &= ~((1<<EN_Switch) | (1<<RW_Switch) | (1<<RS_Switch));
	//RS switch
	PinCnfg.GPIO_Pin_Num = RS_Switch;
	PinCnfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCnfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
	MCAL_GPIO_Init(LCD_Ctrl, &PinCnfg);

	//RW switch
	PinCnfg.GPIO_Pin_Num = RW_Switch;
	PinCnfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCnfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
	MCAL_GPIO_Init(LCD_Ctrl, &PinCnfg);

	//EN switch
	PinCnfg.GPIO_Pin_Num = EN_Switch;
	PinCnfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCnfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
	MCAL_GPIO_Init(LCD_Ctrl, &PinCnfg);

	//	To make pins output with speed 10 MHz
	for(int i = GPIO_Pin_0; i<GPIO_Pin_7 ; i++)
	{
		PinCnfg.GPIO_Pin_Num = GPIO_Pins_Array[i];
		PinCnfg.GPIO_Mode = GPIO_Mode_Output_PP;
		PinCnfg.GPIO_Output_Speed = GPIO_Speed_10MHz;
		MCAL_GPIO_Init(LCD_PORT, &PinCnfg);
	}


	MCAL_GPIO_WritePin(LCD_Ctrl, EN_Switch, GPIO_Pin_Reset);
	MCAL_GPIO_WritePin(LCD_Ctrl, RS_Switch, GPIO_Pin_Reset);
	MCAL_GPIO_WritePin(LCD_Ctrl, RW_Switch, GPIO_Pin_Reset);


	my_wait(1);
	//	LCD_Is_Busy();
	LCD_Clear_Screen();

	//#ifdef EIGHT_BIT_MODE
	LCD_Write_Command(LCD_FUNCTION_8BIT_2LINES);
	//#endif

	//#ifdef FOUR_BIT_MODE
	//	//A command needed for using 4 bit mode
	//	LCD_Write_Command(0x02);
	//	LCD_Write_Command(LCD_FUNCTION_4BIT_2LINES);
	//#endif

	LCD_Write_Command(LCD_ENTRY_MODE);
	LCD_Write_Command(LCD_BEGIN_AT_FIRST_ROW);
	LCD_Write_Command(LCD_DISP_ON_CURSOR_BLINK);
}


void LCD_Write_Command(unsigned char command)
{
	//	LCD_Is_Busy();

	//#ifdef EIGHT_BIT_MODE
	//	LCD_PORT = command;
	MCAL_GPIO_WritePort(LCD_PORT, command);

	//	LCD_Ctrl &= ~((1<<RW_Switch) | (1<<RS_Switch));
	MCAL_GPIO_WritePin(LCD_Ctrl, RW_Switch, GPIO_Pin_Reset);
	MCAL_GPIO_WritePin(LCD_Ctrl, RS_Switch, GPIO_Pin_Reset);

	my_wait(1);
	LCD_En_Kick();
	//#endif

	//#ifdef FOUR_BIT_MODE
	//	//First part of command
	//	LCD_PORT = ((LCD_PORT & 0x0F) | (command & 0xF0));
	//	LCD_Ctrl &= ~((1<<RW_Switch) | (1<<RS_Switch));
	//	my_wait(1);
	//	LCD_En_Kick();
	//
	//	//Second 4 bits
	//	LCD_PORT = ((LCD_PORT & 0x0F) | (command << 4));
	//	LCD_Ctrl &= ~((1<<RW_Switch) | (1<<RS_Switch));
	//	my_wait(1);
	//	LCD_En_Kick();
	//#endif
}

void LCD_Write_Char(unsigned char data)
{
	//LCD_Is_Busy();

	//#ifdef EIGHT_BIT_MODE
	//	LCD_PORT = data;
	MCAL_GPIO_WritePort(LCD_PORT, data);

	//	LCD_Ctrl &= ~(1<<RW_Switch);
	//	LCD_Ctrl |= (1<<RS_Switch);
	MCAL_GPIO_WritePin(LCD_Ctrl, RW_Switch, GPIO_Pin_Reset);
	MCAL_GPIO_WritePin(LCD_Ctrl, RS_Switch, GPIO_Pin_Set);

	my_wait(1);
	LCD_En_Kick();
	//#endif

	//#ifdef FOUR_BIT_MODE
	//	//First part of command
	//	LCD_PORT = ((LCD_PORT & 0x0F) | (data & 0xF0));
	//	LCD_Ctrl |= (1<<RS_Switch);
	//	LCD_Ctrl &= ~(1<<RW_Switch);
	//	my_wait(1);
	//	LCD_En_Kick();
	//
	//	//Second 4 bits
	//	LCD_PORT = ((LCD_PORT & 0x0F) | (data << 4));
	//	LCD_Ctrl |= (1<<RS_Switch);
	//	LCD_Ctrl &= ~(1<<RW_Switch);
	//	my_wait(1);
	//	LCD_En_Kick();
	//#endif
}


void LCD_Write_String(char* data)
{
	int count = 0;
	while(*data > 0)
	{
		count++;
		LCD_Write_Char(*data++);
		if(count == 16)
		{
			LCD_GOTO_XY(2 , 0);
		}
		else if(count == 32)
		{
			LCD_Clear_Screen();
			LCD_GOTO_XY(1,0);
			count = 0;
		}
	}
}


void LCD_Custom_Character()
{
	LCD_Write_Command(64);
	LCD_Write_Char(0);
	LCD_Write_Char(14);
	LCD_Write_Char(17);
	LCD_Write_Char(2);
	LCD_Write_Char(4);
	LCD_Write_Char(4);
	LCD_Write_Char(0);
	LCD_Write_Char(4);
	LCD_Write_Command(LCD_BEGIN_AT_FIRST_ROW);
	LCD_Write_Char(0);
	my_wait(10);
}
