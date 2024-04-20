export IDF_PATH=/opt/esp/idf
/opt/esp/python_env/idf5.3_py3.10_env/bin/python /opt/esp/idf/tools/idf_monitor.py -p /dev/ttyACM0 -b 115200 --toolchain-prefix xtensa-esp32s3-elf- --target esp32s3 /workspaces/build/esp-miner.elf
root@31cc35ad06b6:/workspaces# export IDF_PATH=/opt/esp/idf
root@31cc35ad06b6:/workspaces# /opt/esp/python_env/idf5.3_py3.10_env/bin/python /opt/esp/idf/tools/idf_monitor.py -p /dev/ttyACM0 -b 115200 --toolchain-prefix xtensa-esp32s3-elf- --target esp32s3 /workspaces/build/esp-miner.elf
--- esp-idf-monitor 1.4.0 on /dev/ttyACM0 115200 ---
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
I (115) esp_image: segment 1: paddr=00023ea4 vaddr=3fc93cESP-ROM:esp32s3-20210327
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
I (27) boot: compile time Apr 18 2024 07:48:00
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
I (92) esp_image: segment 0: paddr=00010020 vaddr=3c040020 size=13e7ch ( 81532) map
I (115) esp_image: segment 1: paddr=00023ea4 vaddr=3fc93c00 size=03228h ( 12840) load
I (119) esp_image: segment 2: paddr=000270d4 vaddr=40374000 size=08f44h ( 36676) load
I (129) esp_image: segment 3: paddr=00030020 vaddr=42000020 size=32cdch (208092) map
I (167) esp_image: segment 4: paddr=00062d04 vaddr=4037cf44 size=06c74h ( 27764) load
I (180) boot: Loaded app from partition at offset 0x10000
I (180) boot: Disabling RNG early entropy source...
I (192) cpu_start: Multicore app
I (202) cpu_start: Pro cpu start user code
I (202) cpu_start: cpu freq: 160000000 Hz
I (202) app_init: Application information:
I (205) app_init: Project name:     unit_test_stratum
I (210) app_init: App version:      89d72fe
I (215) app_init: Compile time:     Apr 19 2024 18:33:53
I (221) app_init: ELF file SHA256:  ae2603086...
Warning: checksum mismatch between flashed and built applications. Checksum of built application is 086605b5eb05fdc11580ba1205aaf07638fc4770c2c2403be9a63325fe8b9036
I (226) app_init: ESP-IDF:          v5.3-dev-3225-g5a40bb8746
I (233) efuse_init: Min chip rev:     v0.0
I (238) efuse_init: Max chip rev:     v0.99 
I (243) efuse_init: Chip rev:         v0.2
I (247) heap_init: Initializing. RAM available for dynamic allocation:
I (255) heap_init: At 3FC98C00 len 00050B10 (322 KiB): RAM
I (261) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (267) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (273) heap_init: At 600FE100 len 00001EE8 (7 KiB): RTCRAM
I (280) spi_flash: detected chip: gd
I (283) spi_flash: flash io: dio
W (287) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (301) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
W (312) ADC: legacy driver is deprecated, please migrate to `esp_adc/adc_oneshot.h`
I (320) sleep: Configure to isolate all GPIO pins in sleep state
I (327) sleep: Enable automatic switching of GPIO sleep configuration
I (334) main_task: Started on CPU0
I (344) main_task: Calling app_main()

#### Running all the registered tests #####

