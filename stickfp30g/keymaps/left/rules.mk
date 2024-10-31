###Add all custom function files
SRC += oled.c joystick.c
###
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
OLED_TRANSPORT = i2c
OLED_TIMEOUT = 0
###
#LTO_ENABLE = yes
###
JOYSTICK_ENABLE = yes
#POINTING_DEVICE_ENABLE = yes
#POINTING_DEVICE_DRIVER = analog_joystick
###
TAP_DANCER_ENABLE = yes
###
CONSOLE_ENABLE = yes
###
WPM_ENABLE = yes
