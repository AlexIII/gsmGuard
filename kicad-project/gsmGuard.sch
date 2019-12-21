EESchema Schematic File Version 4
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L gsmGuard-rescue:SIM800C-ArduinoModules U4
U 1 1 5C86B4D4
P 6700 1550
F 0 "U4" H 6700 2075 50  0000 C CNN
F 1 "SIM800C" H 6700 1984 50  0000 C CNN
F 2 "cad:SIM800C" H 6700 1550 50  0001 C CNN
F 3 "" H 6700 1550 50  0001 C CNN
	1    6700 1550
	1    0    0    -1  
$EndComp
$Comp
L gsmGuard-rescue:RTC_DS3231-ArduinoModules U2
U 1 1 5C87EF3B
P 6600 2700
F 0 "U2" H 6827 2751 50  0000 L CNN
F 1 "RTC_DS3231" H 6827 2660 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 6950 2700 50  0001 C CNN
F 3 "" H 6950 2700 50  0001 C CNN
	1    6600 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:Buzzer BZ1
U 1 1 5C893D49
P 8800 4550
F 0 "BZ1" H 8953 4579 50  0000 L CNN
F 1 "Buzzer" H 8953 4488 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" V 8775 4650 50  0001 C CNN
F 3 "~" V 8775 4650 50  0001 C CNN
	1    8800 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_PHOTO R1
U 1 1 5C893F77
P 7500 3350
F 0 "R1" H 7570 3396 50  0000 L CNN
F 1 "1-300k" H 7570 3305 50  0000 L CNN
F 2 "Opto-Devices:Resistor_LDR_4.9x4.2_RM2.54" V 7550 3100 50  0001 L CNN
F 3 "~" H 7500 3300 50  0001 C CNN
	1    7500 3350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5C894014
P 7500 3850
F 0 "R2" H 7570 3896 50  0000 L CNN
F 1 "4.7k" H 7570 3805 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" V 7430 3850 50  0001 C CNN
F 3 "~" H 7500 3850 50  0001 C CNN
	1    7500 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5C89416D
P 8750 3850
F 0 "C1" H 8865 3896 50  0000 L CNN
F 1 "0.1uF" H 8865 3805 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 8788 3700 50  0001 C CNN
F 3 "~" H 8750 3850 50  0001 C CNN
	1    8750 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 5C8942AC
P 9350 2250
F 0 "C2" H 9468 2296 50  0000 L CNN
F 1 "1000uF 6.3V" H 9468 2205 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D8.0mm_P3.50mm" H 9388 2100 50  0001 C CNN
F 3 "~" H 9350 2250 50  0001 C CNN
	1    9350 2250
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Reed SW1
U 1 1 5C89441A
P 6650 4200
F 0 "SW1" H 6650 4422 50  0000 C CNN
F 1 "SW_Reed" H 6650 4331 50  0000 C CNN
F 2 "cad:reed-1" H 6650 4200 50  0001 C CNN
F 3 "" H 6650 4200 50  0001 C CNN
	1    6650 4200
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x03_Male J2
U 1 1 5C894585
P 8050 2200
F 0 "J2" H 8156 2478 50  0000 C CNN
F 1 "Conn_01x03_Male" H 8156 2387 50  0000 C CNN
F 2 "Connectors_Phoenix:PhoenixContact_MC-G_03x3.81mm_Angled" H 8050 2200 50  0001 C CNN
F 3 "~" H 8050 2200 50  0001 C CNN
	1    8050 2200
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J3
U 1 1 5C894612
P 8050 2700
F 0 "J3" H 8156 2978 50  0000 C CNN
F 1 "Conn_01x04_Male" H 8156 2887 50  0000 C CNN
F 2 "Connectors_Phoenix:PhoenixContact_MC-G_04x3.81mm_Angled" H 8050 2700 50  0001 C CNN
F 3 "~" H 8050 2700 50  0001 C CNN
	1    8050 2700
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRLML6402 Q1
U 1 1 5C8946E7
P 9000 1950
F 0 "Q1" H 9205 1996 50  0000 L CNN
F 1 "IRLML6401" H 9205 1905 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 9200 1875 50  0001 L CIN
F 3 "https://www.infineon.com/dgdl/irlml6402pbf.pdf?fileId=5546d462533600a401535668d5c2263c" H 9000 1950 50  0001 L CNN
	1    9000 1950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J1
