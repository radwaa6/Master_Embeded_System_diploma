/*
 * Utils.h
 *
 *  Created on: Sep 4, 2024
 *      Author: Younis
 */

#ifndef UTILS_H_
#define UTILS_H_

#define Set_bit(register,bit)		register|=(1<<bit)
#define Toggle_bit(register,bit)	register^=(1<<bit)
#define Clear_bit(register,bit)		register&=~(1<<bit)
#define Read_bit(register,bit)		((register>>bit)&1)//To read bit you should read it from register PIN

#endif /* UTILS_H_ */
