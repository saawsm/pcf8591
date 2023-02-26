#ifndef _PCF8591_H
#define _PCF8591_H

#include <i2c.h>
#include <esp_err.h>

#ifdef __cplusplus
extern "C" {
#endif

// See section 8.2, figure. 4
typedef enum {
   PCF8591_MODE_4_SINGLES = 0,    // 0-3 channels (inclusive)
   PCF8591_MODE_3_DIFF,           // 0-2 channels (inclusive)
   PCF8591_MODE_2_SINGLES_1_DIFF, // 0-2 channels (inclusive)
   PCF8591_MODE_2_DIFFS,          // 0-1 channels (inclusive)
} pcf8591_input_mode_t;

/**
 * @brief Setup the PCF8591 device
 *
 * Setup PCF8591 and the I2C descriptor.
 *
 * @param dev I2C device descriptor
 * @param port I2C port the device is using
 * @param address I2C device address
 * @return ESP_OK on success
 */
esp_err_t pcf8591_init(i2c_dev_t* dev, i2c_port_t port, uint8_t address);

/**
 * @brief Cleanup the PCF8591 device
 *
 * @param dev I2C device descriptor
 * @return ESP_OK on success
 */
esp_err_t pcf8591_free(i2c_dev_t* dev);

/**
 * @brief Read value of an analog input
 *
 * @param dev I2C device descriptor
 * @param mode Analog input mux mode
 * @param channel Analog channel (mode dependant - see section 8.2, fig. 4)
 * @param[out] val Analog value
 * @return ESP_OK on success
 */
esp_err_t pcf8591_read(i2c_dev_t* dev, pcf8591_input_mode_t mode, uint8_t channel, uint8_t* val);

/**
 * @brief Write value to analog output
 *
 * @param dev I2C device descriptor
 * @param val DAC value
 * @return ESP_OK on success
 */
esp_err_t pcf8591_write(i2c_dev_t* dev, uint8_t val);

#ifdef __cplusplus
}
#endif

#endif