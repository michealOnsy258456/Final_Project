/*
 * E2PROM.h
 *
 *  Created on: Jan 20, 2020
 *      Author: micheal_onsy
 */

#ifndef E2PROM_H_
#define E2PROM_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

void E2PROM_VidInit();
void E2PROM_VidWrite(uint16 a_u16Address,uint8 a_u8Data);
void E2PROM_VidRead(uint16 a_u16Address,uint8 * a_u8Data);


#endif /* E2PROM_H_ */
