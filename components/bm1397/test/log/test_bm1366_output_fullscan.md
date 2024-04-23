
S19k-Pro (77 chips):
55 AA 51 09 00 10 00 00 11 5A 04
{0x00, 0x10, 0b00000000, 0b00000000, 0b00010001, 0b01011010}
-> 6 bit high = 64

(2^12)/(2^6) = 64
256/((2^12)/(2^6)) = 4

S19xp-luxos (110 chips):
55 AA 51 09 00 10 00 00 14 46 04
{0x00, 0x10, 0b00000000, 0b00000000, 0b00010100, 0b01000110}
-> 5 bit high = 32 * 128 chip address = 4096

(2^12)/(2^5) = 128
256/((2^12)/(2^5)) = 2

(2^32)-(2^5*128) = 4.294.963.200
(2^32)/128 = 33.554.432
2^7 = 128
(2^32)/(2^7) = 33.554.432
2^25 = 33.554.432
(2^32)/(2^7)-(2^25) = 0
2^32 / 2^7 - 2^(32-7) = 0 













Bitaxe Ultra (1 chip):
55 AA 51 09 00 10 00 00 15 1C 02
{0x00, 0x10, 0b00000000, 0b00000000, 0b00010101, 0b00011100}
-> 6 bit high = 64

Bitaxe Ultra (1 chip) - 20bit mask
{0x00, 0x10, 0b00000000, 0b00001111, 0b11111111, 0b11111111}
-> 20 bits high = 1048576 * 1 chip address




Starttime 13:58 Uhr
duration 1 fullscan: ((689521-2281)/1000) = 687,24 sec
for
version rolling = 2^16 = 65.536
nonce space = 2^32 = 4.294.967.296

{0x00, 0x10, 0b00000000, 0b00001111, 0b11111111, 0b11111111}
-> 20bit

12bit to explain - 2^12 = 4096

static const uint64_t BM1366_CHIP_COUNT = 1;
static const uint64_t BM1366_CORE_COUNT = 894;
// bm1366: 8 cores, 112 asic_cores each = 896 small cores (what are the 2 additional (896 vs. 894) small cores for?)

"asic_id": "BM1366",
"asic_addr": "0x1366",
"asic_core_num": 112,
"asic_small_core_num": 894,
"core_small_core_num": 8,
"asic_domain_num": 1,
"asic_addr_interval": 1


export IDF_PATH=/opt/esp/idf
/opt/esp/python_env/idf5.3_py3.10_env/bin/python /opt/esp/idf/tools/idf_monitor.py -p /dev/ttyACM0 -b 115200 --toolchain-prefix xtensa-esp32s3-elf- --target esp32s3 /workspaces/build/esp-miner.elf
root@31cc35ad06b6:/workspaces# export IDF_PATH=/opt/esp/idf
root@31cc35ad06b6:/workspaces# /opt/esp/python_env/idf5.3_py3.10_env/bin/python /opt/esp/idf/tools/idf_monitor.py -p /dev/ttyACM0 -b 115200 --toolchain-prefix xtensa-esp32s3-elf- --target esp32s3 /workspaces/build/esp-miner.elf
--- esp-idf-monitor 1.4.0 on /dev/ttyACM0 115200 ---
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
I (115) esp_image: segment 1: paddr=00023eb4 vaddr=3fc93cESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0x15 (USB_UART_CHIP_RESET),boot:0x28 (SPI_FAST_FLASH_BOOT)
Saved PC:0x40378db6
0x40378db6: esp_random at /opt/esp/idf/components/esp_hw_support/hw_random.c:84 (discriminator 1)

SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2810,len:0x178c
load:0x403c8700,len:0x4
load:0x403c8704,len:0xcb8
load:0x403cb700,len:0x2d9c
entry 0x403c8914
I (26) boot: ESP-IDF v5.3-dev-3225-g5a40bb8746 2nd stage bootloader
I (27) boot: compile time Apr 21 2024 13:11:58
I (27) boot: Multicore bootloader
I (31) boot: chip revision: v0.2
I (35) boot.esp32s3: Boot SPI Speed : 80MHz
I (40) boot.esp32s3: SPI Mode       : DIO
I (45) boot.esp32s3: SPI Flash Size : 2MB
I (49) boot: Enabling RNG early entropy source...
I (55) boot: Partition Table:
I (58) boot: ## Label            Usage          Type ST Offset   Length
I (66) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (73) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (81) boot:  2 factory          factory app      00 00 00010000 00100000
I (88) boot: End of partition table
I (92) esp_image: segment 0: paddr=00010020 vaddr=3c040020 size=13e8ch ( 81548) map
I (115) esp_image: segment 1: paddr=00023eb4 vaddr=3fc93c00 size=03228h ( 12840) load
I (119) esp_image: segment 2: paddr=000270e4 vaddr=40374000 size=08f34h ( 36660) load
I (129) esp_image: segment 3: paddr=00030020 vaddr=42000020 size=32d40h (208192) map
I (167) esp_image: segment 4: paddr=00062d68 vaddr=4037cf34 size=06c84h ( 27780) load
I (180) boot: Loaded app from partition at offset 0x10000
I (180) boot: Disabling RNG early entropy source...
I (192) cpu_start: Multicore app
I (201) cpu_start: Pro cpu start user code
I (201) cpu_start: cpu freq: 160000000 Hz
I (202) app_init: Application information:
I (204) app_init: Project name:     unit_test_stratum
I (210) app_init: App version:      4c3684d-dirty
I (215) app_init: Compile time:     Apr 23 2024 08:09:26
I (221) app_init: ELF file SHA256:  46e254ba8...
Warning: checksum mismatch between flashed and built applications. Checksum of built application is 4bf64982e125bc2785b93766264887450baa3779c2dd1e5014b870ce9bb926b6
I (227) app_init: ESP-IDF:          v5.3-dev-3225-g5a40bb8746
I (233) efuse_init: Min chip rev:     v0.0
I (238) efuse_init: Max chip rev:     v0.99 
I (243) efuse_init: Chip rev:         v0.2
I (248) heap_init: Initializing. RAM available for dynamic allocation:
I (255) heap_init: At 3FC98C00 len 00050B10 (322 KiB): RAM
I (261) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (267) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (273) heap_init: At 600FE100 len 00001EE8 (7 KiB): RTCRAM
I (280) spi_flash: detected chip: gd
I (284) spi_flash: flash io: dio
W (288) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (301) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
W (312) ADC: legacy driver is deprecated, please migrate to `esp_adc/adc_oneshot.h`
I (320) sleep: Configure to isolate all GPIO pins in sleep state
I (327) sleep: Enable automatic switching of GPIO sleep configuration
I (351) main_task: Started on CPU0
I (361) main_task: Calling app_main()

#### Running all the registered tests #####