U 1 1 5C89481C
P 9400 2750
F 0 "J1" H 9427 2726 50  0000 L CNN
F 1 "Conn_01x02_Female" H 9427 2635 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 9400 2750 50  0001 C CNN
F 3 "~" H 9400 2750 50  0001 C CNN
	1    9400 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:Microphone MK1
U 1 1 5CB2F6FE
P 7500 1750
F 0 "MK1" H 7370 1704 50  0000 R CNN
F 1 "Microphone" H 7370 1795 50  0000 R CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" V 7500 1850 50  0001 C CNN
F 3 "~" V 7500 1850 50  0001 C CNN
	1    7500 1750
	-1   0    0    1   
$EndComp
Wire Wire Line
	7200 1500 7500 1500
Wire Wire Line
	7500 1500 7500 1550
Wire Wire Line
	7200 1600 7350 1600
Wire Wire Line
	7350 1600 7350 2000
Wire Wire Line
	7350 2000 7500 2000
Wire Wire Line
	7500 2000 7500 1950
Text GLabel 5900 1350 0    50   BiDi ~ 0
VMOD
Text GLabel 6200 1750 0    50   BiDi ~ 0
GND
Text GLabel 6200 2050 0    50   BiDi ~ 0
GND
Text GLabel 4600 3500 0    50   BiDi ~ 0
GND
Text GLabel 6200 1650 0    50   BiDi ~ 0
TX
Text GLabel 6200 1550 0    50   BiDi ~ 0
RX
Text GLabel 6200 2600 0    50   BiDi ~ 0
SDA
Text GLabel 6200 2700 0    50   BiDi ~ 0
SCL
Text GLabel 6200 2900 0    50   BiDi ~ 0
GND
Text GLabel 6200 2500 0    50   BiDi ~ 0
VSENS
$Comp
L Device:R R3
U 1 1 5CB31742
P 7500 4600
F 0 "R3" H 7570 4646 50  0000 L CNN
F 1 "4.7k" H 7570 4555 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" V 7430 4600 50  0001 C CNN
F 3 "~" H 7500 4600 50  0001 C CNN
	1    7500 4600
	1    0    0    -1  
$EndComp
Text GLabel 7400 4400 0    50   BiDi ~ 0
VSENS
$Comp
L Device:R R4
U 1 1 5CB31BB4
P 7800 4600
F 0 "R4" H 7870 4646 50  0000 L CNN
F 1 "4.7k" H 7870 4555 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" V 7730 4600 50  0001 C CNN
F 3 "~" H 7800 4600 50  0001 C CNN
	1    7800 4600
	1    0    0    -1  
$EndComp
Text GLabel 7500 4800 3    50   BiDi ~ 0
SDA
Text GLabel 7800 4800 3    50   BiDi ~ 0
SCL
Wire Wire Line
	7800 4800 7800 4750
Wire Wire Line
	7500 4800 7500 4750
Wire Wire Line
	7500 4450 7500 4400
Wire Wire Line
	7500 4400 7400 4400
Wire Wire Line
	7800 4400 7800 4450
Wire Wire Line
	7500 4400 7800 4400
Text GLabel 5150 4850 3    50   BiDi ~ 0
SDA
Text GLabel 5050 4850 3    50   BiDi ~ 0
SCL
Text GLabel 8650 4650 0    50   BiDi ~ 0
GND
Wire Wire Line
	8650 4650 8700 4650
Connection ~ 7500 4400
$Comp
L Device:R R5
U 1 1 5CB33B30
P 8100 4600
F 0 "R5" H 8170 4646 50  0000 L CNN
F 1 "4.7k" H 8170 4555 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" V 8030 4600 50  0001 C CNN
F 3 "~" H 8100 4600 50  0001 C CNN
	1    8100 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 4800 8100 4750
Wire Wire Line
	8100 4400 8100 4450
Wire Wire Line
	7800 4400 8100 4400
Connection ~ 7800 4400
Text GLabel 7400 4100 0    50   BiDi ~ 0
GND
Text GLabel 7400 3100 0    50   BiDi ~ 0
VSENS
Wire Wire Line
	7400 4100 7500 4100
Wire Wire Line
	7500 4100 7500 4000
