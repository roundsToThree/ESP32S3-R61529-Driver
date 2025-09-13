# ESP32S3-R61529-Driver
A display driver for the R61529 LCD that supports communication over the ESP32S3's i80 bus with DMA frame buffers (16 bit parallel).

Made for the ESP-IDF (Not Arduino) framework, probably works in arduino with some tweaks.

# ⚠️⚠️ WIP ⚠️⚠️
## This project is still in progress and not all functionality has been implemented, it should give you a starting point in using this in your own project


# Usage
Place the R61529.c & R61529.h files in your project\
Include the header in your code (e.g. `#include "R61529.h"`)\
The `esp_lcd_new_panel_r61529()` function is now provided, which can be used in the same way as the other pre-built display drivers in the ESP core.

# Support
| Feature | Status |
|---|:---:|
|16b Colour | ✅ |
|18/24b Colour | 🚧 |
|TE Pin | ❌ |
|Rotation/Mirror| 🚧 |
|Sleep/Invert/Etc| 🚧 |

# Testing
I was not able to get my Octal PSRAM to clock at 120MHz, however at 80MHz, I was able to completely refresh the display with minimal tearing at 10FPS. Pixel Clock 16MHz.\
Compared to fast GPIO bitbashing, its somewhere around 5-10x faster.

# Example
```c
// Initialise the bus
esp_lcd_i80_bus_handle_t i80_bus = NULL;
esp_lcd_i80_bus_config_t bus_config = {
    .dc_gpio_num = TFT_DC,
    .wr_gpio_num = TFT_WR,
    .data_gpio_nums = {
        TFT_D0, TFT_D1, TFT_D2, TFT_D3, TFT_D4, TFT_D5, TFT_D6, TFT_D7,
        TFT_D8, TFT_D9, TFT_D10, TFT_D11, TFT_D12, TFT_D13, TFT_D14, TFT_D15},
    .clk_src = LCD_CLK_SRC_PLL240M,
    .bus_width = 16,
    // This is here as I transfer the whole frame in one tx, you can probably change these
    .max_transfer_bytes = TFT_WIDTH * TFT_HEIGHT * sizeof(uint16_t),
    .dma_burst_size = TFT_WIDTH * TFT_HEIGHT,
    .psram_trans_align = 16,
    .sram_trans_align = 0};
ESP_ERROR_CHECK(esp_lcd_new_i80_bus(&bus_config, &i80_bus));

// The RD pin should be tied high, this may be moved inside the code at a later date
gpio_config_t io_conf = {
    .mode = GPIO_MODE_OUTPUT,
    .pin_bit_mask = 1ULL << TFT_RD};
gpio_config(&io_conf);
gpio_set_level(TFT_RD, 1);

// Create the IO struct
esp_lcd_panel_io_handle_t io_handle = NULL;
esp_lcd_panel_io_i80_config_t io_config = {
    .cs_gpio_num = TFT_CS,
    // Change this pixel clock if unstable or you are getting gdma errors
    .pclk_hz = 16000000, // 2 MHz
    .trans_queue_depth = 10,
    .dc_levels = {
        .dc_idle_level = 0,
        .dc_cmd_level = 0,
        .dc_dummy_level = 0,
        .dc_data_level = 1,
    },
    .lcd_cmd_bits = 16,
    .lcd_param_bits = 16};
ESP_ERROR_CHECK(esp_lcd_new_panel_io_i80(i80_bus, &io_config, &io_handle));

// Create the panel driver
esp_lcd_panel_handle_t panel_handle = NULL;
esp_lcd_panel_dev_config_t panel_config = {
    .reset_gpio_num = TFT_RST,
    .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
    .bits_per_pixel = 16,
};
ESP_ERROR_CHECK(esp_lcd_new_panel_r61529(io_handle, &panel_config, &panel_handle));

// Reset & Init
esp_lcd_panel_reset(panel_handle);
esp_lcd_panel_init(panel_handle);
esp_lcd_panel_disp_on_off(panel_handle, true);


// Make Framebuffer and write to screen
uint16_t *fb;
// Change cap to MALLOC_CAP_INTERNAL if you dont want to use PSRAM (note memory limit - you probably cant fit a whole frame in internal memory)
fb = esp_lcd_i80_alloc_draw_buffer(io_handle, TFT_WIDTH * TFT_HEIGHT, MALLOC_CAP_DMA | MALLOC_CAP_SPIRAM);
for (int i = 0; i < TFT_WIDTH * TFT_HEIGHT; i++)
{
   // Fill screen white (change colour if you want)
    fb[i] = 0xFFFF;
}

// Draw
esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, TFT_WIDTH, TFT_HEIGHT, fb);
    

```

# Final Notes
This was made for a project that initially used the Arduino GFX Library (As it supported ESP32S3 16 bit parallel).\
That project no longer seems to compile in Arduino core 3, alternatives like TFT_eSPI don't support 16 bit parallel communication.\
I figured i'd use this oppourtunity to write my own driver in ESP-IDF. I haven't done that before, or used ESP-IDF, so there may be issues.\
Please let me know if theres any issues with this code or if I can help you use this in a different way.\
I also have bit-bashing Arduino code if you would like to use this display on a different platform or not using the i80 bus.
