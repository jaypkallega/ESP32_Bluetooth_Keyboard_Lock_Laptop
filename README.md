# ESP32_Bluetooth_Keyboard_Lock_Laptop
This project uses ESP32_WROOM-32 to identify as a bluetooth keyboard. It is connected to a ultrasonic sensor to detect presence. It will lock the laptop when presence is not detected. The code will check distance and indicate if an obstacle/person is away for 5 seconds from a fixed distance ( it is set at 70cm here). A lock keyboard press is issued via bluetooth keyboard
Items needed : ESP 32 WROOM, Ultrasonic sensor HC SR04
the code needs to be executed on VScode with platformio extension. It needs nible ble and bluetooth keyboard libraries.