Wire Wire Line
	7500 3700 7500 3600
Wire Wire Line
	7500 3200 7500 3100
Wire Wire Line
	7500 3100 7400 3100
Text GLabel 7400 3600 0    50   BiDi ~ 0
A0
Wire Wire Line
	7500 3600 7400 3600
Connection ~ 7500 3600
Wire Wire Line
	7500 3600 7500 3500
Text GLabel 5800 3900 2    50   BiDi ~ 0
A0
Text GLabel 8100 4800 3    50   BiDi ~ 0
D9
Text GLabel 4600 4300 0    50   BiDi ~ 0
D9
$Comp
L Device:R R7
U 1 1 5CB3745D
P 8400 3850
F 0 "R7" H 8470 3896 50  0000 L CNN
F 1 "300k" H 8470 3805 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" V 8330 3850 50  0001 C CNN
F 3 "~" H 8400 3850 50  0001 C CNN
	1    8400 3850
	1    0    0    -1  
$EndComp
Text GLabel 8300 4100 0    50   BiDi ~ 0
GND
Wire Wire Line
	8300 4100 8400 4100
Wire Wire Line
	8400 4100 8400 4000
Wire Wire Line
	8400 3700 8400 3600
Wire Wire Line
	8400 3200 8400 3100
Wire Wire Line
	8400 3100 8300 3100
Wire Wire Line
	8400 3600 8300 3600
Connection ~ 8400 3600
Wire Wire Line
	8400 3600 8400 3500
$Comp
L Device:R R6
U 1 1 5CB379C1
P 8400 3350
F 0 "R6" H 8470 3396 50  0000 L CNN
F 1 "1M" H 8470 3305 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" V 8330 3350 50  0001 C CNN
F 3 "~" H 8400 3350 50  0001 C CNN
	1    8400 3350
	1    0    0    -1  
$EndComp
Text GLabel 8300 3600 0    50   BiDi ~ 0
A1
Text GLabel 6550 3900 0    50   BiDi ~ 0
D7
Text GLabel 4600 4100 0    50   BiDi ~ 0
D7
Text GLabel 5650 2100 1    50   BiDi ~ 0
D6
Text GLabel 4600 4000 0    50   BiDi ~ 0
D6
Text GLabel 8650 4450 0    50   BiDi ~ 0
D8
Wire Wire Line
	8650 4450 8700 4450
Text GLabel 4600 4200 0    50   BiDi ~ 0
D8
Text GLabel 7850 2900 0    50   BiDi ~ 0
GND
Text GLabel 7850 2600 0    50   BiDi ~ 0
VSENS
Text GLabel 7850 2100 0    50   BiDi ~ 0
VSENS
Text GLabel 7850 2300 0    50   BiDi ~ 0
GND
Text GLabel 7850 2200 0    50   BiDi ~ 0
D9
Text GLabel 7850 2700 0    50   BiDi ~ 0
D10
Text GLabel 7850 2800 0    50   BiDi ~ 0
D11
Text GLabel 9200 2850 0    50   BiDi ~ 0
GND
Text GLabel 9350 2400 3    50   BiDi ~ 0
GND
Text GLabel 4600 3700 0    50   BiDi ~ 0
RX
Text GLabel 4600 3800 0    50   BiDi ~ 0
TX
Text GLabel 6200 1450 0    50   BiDi ~ 0
M_ON
$Comp
L gsmGuard-rescue:ArduinoProMini-ArduinoModules U1
U 1 1 5CB428E9
P 5750 3800
F 0 "U1" H 4700 4700 50  0000 C CNN
F 1 "ArduinoProMini" V 5200 4000 50  0000 C CNN
F 2 "cad:pro_mini" H 5700 3800 50  0001 C CNN
F 3 "" H 5700 3800 50  0001 C CNN
	1    5750 3800
	1    0    0    -1  
$EndComp
Text GLabel 6550 4500 0    50   BiDi ~ 0
GND
Wire Wire Line
	6550 4500 6650 4500
Wire Wire Line
	6650 4500 6650 4400
Wire Wire Line
	6650 4000 6650 3900
Wire Wire Line
	6650 3500 6650 3400
Wire Wire Line
	6650 3400 6550 3400
Wire Wire Line
	6650 3900 6550 3900
