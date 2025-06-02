#ifndef SD_CARD_H
#define  SD_CARD_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <M5Unified.h>
#include <M5GFX.h>

#define SD_SPI_CS_PIN   47
#define SD_SPI_SCK_PIN  39
#define SD_SPI_MOSI_PIN 38
#define SD_SPI_MISO_PIN 40

inline void sd_card_setup() {
    SPI.begin(SD_SPI_SCK_PIN, SD_SPI_MISO_PIN, SD_SPI_MOSI_PIN, SD_SPI_CS_PIN);

    if (!SD.begin(SD_SPI_CS_PIN, SPI, 25000000)) {
        // Print a message if SD card initialization failed or if the SD card does not exist.
        M5.Display.print("\n SD card not detected\n");
        return;
    }
    M5.Display.print("\n SD card detected\n");
    M5.Display.printf("[SD] Card Type: %d\n", SD.cardType());
    M5.Display.printf("[SD] Card Size: %llu\n", SD.cardSize());
    M5.Display.printf("[SD] Used Bytes: %llu\n", SD.usedBytes());

    M5.Display.print("\n Files on SD card:\n");
    File root = SD.open("/");
    if (!root) {
        M5.Display.print("Failed to open root directory\n");
        return;
    }
    File file = root.openNextFile();
    while (file) {
        M5.Display.printf("NAME: %s\tSIZE: %u\n", file.name(), file.size());
        file = root.openNextFile();
    }
}

#endif
