/*
 * DMA_Connfigure.h
 *
 *  Created on: Jun 6, 2023
 *      Author: nguye
 */

#ifndef DMA1_DMA_CONFIGURE_H_
#define DMA1_DMA_CONFIGURE_H_

#include "stdint.h"

void DMA_ConfigureADC(uint32_t *buffer, uint8_t numberOfChannels);
void DMA_ConfigureUART(void);
void sendUART1DMA(uint8_t *data);

#endif /* DMA1_DMA_CONFIGURE_H_ */
