#include "pcf8591.h"

#define CTRL_AD_IN_PRG (4)
#define CTRL_DA_OUT_EN (6)

esp_err_t pcf8591_init(i2c_dev_t* dev, i2c_port_t port, uint8_t address) {
   return i2c_dev_desc(dev, port, address);
}

esp_err_t pcf8591_free(i2c_dev_t* dev) {
   return ESP_OK;
}

esp_err_t pcf8591_read(i2c_dev_t* dev, pcf8591_input_mode_t mode, uint8_t channel, uint8_t* val) {
   if (channel > 3)
      return ESP_ERR_INVALID_ARG;

   // enable D/A since it's needed for A/D conversion
   uint8_t ctrl = (1 << CTRL_DA_OUT_EN) | (mode << CTRL_AD_IN_PRG) | channel;

   // see section 8.4 for more information
   // TODO: Wrap successive calls with i2c_dev_mutex
   esp_err_t err = i2c_dev_read_reg(dev, ctrl, val, 1); // write ctrl reg then read (triggers new conversion)
   if (err != ESP_OK)
      return err;
   return i2c_dev_read(dev, NULL, 0, val, 1); // read last conversion result
}

esp_err_t pcf8591_write(i2c_dev_t* dev, uint8_t val) {
   uint8_t buf[2] = {(1 << CTRL_DA_OUT_EN), val};

   return i2c_dev_write(dev, NULL, 0, buf, sizeof(buf));
}