Connection ~ 6650 3900
Wire Wire Line
	6650 3900 6650 3800
$Comp
L Device:R R8
U 1 1 5CB4BDED
P 6650 3650
F 0 "R8" H 6720 3696 50  0000 L CNN
F 1 "1M" H 6720 3605 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" V 6580 3650 50  0001 C CNN
F 3 "~" H 6650 3650 50  0001 C CNN
	1    6650 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5CB4DB11
P 6850 4200
F 0 "C3" H 6965 4246 50  0000 L CNN
F 1 "0.1uF" H 6965 4155 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 6888 4050 50  0001 C CNN
F 3 "~" H 6850 4200 50  0001 C CNN
	1    6850 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 4050 6850 3900
Wire Wire Line
	6850 3900 6650 3900
Wire Wire Line
	6850 4350 6850 4500
Wire Wire Line
	6850 4500 6650 4500
Connection ~ 6650 4500
Text GLabel 8600 2750 0    50   BiDi ~ 0
VBAT
Text GLabel 9100 1550 1    50   BiDi ~ 0
VMOD
$Comp
L Device:R R9
U 1 1 5CB50E50
P 8850 2250
F 0 "R9" H 8920 2296 50  0000 L CNN
F 1 "4.7k" H 8920 2205 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" V 8780 2250 50  0001 C CNN
F 3 "~" H 8850 2250 50  0001 C CNN
	1    8850 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	8700 2250 8650 2250
Wire Wire Line
	8650 2250 8650 1950
Wire Wire Line
	8650 1950 8800 1950
Wire Wire Line
	9000 2250 9100 2250
Wire Wire Line
	9100 2250 9100 2150
Connection ~ 9100 2250
Text GLabel 4600 3900 0    50   BiDi ~ 0
D5
Text GLabel 8650 1850 1    50   BiDi ~ 0
D5
Wire Wire Line
	8650 1950 8650 1850
Connection ~ 8650 1950
Text GLabel 5800 3500 2    50   BiDi ~ 0
VBAT
Wire Wire Line
	8750 4100 8750 4000
Wire Wire Line
	8750 3600 8750 3700
Wire Wire Line
	8400 4100 8750 4100
Connection ~ 8400 4100
Wire Wire Line
	8400 3600 8750 3600
$Comp
L gsmGuard-rescue:MH-SR602-ArduinoModules U5
U 1 1 5CB60EB5
P 6600 2150
F 0 "U5" H 6827 2196 50  0000 L CNN
F 1 "MH-SR602" H 6827 2105 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 6650 2100 50  0001 C CNN
F 3 "" H 6650 2100 50  0001 C CNN
	1    6600 2150
	1    0    0    -1  
$EndComp
Text GLabel 4450 2700 0    50   BiDi ~ 0
GND
$Comp
L Device:R R10
U 1 1 5CC8F036
P 5050 1750
F 0 "R10" H 5120 1796 50  0000 L CNN
F 1 "1k" H 5120 1705 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" V 4980 1750 50  0001 C CNN
F 3 "~" H 5050 1750 50  0001 C CNN
	1    5050 1750
	1    0    0    -1  
$EndComp
Text GLabel 5650 1500 2    50   BiDi ~ 0
VBAT
Wire Wire Line
	9050 2750 9100 2750
Wire Wire Line
	4550 2700 4450 2700
$Comp
L Device:R R11
U 1 1 5CC990A6
P 4700 2700
F 0 "R11" H 4770 2746 50  0000 L CNN
F 1 "1k" H 4770 2655 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" V 4630 2700 50  0001 C CNN
F 3 "~" H 4700 2700 50  0001 C CNN
	1    4700 2700
	0    -1   -1   0   
$EndComp
Text GLabel 5800 3800 2    50   BiDi ~ 0
A1
Text GLabel 5800 4300 2    50   BiDi ~ 0
D10
Text GLabel 5800 4200 2    50   BiDi ~ 0
D11
Text GLabel 6550 3400 0    50   BiDi ~ 0
VBAT
Text GLabel 8300 3100 0    50   BiDi ~ 0
VBAT
Text GLabel 6200 2150 0    50   BiDi ~ 0
VBAT
$Comp
L gsmGuard-rescue:USB_UART-ArduinoModules U3
U 1 1 5CDA81B5
P 4000 2000
F 0 "U3" H 4000 2300 50  0000 L CNN
F 1 "USB_UART" V 4150 1750 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06_Pitch2.54mm" H 4150 2000 50  0001 C CNN
F 3 "" H 4150 2000 50  0001 C CNN
	1    4000 2000
	-1   0    0    -1  
