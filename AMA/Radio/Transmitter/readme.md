# Arduino Nano Transmitter

### Arduino Nano Pinouts

| Connect |  Pin  | Pin   | Connect |
| ----- | ------ | ------ | ------ |
| Buzzer           | TX     | Vin   | 7-12VDC  |
| LED              | RX     | Gnd   | Gnd      |
| N/C              | Reset  | Reset | N/C      |
| Gnd              | Gnd    | 5v0   | VOut     |
| OPen             | D2     | ADC7  | CD4052-Y |
| CD4051/CD4052-A  | D3     | ADC6  | CD4052-X |
| CD4051/CD4052-B  | D4     | SDC   | LCD SDC  |
| CD4051-C         | D5     | SDA   | LCD SDA  |
| CD4051 #3 (Menu?)| D6     | ADC3  | Role     |
| CD4051 #1 (trims)| D7     | ADC2  | Pitch    |
| CD4051 #2 (switch)| D8    | ADC1  | Yaw      |
| Nrf24 - CE       | D9     | ADC0  | Throttle |
| Nrf24 - CSN      | D10    | Aref  | 5v0      |
| Nrf24 - MOSI     | D11    | 3v3   | N/C      |
| Nrf24 - MISO     | D12    | D13   | Nrf24 - CSN|

### NRF24 with PA and antenna Pinouts
| Arduino Pin |  NRF24 Pin  | NRF24 Pin   | Arduino Pin |
| ----- | ------ | ------ | ------ |
| GND   | GND    | VCC    | 3v3    |
| D9    | CE     | CSN    | D10    |
| D13   | SCK    | MOSI   | D11    |
| D12   | MISO   | IRQ    | N/C    |



> **Transmitter performance tuned setup**
> - AutoAck = false 
> - Max power 
- - setPALevel( RF24_PA_MAX ) ; 
> - Min speed (for better range I presume)
> - - setDataRate( RF24_250KBPS ) ; 
> - 8 bits CRC
> - - setCRCLength( RF24_CRC_8 ) ; 
> - Disable dynamic payloads 
> -  -write_register(DYNPD,0); 
> - increase the delay between retries & # of retries 
> - - setRetries(15,15);

> - Modify pipeOut to be unique for your codebase
