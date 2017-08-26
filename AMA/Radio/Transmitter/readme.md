# Arduino Nano Transmitter

.......... <- TX        Vin -> 7-12Vin
.......... <- RX        GND -> Gnd
.......... <- RST       RST ->..........
       Gnd <- Gnd       5v0 -> Out
.......... <- D2        ACD7 -> CD4052-Y
.......... <- D3   ACD6 -> CD4052-X
.......... <- D4    SDC -> LCD
.......... <- D5    SDA -> LCD
.......... <- D6   ACD3 -> Roll
.......... <- D7   ACD2 -> Pitch
.......... <- D8   ACD1 -> Yaw
.......... <- D9   ACD0 -> Throttle
.......... <- D10  Aref -> 5v0
.......... <- D11   3v3 ->..........
.......... <- D12   D13 -> Nrf24 - 

### Arduino Nano Pinouts

Dillinger is currently extended with the following plugins. Instructions on how to use them in your own application are linked below.

| Connect |  Pin  | Pin   | Connect |
| ----- | ------ | ------ | ------ |
|       | TX     | Vin   | 7-12VDC|
|       | RX     | Gnd   | Gnd    |
|       | Reset  | Reset |      |
| Gnd   | Gnd    | 5v0   | VOut     |
|       | D2     | ADC7  | CD4052-Y |
|       | D3     | ADC6  | CD4052-X |
| CD4051-A       | D4     | SDC   | LCD SDC  |
| CD4051-B       | D5     | SDA   | LCD SDA  |
| CD4051-C       | D6     | ADC3  | Role     |
| CD4051-2 (btns)| D7     | ADC2  | Pitch    |
| CD4051-1 (switch)| D8     | ADC1  | Yaw      |
| Nrf24 - CE     | D9     | ADC0  | Throttle |
| Nrf24 - D10    | D10    | Aref  | 5v0      |
| Nrf24 - MOSI   | D11    | 3v3   | NC       |
| Nrf24 - MISO   | D12    | D13   | Nrf24 - CSN  |

# NRF24 with PA and antenna
| Arduino Pin |  NRF24 Pin  | NRF24 Pin   | Arduino Pin |
| ----- | ------ | ------ | ------ |
| GND   | GND    | VCC    | 3v3    |
| D9    | CE     | CSN    | D10     |
| D13   | SCK    | MOSI   | D11    |
| D12   | MISO   | IRQ    | N/C    |



>  a
> b

**Free Software, Hell Yeah!**

Online GitHub md editor: http://dillinger.io/
   
