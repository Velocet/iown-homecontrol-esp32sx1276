#ifndef IOHC_BOARD_H
#define IOHC_BOARD_H

#undef CC1101
#define RADIO_SX127X
#define Regulatory_Domain_EU_868
#undef ESP8266
//#define HELTEC
//#define LILYGO
/*
 * Board pins definitions
 */
// OK Heltec Wifi ESP32 Lora v2.1
#define RADIO_SCLK_PIN       5 
#define RADIO_MISO_PIN      19 
#define RADIO_MOSI_PIN      27 
#define RADIO_CS_PIN        18 
#define RADIO_DIO0_PIN      26 
#define RADIO_RST_PIN       14
#define BOARD_LED_PIN       25 
#ifdef LILYGO
#define RADIO_DIO1_PIN      33 //LILYGO
#define RADIO_DIO2_PIN      32 //LILYGO
#elif defined(HELTEC)
#define RADIO_DIO1_PIN      35 //HELTEC
#define RADIO_DIO2_PIN      34 //HELTEC
#define RADIO_BUSY_PIN      32
#endif

// OK LilyGo Wifi ESP32 Lora v2.1.6
// https://github.com/LilyGO/ESP32-Paxcounter/blob/master/src/hal/ttgov2.h 


#if defined(ESP8266)
#define RADIO_RESET                                 4   // NodeMCU D2
#define RADIO_MOSI                                  13  // NodeMCU D7
#define RADIO_MISO                                  12  // NodeMCU D6
#define RADIO_SCLK                                  14  // NodeMCU D5
#define RADIO_NSS                                   15  // NodeMCU D8
#elif defined(ESP32)
    #define RADIO_MOSI             RADIO_MOSI_PIN //                 23  // Default VSPI
    #define RADIO_MISO             RADIO_MISO_PIN //                 19  // Default VSPI
    #define RADIO_SCLK             RADIO_SCLK_PIN //                 18  // Default VSPI
    #if defined(RADIO_SX127X)
        #define RADIO_RESET        RADIO_RST_PIN  //                 12
        #define RADIO_NSS          RADIO_CS_PIN   //                 25
    #elif defined(CC1101)
        #define RADIO_NSS                           32
    #endif
#endif

#if defined(RADIO_SX127X)
    //#define RADIO_DIO_0                             5   // NodeMCU D1
    //#define RADIO_DIO_1                             2   // NodeMCU D4 // Not used - No wire
    //#define RADIO_DIO_2                             2   // NodeMCU D4 // Not used - No wire
    //#define RADIO_DIO_4                             2   // NodeMCU D4
    #define RADIO_DIO_0                             RADIO_DIO0_PIN //                 35
    //#define RADIO_DIO_1                             34      // Not used - No wire
    //#define RADIO_DIO_2                             34      // Not used - No wire
    #define RADIO_DIO_4                             RADIO_DIO2_PIN //                 34
#elif defined(CC1101)
    #define RADIO_DIO_0                             14
    #define RADIO_DIO_2                             33
#endif

#if defined(RADIO_SX127X)
    #define RADIO_PACKET_AVAIL                      RADIO_DIO_0     // Packet Received / CRC ok from Radio
    #define RADIO_DATA_AVAIL                        RADIO_DIO_1     // FIFO empty from Radio
    #define RADIO_RXTIMEOUT                         RADIO_DIO_2     // Radio Rx Sequencer timeout (used to switch the receiver frequency)
    #define RADIO_PREAMBLE_DETECTED                 RADIO_DIO_4     // Preamble detected from Radio (used instead of FIFO empty)
#elif defined(CC1101)
    #define RADIO_PREAMBLE_DETECTED                 RADIO_DIO_0     // Preamble detected from Radio (used instead of FIFO empty)
    //#define RADIO_RXCLK                             RADIO_DIO_0     // Radio Rx CLK for serial data sync
    // GDO Serial Clk (0x0B)
    // GD2 
#endif

#define SPI_CLK_FRQ                                 10000000

/*
 * Defines the time required for the TCXO to wakeup [ms].
 */

#define BOARD_TCXO_WAKEUP_TIME                      0
#define BOARD_READY_AFTER_POR						10000

#define PREAMBLE_MSB                                0x00
#define PREAMBLE_LSB        64//                        52  // 0x34: 12ms to have receiver up and running (52 0x55 bytes - 13,54mS)
#define SYNC_BYTE_1                                 0xff
#define SYNC_BYTE_2                                 0x33    // Sync word - Size must be set to 2; first byte 0xff then 0x33 size-1 times
//#define SYNC_BYTE_2_ENC                             0xB3    // Sync word Inverted + Encoded with start & stop bits

  #define CHANNEL1  868250000 //2W
  #define CHANNEL2  868950000 //1W 2W
  #define CHANNEL3  869850000 //2W

#define FREQS2SCAN              {CHANNEL2, CHANNEL1, CHANNEL3} 
#define MAX_FREQS                1       // Number of Frequencies to scan through Fast Hopping set to 1 to disable FHSS

#if defined(ESP8266)
    #define SCAN_LED                                D0
#elif defined(HELTEC)
    #define SCAN_LED                  BOARD_LED_PIN //              22
#endif
#define RX_LED                        SCAN_LED

#endif