Running Testing single BM1366 chip against a known valid block...
I (401) test_bm1366: ASIC: BM1366
I (401) test_bm1366: I2C initialized successfully
I (401) DS4432U.c: Set ASIC voltage = 1.250V [0xB9]
I (411) DS4432U.c: Writing 0xB9
I (411) serial: Initializing serial
I (411) bm1366Module: Initializing BM1366
I (1621) bm1366Module: 1 chip(s) detected on the chain
final refdiv: 2, fbdiv: 220, postdiv1: 5, postdiv2: 1, min diff value: 0.000000
I (1651) bm1366Module: Setting Frequency to 550.00MHz (0.01)
I (1651) bm1366Module: Setting max baud of 1000000 
I (1661) serial: Changing UART baud to 1000000
I (1661) test_bm1366: BM1366 is ready and waiting for work
I (1671) test_bm1366: Preparing job
I (1671) bm1366Module: Setting job ASIC mask to 1023 (3ff)
I (1681) test_bm1366: Changing chip address and sending job; new chip address: 0x00
I (1691) test_bm1366: Waiting for result ... (might take a while)
I (2281) test_bm1366: Result[1]: Nonce 3356630138 Nonce difficulty 1026.29000767828665630077011883258820. rolled-version 0x2007c000
I (6401) test_bm1366: Result[2]: Nonce 4098331810 Nonce difficulty 1064.96651917922304164676461368799210. rolled-version 0x20386000
I (18171) test_bm1366: Result[3]: Nonce 730428121 Nonce difficulty 12925.98079703762959979940205812454224. rolled-version 0x20c40000
I (25471) test_bm1366: Result[4]: Nonce 2054183361 Nonce difficulty 1083.48521959102208711556158959865570. rolled-version 0x211b6000
I (32101) test_bm1366: Result[5]: Nonce 4220411461 Nonce difficulty 1352.93364926346794163691811263561249. rolled-version 0x216aa000
I (33841) test_bm1366: Result[6]: Nonce 1738592294 Nonce difficulty 3253.28003757193982892204076051712036. rolled-version 0x217f8000
I (44821) test_bm1366: Result[7]: Nonce 3296296050 Nonce difficulty 1453.17780613829404501302633434534073. rolled-version 0x2202c000
I (57001) test_bm1366: Result[8]: Nonce 2916474458 Nonce difficulty 2900.01401468868380106869153678417206. rolled-version 0x22932000
I (65581) test_bm1366: Result[9]: Nonce 728484779 Nonce difficulty 73303.47024935472290962934494018554688. rolled-version 0x22f9e000
I (72761) test_bm1366: Result[10]: Nonce 3543509168 Nonce difficulty 2768.57575025543292213114909827709198. rolled-version 0x234f4000
I (74531) test_bm1366: Result[11]: Nonce 3733637076 Nonce difficulty 5323.27495962955345021327957510948181. rolled-version 0x23640000
I (77281) test_bm1366: Result[12]: Nonce 3314032302 Nonce difficulty 6208.96365635305573960067704319953918. rolled-version 0x2385a000
I (85471) test_bm1366: Result[13]: Nonce 624424727 Nonce difficulty 1174.62942058242470011464320123195648. rolled-version 0x23e66000
I (89321) test_bm1366: Result[14]: Nonce 3818226259 Nonce difficulty 8452.86377870396427169907838106155396. rolled-version 0x24148000
I (107401) test_bm1366: Result[15]: Nonce 1379217352 Nonce difficulty 1947.37949368304271047236397862434387. rolled-version 0x24ece000
I (122361) test_bm1366: Result[16]: Nonce 435963153 Nonce difficulty 3911.03653636329499931889586150646210. rolled-version 0x259ec000
I (176881) test_bm1366: Result[17]: Nonce 3021266242 Nonce difficulty 2761.89034417103221130673773586750031. rolled-version 0x2828c000
I (185631) test_bm1366: Result[18]: Nonce 3850541471 Nonce difficulty 14370.11093116940901381894946098327637. rolled-version 0x28902000
I (209701) test_bm1366: Result[19]: Nonce 886605891 Nonce difficulty 1194.31917192739751953922677785158157. rolled-version 0x29afa000
I (215751) test_bm1366: Result[20]: Nonce 2161230739 Nonce difficulty 1958.41612947111821085854899138212204. rolled-version 0x29f72000
I (215911) test_bm1366: Result[21]: Nonce 2896796331 Nonce difficulty 6206.93857926386044709943234920501709. rolled-version 0x29f98000
I (223941) test_bm1366: Result[22]: Nonce 3310734796 Nonce difficulty 22439.06738404306452139280736446380615. rolled-version 0x2a59e000
I (229081) test_bm1366: Result[23]: Nonce 3529540887 Nonce difficulty 125538251293054.07812500000000000000000000000000. rolled-version 0x2a966000
I (254881) test_bm1366: Result[24]: Nonce 3979369686 Nonce difficulty 1065.74329468743121651641558855772018. rolled-version 0x2bca0000
I (270031) test_bm1366: Result[25]: Nonce 2367093861 Nonce difficulty 1053.33980769035611047002021223306656. rolled-version 0x2c7e0000
I (279641) test_bm1366: Result[26]: Nonce 1466870368 Nonce difficulty 1202.53008809878724605368915945291519. rolled-version 0x2cf18000
I (280841) test_bm1366: Result[27]: Nonce 3095815785 Nonce difficulty 1113.14920939102808006282430142164230. rolled-version 0x2cff6000
I (290151) test_bm1366: Result[28]: Nonce 3515377569 Nonce difficulty 3075.84001209167627166607417166233063. rolled-version 0x2d6e8000
I (293151) test_bm1366: Result[29]: Nonce 753393608 Nonce difficulty 4753.95315653250781906535848975181580. rolled-version 0x2d920000
I (293941) test_bm1366: Result[30]: Nonce 2554068531 Nonce difficulty 18653.14885606238385662436485290527344. rolled-version 0x2d9ba000
I (312051) test_bm1366: Result[31]: Nonce 4214192723 Nonce difficulty 1077.07178599741473590256646275520325. rolled-version 0x2e73e000
I (316051) test_bm1366: Result[32]: Nonce 4260924074 Nonce difficulty 1171.41560793723556344048120081424713. rolled-version 0x2ea3a000
I (318831) test_bm1366: Result[33]: Nonce 1412305839 Nonce difficulty 1199.63505616408269816020037978887558. rolled-version 0x2ec44000
I (335921) test_bm1366: Result[34]: Nonce 2446869902 Nonce difficulty 5151.08160455553479550871998071670532. rolled-version 0x2f900000
I (347421) test_bm1366: Result[35]: Nonce 3996152402 Nonce difficulty 1711.36246177649127275799401104450226. rolled-version 0x30194000
I (361861) test_bm1366: Result[36]: Nonce 1403708462 Nonce difficulty 1686.77668423937393527012318372726440. rolled-version 0x30c52000
I (371931) test_bm1366: Result[37]: Nonce 4292405564 Nonce difficulty 4826.03334644024380395421758294105530. rolled-version 0x313da000
I (374251) test_bm1366: Result[38]: Nonce 4113567568 Nonce difficulty 9897.91747666776609548833221197128296. rolled-version 0x31592000
I (391531) test_bm1366: Result[39]: Nonce 1276381192 Nonce difficulty 1256.61434292565650139295030385255814. rolled-version 0x3227a000
I (398331) test_bm1366: Result[40]: Nonce 3030061972 Nonce difficulty 1909.77368000968203887168783694505692. rolled-version 0x3278c000
I (404641) test_bm1366: Result[41]: Nonce 532194200 Nonce difficulty 1766.84642728682615597790572792291641. rolled-version 0x32c3a000
I (416871) test_bm1366: Result[42]: Nonce 2856921458 Nonce difficulty 4395.74669893087684613419696688652039. rolled-version 0x3355e000
I (417171) test_bm1366: Result[43]: Nonce 2625422405 Nonce difficulty 3364.87174582585703319637104868888855. rolled-version 0x33586000
I (421321) test_bm1366: Result[44]: Nonce 1340820186 Nonce difficulty 1561.98338810546511012944392859935760. rolled-version 0x338ac000
I (434581) test_bm1366: Result[45]: Nonce 3925501370 Nonce difficulty 2798.92112900040274325874634087085724. rolled-version 0x34286000
I (442251) test_bm1366: Result[46]: Nonce 2612621415 Nonce difficulty 41195.99239840431255288422107696533203. rolled-version 0x3483e000
I (460701) test_bm1366: Result[47]: Nonce 3490792207 Nonce difficulty 1454.04923850163299903215374797582626. rolled-version 0x355f4000
I (469731) test_bm1366: Result[48]: Nonce 3804451920 Nonce difficulty 5845.79301263196884974604472517967224. rolled-version 0x35cbe000
I (522091) test_bm1366: Result[49]: Nonce 2276386072 Nonce difficulty 1804.72462226439961341384332627058029. rolled-version 0x383bc000
I (564551) test_bm1366: Result[50]: Nonce 2129142167 Nonce difficulty 2050.76354358329308524844236671924591. rolled-version 0x3a35a000
I (588381) test_bm1366: Result[51]: Nonce 3792324699 Nonce difficulty 1050.60596683861763267486821860074997. rolled-version 0x3b51e000
I (589701) test_bm1366: Result[52]: Nonce 3616117198 Nonce difficulty 1780.86896359463571570813655853271484. rolled-version 0x3b61a000
I (595321) test_bm1366: Result[53]: Nonce 2318185730 Nonce difficulty 1411.90923138176458451198413968086243. rolled-version 0x3ba4c000
I (637431) test_bm1366: Result[54]: Nonce 779646338 Nonce difficulty 1309.10155970781420364801306277513504. rolled-version 0x3d9a0000
I (648341) test_bm1366: Result[55]: Nonce 106727592 Nonce difficulty 1900.49249539394349994836375117301941. rolled-version 0x3e1c4000
I (670081) test_bm1366: Result[56]: Nonce 3485472715 Nonce difficulty 1212.32286936800187504559289664030075. rolled-version 0x3f1f0000
I (677381) test_bm1366: Result[57]: Nonce 1397762629 Nonce difficulty 1877.09231490095703520637471228837967. rolled-version 0x3f764000
I (689521) test_bm1366: Result[58]: Nonce 3356630138 Nonce difficulty 1026.29000767828665630077011883258820. rolled-version 0x2007c000
I (693641) test_bm1366: Result[59]: Nonce 4098331810 Nonce difficulty 1064.96651917922304164676461368799210. rolled-version 0x20386000
I (705411) test_bm1366: Result[60]: Nonce 730428121 Nonce difficulty 12925.98079703762959979940205812454224. rolled-version 0x20c40000
I (712711) test_bm1366: Changing chip address and sending job; new chip address: 0x80
I (712711) test_bm1366: Waiting for result ... (might take a while)
I (713331) test_bm1366: Result[1]: Nonce 3356630138 Nonce difficulty 1026.29000767828665630077011883258820. rolled-version 0x2007c000
I (717461) test_bm1366: Result[2]: Nonce 4098331810 Nonce difficulty 1064.96651917922304164676461368799210. rolled-version 0x20386000
I (729171) test_bm1366: Result[3]: Nonce 730428121 Nonce difficulty 12925.98079703762959979940205812454224. rolled-version 0x20c40000
I (736461) test_bm1366: Result[4]: Nonce 2054183361 Nonce difficulty 1083.48521959102208711556158959865570. rolled-version 0x211b6000
I (743091) test_bm1366: Result[5]: Nonce 4220411461 Nonce difficulty 1352.93364926346794163691811263561249. rolled-version 0x216aa000
I (744901) test_bm1366: Result[6]: Nonce 1738592294 Nonce difficulty 3253.28003757193982892204076051712036. rolled-version 0x217f8000
I (755881) test_bm1366: Result[7]: Nonce 3296296050 Nonce difficulty 1453.17780613829404501302633434534073. rolled-version 0x2202c000
I (768051) test_bm1366: Result[8]: Nonce 2916474458 Nonce difficulty 2900.01401468868380106869153678417206. rolled-version 0x22932000
I (776581) test_bm1366: Result[9]: Nonce 728484779 Nonce difficulty 73303.47024935472290962934494018554688. rolled-version 0x22f9e000
I (783821) test_bm1366: Result[10]: Nonce 3543509168 Nonce difficulty 2768.57575025543292213114909827709198. rolled-version 0x234f4000
I (785581) test_bm1366: Result[11]: Nonce 3733637076 Nonce difficulty 5323.27495962955345021327957510948181. rolled-version 0x23640000
I (788331) test_bm1366: Result[12]: Nonce 3314032302 Nonce difficulty 6208.96365635305573960067704319953918. rolled-version 0x2385a000
I (796461) test_bm1366: Result[13]: Nonce 624424727 Nonce difficulty 1174.62942058242470011464320123195648. rolled-version 0x23e66000
I (800311) test_bm1366: Result[14]: Nonce 3818226259 Nonce difficulty 8452.86377870396427169907838106155396. rolled-version 0x24148000
I (818451) test_bm1366: Result[15]: Nonce 1379217352 Nonce difficulty 1947.37949368304271047236397862434387. rolled-version 0x24ece000
I (833351) test_bm1366: Result[16]: Nonce 435963153 Nonce difficulty 3911.03653636329499931889586150646210. rolled-version 0x259ec000
I (887931) test_bm1366: Result[17]: Nonce 3021266242 Nonce difficulty 2761.89034417103221130673773586750031. rolled-version 0x2828c000
I (896621) test_bm1366: Result[18]: Nonce 3850541471 Nonce difficulty 14370.11093116940901381894946098327637. rolled-version 0x28902000
I (920691) test_bm1366: Result[19]: Nonce 886605891 Nonce difficulty 1194.31917192739751953922677785158157. rolled-version 0x29afa000
I (926741) test_bm1366: Result[20]: Nonce 2161230739 Nonce difficulty 1958.41612947111821085854899138212204. rolled-version 0x29f72000
I (926901) test_bm1366: Result[21]: Nonce 2896796331 Nonce difficulty 6206.93857926386044709943234920501709. rolled-version 0x29f98000
I (934991) test_bm1366: Result[22]: Nonce 3310734796 Nonce difficulty 22439.06738404306452139280736446380615. rolled-version 0x2a59e000
I (940071) test_bm1366: Result[23]: Nonce 3529540887 Nonce difficulty 125538251293054.07812500000000000000000000000000. rolled-version 0x2a966000
I (965941) test_bm1366: Result[24]: Nonce 3979369686 Nonce difficulty 1065.74329468743121651641558855772018. rolled-version 0x2bca0000
I (981031) test_bm1366: Result[25]: Nonce 2367093861 Nonce difficulty 1053.33980769035611047002021223306656. rolled-version 0x2c7e0000
I (990691) test_bm1366: Result[26]: Nonce 1466870368 Nonce difficulty 1202.53008809878724605368915945291519. rolled-version 0x2cf18000
I (991831) test_bm1366: Result[27]: Nonce 3095815785 Nonce difficulty 1113.14920939102808006282430142164230. rolled-version 0x2cff6000
I (1001141) test_bm1366: Result[28]: Nonce 3515377569 Nonce difficulty 3075.84001209167627166607417166233063. rolled-version 0x2d6e8000
I (1004211) test_bm1366: Result[29]: Nonce 753393608 Nonce difficulty 4753.95315653250781906535848975181580. rolled-version 0x2d920000
I (1004931) test_bm1366: Result[30]: Nonce 2554068531 Nonce difficulty 18653.14885606238385662436485290527344. rolled-version 0x2d9ba000
I (1023041) test_bm1366: Result[31]: Nonce 4214192723 Nonce difficulty 1077.07178599741473590256646275520325. rolled-version 0x2e73e000
I (1027101) test_bm1366: Result[32]: Nonce 4260924074 Nonce difficulty 1171.41560793723556344048120081424713. rolled-version 0x2ea3a000
I (1029821) test_bm1366: Result[33]: Nonce 1412305839 Nonce difficulty 1199.63505616408269816020037978887558. rolled-version 0x2ec44000
I (1046971) test_bm1366: Result[34]: Nonce 2446869902 Nonce difficulty 5151.08160455553479550871998071670532. rolled-version 0x2f900000
I (1058471) test_bm1366: Result[35]: Nonce 3996152402 Nonce difficulty 1711.36246177649127275799401104450226. rolled-version 0x30194000
I (1072911) test_bm1366: Result[36]: Nonce 1403708462 Nonce difficulty 1686.77668423937393527012318372726440. rolled-version 0x30c52000
I (1082981) test_bm1366: Result[37]: Nonce 4292405564 Nonce difficulty 4826.03334644024380395421758294105530. rolled-version 0x313da000
I (1085301) test_bm1366: Result[38]: Nonce 4113567568 Nonce difficulty 9897.91747666776609548833221197128296. rolled-version 0x31592000
I (1102591) test_bm1366: Result[39]: Nonce 1276381192 Nonce difficulty 1256.61434292565650139295030385255814. rolled-version 0x3227a000
I (1109381) test_bm1366: Result[40]: Nonce 3030061972 Nonce difficulty 1909.77368000968203887168783694505692. rolled-version 0x3278c000
I (1115691) test_bm1366: Result[41]: Nonce 532194200 Nonce difficulty 1766.84642728682615597790572792291641. rolled-version 0x32c3a000
I (1127921) test_bm1366: Result[42]: Nonce 2856921458 Nonce difficulty 4395.74669893087684613419696688652039. rolled-version 0x3355e000
I (1128161) test_bm1366: Result[43]: Nonce 2625422405 Nonce difficulty 3364.87174582585703319637104868888855. rolled-version 0x33586000
I (1132371) test_bm1366: Result[44]: Nonce 1340820186 Nonce difficulty 1561.98338810546511012944392859935760. rolled-version 0x338ac000
I (1145631) test_bm1366: Result[45]: Nonce 3925501370 Nonce difficulty 2798.92112900040274325874634087085724. rolled-version 0x34286000
I (1153241) test_bm1366: Result[46]: Nonce 2612621415 Nonce difficulty 41195.99239840431255288422107696533203. rolled-version 0x3483e000
I (1171691) test_bm1366: Result[47]: Nonce 3490792207 Nonce difficulty 1454.04923850163299903215374797582626. rolled-version 0x355f4000
I (1180781) test_bm1366: Result[48]: Nonce 3804451920 Nonce difficulty 5845.79301263196884974604472517967224. rolled-version 0x35cbe000
I (1233151) test_bm1366: Result[49]: Nonce 2276386072 Nonce difficulty 1804.72462226439961341384332627058029. rolled-version 0x383bc000
I (1275541) test_bm1366: Result[50]: Nonce 2129142167 Nonce difficulty 2050.76354358329308524844236671924591. rolled-version 0x3a35a000
I (1299371) test_bm1366: Result[51]: Nonce 3792324699 Nonce difficulty 1050.60596683861763267486821860074997. rolled-version 0x3b51e000
I (1300751) test_bm1366: Result[52]: Nonce 3616117198 Nonce difficulty 1780.86896359463571570813655853271484. rolled-version 0x3b61a000
I (1306381) test_bm1366: Result[53]: Nonce 2318185730 Nonce difficulty 1411.90923138176458451198413968086243. rolled-version 0x3ba4c000
I (1348481) test_bm1366: Result[54]: Nonce 779646338 Nonce difficulty 1309.10155970781420364801306277513504. rolled-version 0x3d9a0000
I (1359391) test_bm1366: Result[55]: Nonce 106727592 Nonce difficulty 1900.49249539394349994836375117301941. rolled-version 0x3e1c4000
I (1381081) test_bm1366: Result[56]: Nonce 3485472715 Nonce difficulty 1212.32286936800187504559289664030075. rolled-version 0x3f1f0000
I (1388381) test_bm1366: Result[57]: Nonce 1397762629 Nonce difficulty 1877.09231490095703520637471228837967. rolled-version 0x3f764000
I (1400571) test_bm1366: Result[58]: Nonce 3356630138 Nonce difficulty 1026.29000767828665630077011883258820. rolled-version 0x2007c000
I (1404691) test_bm1366: Result[59]: Nonce 4098331810 Nonce difficulty 1064.96651917922304164676461368799210. rolled-version 0x20386000
I (1416411) test_bm1366: Result[60]: Nonce 730428121 Nonce difficulty 12925.98079703762959979940205812454224. rolled-version 0x20c40000
/workspaces/components/bm1397/test/test_bm1366.c:217:Testing single BM1366 chip against a known valid block:FAIL: Expected 3529540887 Was 2054183361. Function [bm1366]
Running Check coinbase tx construction...
/workspaces/components/stratum/test/test_mining.c:7:Check coinbase tx construction:PASS
Running Validate merkle root calculation...
/workspaces/components/stratum/test/test_mining.c:19:Validate merkle root calculation:PASS
Running Validate another merkle root calculation...
/workspaces/components/stratum/test/test_mining.c:43:Validate another merkle root calculation:PASS
Running Validate bm job construction...
/workspaces/components/stratum/test/test_mining.c:61:Validate bm job construction:PASS
Running Validate version mask incrementing...
/workspaces/components/stratum/test/test_mining.c:78:Validate version mask incrementing:PASS
Running Test extranonce 2 generation...
/workspaces/components/stratum/test/test_mining.c:118:Test extranonce 2 generation:PASS
Running Test nonce diff checking...
/workspaces/components/stratum/test/test_mining.c:153:Test nonce diff checking:FAIL: Expected 18 Was 0. Function [mining test_nonce]
Running Test nonce diff checking 2...
/workspaces/components/stratum/test/test_mining.c:189:Test nonce diff checking 2:FAIL: Expected 683 Was 0. Function [mining test_nonce]
Running Parse stratum method...
/workspaces/components/stratum/test/test_stratum_json.c:4:Parse stratum method:PASS
Running Parse stratum mining.notify abandon work...
/workspaces/components/stratum/test/test_stratum_json.c:21:Parse stratum mining.notify abandon work:PASS
Running Parse stratum set_difficulty params...
/workspaces/components/stratum/test/test_stratum_json.c:62:Parse stratum set_difficulty params:PASS
Running Parse stratum notify params...
/workspaces/components/stratum/test/test_stratum_json.c:71:Parse stratum notify params:PASS
Running Parse stratum mining.set_version_mask params...
/workspaces/components/stratum/test/test_stratum_json.c:108:Parse stratum mining.set_version_mask params:PASS
Running Parse stratum result success...
/workspaces/components/stratum/test/test_stratum_json.c:118:Parse stratum result success:PASS
Running Parse stratum result error...
/workspaces/components/stratum/test/test_stratum_json.c:128:Parse stratum result error:PASS
Running Test double sha...
/workspaces/components/stratum/test/test_utils.c:5:Test double sha:PASS
Running Test hex2bin...
/workspaces/components/stratum/test/test_utils.c:12:Test hex2bin:PASS
Running Test bin2hex...
/workspaces/components/stratum/test/test_utils.c:25:Test bin2hex:PASS
Running Test hex2char...
/workspaces/components/stratum/test/test_utils.c:33:Test hex2char:PASS

-----------------------
20 Tests 3 Failures 0 Ignored 
FAIL

#### Starting interactive test menu #####



Press ENTER to see the list of tests.