Running Testing chip against known valid block...
I (384) test_bm1366: ASIC: BM1366
I (394) test_bm1366: I2C initialized successfully
I (394) DS4432U.c: Set ASIC voltage = 1.200V [0xC6]
I (394) DS4432U.c: Writing 0xC6
I (394) serial: Initializing serial
I (404) bm1366Module: Initializing BM1366
I (1604) bm1366Module: 1 chip(s) detected on the chain
final refdiv: 2, fbdiv: 233, postdiv1: 6, postdiv2: 1, min diff value: 0.416656
I (1634) bm1366Module: Setting Frequency to 485.00MHz (0.01)
I (1634) bm1366Module: Setting max baud of 1000000 
I (1644) serial: Changing UART baud to 1000000
I (1644) test_bm1366: BM1366 is ready and waiting for work
I (1654) test_bm1366: Preparing job
I (1654) test_bm1366: job.prev_block_hash:
I (1664) test_bm1366: a3 9b 43 10 86 39 47 ef d2 82 b3 0f f7 55 d3 ab 
I (1664) test_bm1366: 24 7c 76 ee 7e 5d 01 00 00 00 00 00 00 00 00 00 
I (1674) test_bm1366: job.prev_block_hash_be:
I (1684) test_bm1366: 00 00 00 00 00 00 00 00 7e 5d 01 00 24 7c 76 ee 
I (1684) test_bm1366: f7 55 d3 ab d2 82 b3 0f 86 39 47 ef a3 9b 43 10 
I (1694) test_bm1366: job.merkle_root:
I (1694) test_bm1366: 08 80 83 f5 8d de f9 95 49 4f ec 49 28 80 da 49 
I (1704) test_bm1366: e3 46 3c c7 3d ee 13 06 db df 6c f3 af 77 45 4c 
I (1714) test_bm1366: job.merkle_root_be:
I (1714) test_bm1366: af 77 45 4c db df 6c f3 3d ee 13 06 e3 46 3c c7 
I (1724) test_bm1366: 28 80 da 49 49 4f ec 49 8d de f9 95 08 80 83 f5 
I (1734) bm1366Module: Setting job ASIC mask to 63
I (1734) test_bm1366: Sending job to chip

->[
55 AA 
21 
56 
08 / jobid
01 // num_midstates
00 00 00 00 // start nonce
19 42 03 17 // nbits/target
DF 1B 22 66 // ntime
AF 77 45 4C DB DF 6C F3 3D EE 13 06 E3 46 3C C7 28 80 DA 49 49 4F EC 49 8D DE F9 95 08 80 83 F5 // merkle_root
char * merkle_root = "088083f58ddef995494fec492880da49e3463cc73dee1306dbdf6cf3af77454c";
00 00 00 00 00 00 00 00 7E 5D 01 00 24 7C 76 EE F7 55 D3 AB D2 82 B3 0F 86 39 47 EF A3 9B 43 10 // prev_block_hash
prev_block_hash = "10439ba3ef4739860fb382d2abd355f7ee767c2400015d7e0000000000000000";
00 00 00 20 Version
F7 8C // crc16
]

I (1764) test_bm1366: Waiting for result ...
I (1884) test_bm1366: Result[1]: Nonce 3683778574 Nonce difficulty 77.80559018728487785665492992848158. rolled-version 0x2105c000
I (2834) test_bm1366: Result[2]: Nonce 254804438 Nonce difficulty 102.03668801363397733439342118799686. rolled-version 0x29884000
I (3194) test_bm1366: Result[3]: Nonce 1954087058 Nonce difficulty 84.09947046618982824384147534146905. rolled-version 0x2cc3a000
I (3724) test_bm1366: Result[4]: Nonce 2939289980 Nonce difficulty 120.52920409865235740198841085657477. rolled-version 0x316e0000
I (4324) test_bm1366: Result[5]: Nonce 3994485370 Nonce difficulty 65.54892924781397312017361400648952. rolled-version 0x36ce0000
I (4574) test_bm1366: Result[6]: Nonce 623509588 Nonce difficulty 124.32217134378581135933927726000547. rolled-version 0x3918c000
I (4894) test_bm1366: Result[7]: Nonce 2633826420 Nonce difficulty 84.16303251343467195511038880795240. rolled-version 0x3be6a000
I (4924) test_bm1366: Result[8]: Nonce 1319240078 Nonce difficulty 65.32339276107013859018479706719518. rolled-version 0x3c232000
I (5464) test_bm1366: Result[9]: Nonce 3683778574 Nonce difficulty 77.80559018728487785665492992848158. rolled-version 0x2105c000
I (6424) test_bm1366: Result[10]: Nonce 254804438 Nonce difficulty 102.03668801363397733439342118799686. rolled-version 0x29884000
/workspaces/components/bm1397/test/test_bm1366.c:191:Testing chip against known valid block:FAIL: Expected 3529540887 Was 1954087058. Function [bm1366]
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
