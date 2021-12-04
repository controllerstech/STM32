/* Functions called by the TouchGFX HAL to invoke the actual data transfer to ILI9341.
 * Pero, 2021
 */

#ifndef TOUCHGFX_DATATRANSFER_H
#define TOUCHGFX_DATATRANSFER_H

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

void touchgfxDisplayDriverTransmitBlock(uint8_t* pixels, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
uint32_t touchgfxDisplayDriverTransmitActive(void);

#ifdef __cplusplus
}
#endif
#endif
