#pragma once

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"

#ifdef __cplusplus
extern "C" {
#endif
#define R61529_TFTWIDTH   	480		// R61529 TFT width in default rotation
#define R61529_TFTHEIGHT  	320		// R61529 TFT height in default rotation 



#define R61529_NOP		0x00	// No Op, also reset write state (acording to PDF)
#define R61529_RESET		0x01	// Software reset
#define R61529_SLPOUT		0x11	// Sleep out (Exit sleep)
#define R61529_DISLYON		0x29	// Display ON
#define R61529_CASET		0x2A	// Column Address Set 
#define R61529_PASET		0x2B	// Page Address Set 
#define R61529_RAMWR		0x2C	// Memory Write 
#define R61529_RAMRD		0x2E	// Memory Read
#define R61529_MADCTL		0x36	// Memory Address Control
#define R61529_SETPIXF		0x3A	// Set Pixel Format
#define R61529_MCAP		0xB0	// Manufacturer Command Access Protect
#define R61529_BLCTRL1		0xB8	// Backlight Control 1
#define R61529_BLCTRL2		0xB9	// Backlight Control 2
#define R61529_BLCTRL3		0xBA	// Backlight Control 3
#define R61529_FMAIS		0xB3	// Frame Memory Access and Interface Setting
#define R61529_DISMODE		0xB4	// Display Mode
#define R61529_PANDSET		0xC0	// Panel Driving Setting;
#define R61529_DTSNM		0xC1	// Display Timing Setting for Normal Mode
#define R61529_SGDTSET		0xC4	// Source/Gate Driving Timing Setting
#define R61529_DPIPCTL		0xC6	// DPI polarity control
#define R61529_GAMSETA		0xC8	// Gamma Setting A Set
#define R61529_GAMSETB		0xC9	// Gamma Setting B Set
#define R61529_GAMSETC		0xCA	// Gamma Setting C Set
#define R61529_PSCPSET		0xD0	// Power Setting Charge Pump Setting
#define R61529_VCOMSET		0xD1	// VCOM Setting
#define R61529_NVMACTL		0xE0	// NVM Access Control
#define R61529_DDBWCTL		0xE1	// Set DDB Write Control
#define R61529_NVMLCTL		0xE2	// NVM Load Control


#define MADCTL_RGB 0x00  // Red-Green-Blue pixel order
#define MADCTL_GS  0x01
#define MADCTL_SS  0x02
#define MADCTL_MH  0x04  // LCD refresh right to left
#define MADCTL_BGR 0x08  // Blue-Green-Red pixel order
#define MADCTL_ML  0x10  // LCD refresh Bottom to top
#define MADCTL_MV  0x20  // Row/Column exchange
#define MADCTL_MX  0x40  // Right to left
#define MADCTL_MY  0x80  // Bottom to top

esp_err_t esp_lcd_new_panel_r61529(const esp_lcd_panel_io_handle_t io, const esp_lcd_panel_dev_config_t *panel_dev_config, esp_lcd_panel_handle_t *ret_panel);

#ifdef __cplusplus
}
#endif