# PCF8591

A thread safe ESP-IDF component library for the PCF8591 8-bit A/D and D/A converter 

## Usage 
Requires the [`i2c`](https://github.com/saawsm/i2c) component.

```batch
cd components
git submodule add https://github.com/saawsm/i2c
git submodule add https://github.com/saawsm/pcf8591
```

Add `pcf8591` in project `CMakeLists.txt`