$EndComp
Text GLabel 4400 2200 2    50   BiDi ~ 0
GND
Wire Wire Line
	4400 2000 5050 2000
Wire Wire Line
	4400 2300 4750 2300
Wire Wire Line
	4750 2300 4750 1500
Text GLabel 5800 4100 2    50   BiDi ~ 0
D12
Text GLabel 5100 1350 2    50   BiDi ~ 0
D12
$Comp
L Device:R R12
U 1 1 5CDB75C6
P 4500 1500
F 0 "R12" H 4570 1546 50  0000 L CNN
F 1 "4.7k" H 4570 1455 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" V 4430 1500 50  0001 C CNN
F 3 "~" H 4500 1500 50  0001 C CNN
	1    4500 1500
	0    -1   -1   0   
$EndComp
Text GLabel 4250 1500 0    50   BiDi ~ 0
GND
Wire Wire Line
	4250 1500 4350 1500
Wire Wire Line
	4650 1500 4750 1500
Connection ~ 4750 1500
Wire Wire Line
	5150 2150 5150 2100
Wire Wire Line
	4400 2100 5150 2100
Wire Wire Line
	4950 2750 4950 1900
Wire Wire Line
	4950 1900 4400 1900
Wire Wire Line
	5150 2450 5150 2700
Wire Wire Line
	4850 2700 5150 2700
Connection ~ 5150 2700
Wire Wire Line
	5150 2700 5150 2750
Wire Wire Line
	5050 2750 5050 2650
Wire Wire Line
	5050 2350 5050 2000
Wire Wire Line
	4750 1500 5050 1500
Wire Wire Line
	5050 2000 5050 1900
Connection ~ 5050 2000
Wire Wire Line
	5050 1600 5050 1500
Connection ~ 5050 1500
$Comp
L Device:R R13
U 1 1 5CDDB828
P 4950 1350
F 0 "R13" H 5020 1396 50  0000 L CNN
F 1 "4.7k" H 5020 1305 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" V 4880 1350 50  0001 C CNN
F 3 "~" H 4950 1350 50  0001 C CNN
	1    4950 1350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5050 1500 5350 1500
Wire Wire Line
	4750 1350 4800 1350
Wire Wire Line
	4750 1350 4750 1500
$Comp
L Diode:MBR0520LT D4
U 1 1 5CDEB784
P 8900 2750
F 0 "D4" H 8900 2966 50  0000 C CNN
F 1 "MBR0520LT" H 8900 2875 50  0000 C CNN
F 2 "Diodes_SMD:D_SOD-123F" H 8900 2575 50  0001 C CNN
F 3 "http://www.onsemi.com/pub_link/Collateral/MBR0520LT1-D.PDF" H 8900 2750 50  0001 C CNN
	1    8900 2750
	1    0    0    -1  
$EndComp
$Comp
L Diode:MBR0520LT D3
U 1 1 5CDEEC7F
P 5500 1500
F 0 "D3" H 5500 1400 50  0000 C CNN
F 1 "MBR0520LT" H 5500 1650 50  0000 C CNN
F 2 "Diodes_SMD:D_SOD-123F" H 5500 1325 50  0001 C CNN
F 3 "http://www.onsemi.com/pub_link/Collateral/MBR0520LT1-D.PDF" H 5500 1500 50  0001 C CNN
	1    5500 1500
	-1   0    0    1   
$EndComp
$Comp
L Diode:MBR0520LT D2
U 1 1 5CDEEF65
P 5150 2300
F 0 "D2" V 5196 2221 50  0000 R CNN
F 1 "MBR0520LT" V 5105 2221 50  0000 R CNN
F 2 "Diodes_SMD:D_SOD-123F" H 5150 2125 50  0001 C CNN
F 3 "http://www.onsemi.com/pub_link/Collateral/MBR0520LT1-D.PDF" H 5150 2300 50  0001 C CNN
	1    5150 2300
	0    -1   -1   0   
$EndComp
$Comp
L Diode:MBR0520LT D1
U 1 1 5CDEF033
P 5050 2500
F 0 "D1" V 5096 2421 50  0000 R CNN
F 1 "MBR0520LT" V 5005 2421 50  0000 R CNN
F 2 "Diodes_SMD:D_SOD-123F" H 5050 2325 50  0001 C CNN
F 3 "http://www.onsemi.com/pub_link/Collateral/MBR0520LT1-D.PDF" H 5050 2500 50  0001 C CNN
	1    5050 2500
	0    -1   -1   0   
$EndComp
Text GLabel 4600 3600 0    50   BiDi ~ 0
M_ON
$Comp
L Diode:1N4148W D5
U 1 1 5DBFD195
P 6050 1350
F 0 "D5" H 6050 1133 50  0000 C CNN
F 1 "1N4148W" H 6050 1224 50  0000 C CNN
F 2 "Diodes_SMD:D_SOD-123F" H 6050 1175 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 6050 1350 50  0001 C CNN
	1    6050 1350
	-1   0    0    1   
$EndComp
Text GLabel 5800 4000 2    50   BiDi ~ 0
VSENS
$Comp
L Device:CP C4
U 1 1 5DC71827
P 8700 3050
F 0 "C4" H 8818 3096 50  0000 L CNN
F 1 "33uF 6.3V" H 8818 3005 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:CP_Tantalum_Case-C_EIA-6032-28_Reflow" H 8738 2900 50  0001 C CNN
F 3 "~" H 8700 3050 50  0001 C CNN
	1    8700 3050
	1    0    0    -1  
$EndComp
Text GLabel 8700 3200 3    50   BiDi ~ 0
GND
Wire Wire Line
	9100 2250 9100 2750
Connection ~ 9100 2750
Wire Wire Line
	9100 2750 9200 2750
Wire Wire Line
	9350 2100 9350 1650
Wire Wire Line
	9350 1650 9100 1650
Wire Wire Line
	9100 1650 9100 1550
Wire Wire Line
	9100 1750 9100 1650
Connection ~ 9100 1650
Wire Wire Line
	8750 2750 8700 2750
Wire Wire Line
	8700 2900 8700 2750
Connection ~ 8700 2750
Wire Wire Line
	8700 2750 8600 2750
Text Notes 9350 3000 0    59   ~ 0
to battery 4.5v
Text Notes 8200 2400 1    59   ~ 0
1-wire
Text Notes 8150 3000 1    59   ~ 0
ext. sens
Text Notes 4050 5050 1    98   ~ 20
github.com/AlexIII/GsmGuard
$Comp
L Device:C C6
U 1 1 5DE275C7
P 7850 3850
F 0 "C6" H 7965 3896 50  0000 L CNN
F 1 "0.1uF" H 7965 3805 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 7888 3700 50  0001 C CNN
F 3 "~" H 7850 3850 50  0001 C CNN
	1    7850 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 4000 7850 4100
Wire Wire Line
	7850 4100 7500 4100
Connection ~ 7500 4100
Wire Wire Line
	7850 3700 7850 3600
Wire Wire Line
	7850 3600 7500 3600
$Comp
L Device:R R14
U 1 1 5DE312CD
P 5850 2250
F 0 "R14" H 5920 2296 50  0000 L CNN
F 1 "4.7k" H 5920 2205 50  0000 L CNN
F 2 "Resistors_SMD:R_1206" V 5780 2250 50  0001 C CNN
F 3 "~" H 5850 2250 50  0001 C CNN
	1    5850 2250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6000 2250 6200 2250
$Comp
L Device:C C5
U 1 1 5DE336DD
P 5650 2550
F 0 "C5" H 5765 2596 50  0000 L CNN
F 1 "0.1uF" H 5765 2505 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 5688 2400 50  0001 C CNN
F 3 "~" H 5650 2550 50  0001 C CNN
	1    5650 2550
	1    0    0    -1  
$EndComp
Text GLabel 5650 2700 3    50   BiDi ~ 0
GND
Wire Wire Line
	5650 2400 5650 2250
Wire Wire Line
	5700 2250 5650 2250
Connection ~ 5650 2250
Wire Wire Line
	5650 2250 5650 2100
$EndSCHEMATC
