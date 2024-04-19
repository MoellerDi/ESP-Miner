#include "unity.h"
#include "serial.h"
#include "bm1366.h"
#include "common.h"
#include "DS4432U.h"
#include "EMC2101.h"
#include "INA260.h"
#include "adc.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "global_state.h"
#include "nvs_config.h"
#include "nvs_flash.h"
#include "oled.h"
#include "utils.h"

#include <string.h>

static GlobalState GLOBAL_STATE = {.extranonce_str = NULL, .extranonce_2_len = 0, .abandon_work = 0, .version_mask = 0};

static const char * TAG = "unit_test";

TEST_CASE("Check known working", "[bm1366]")
{
    ESP_ERROR_CHECK(nvs_flash_init());

    GLOBAL_STATE.POWER_MANAGEMENT_MODULE.frequency_value = 525; //nvs_config_get_u16(NVS_CONFIG_ASIC_FREQ, 550);
    ESP_LOGI(TAG, "NVS_CONFIG_ASIC_FREQ %f", GLOBAL_STATE.POWER_MANAGEMENT_MODULE.frequency_value);
    //TEST_ASSERT_EQUAL_INT16(550, GLOBAL_STATE.POWER_MANAGEMENT_MODULE.frequency_value);

    GLOBAL_STATE.asic_model = nvs_config_get_string(NVS_CONFIG_ASIC_MODEL, "");
    ESP_LOGI(TAG, "ASIC: %s", GLOBAL_STATE.asic_model);
    TEST_ASSERT_EQUAL_STRING("BM1366", GLOBAL_STATE.asic_model);

    if (strcmp(GLOBAL_STATE.asic_model, "BM1366") == 0) {
        ESP_LOGI(TAG, "ASIC: BM1366");
        AsicFunctions ASIC_functions = {.init_fn = BM1366_init,
                                        .receive_result_fn = BM1366_proccess_work,
                                        .set_max_baud_fn = BM1366_set_max_baud,
                                        .set_difficulty_mask_fn = BM1366_set_job_difficulty_mask,
                                        .send_work_fn = BM1366_send_work};
        uint64_t bm1366_hashrate = GLOBAL_STATE.POWER_MANAGEMENT_MODULE.frequency_value * BM1366_CORE_COUNT * 1000000;
        GLOBAL_STATE.asic_job_frequency_ms = ((double) SPACE_TO_BE_CALCULATED / (double) bm1366_hashrate) * 1000;

        GLOBAL_STATE.ASIC_functions = ASIC_functions;
    } else if (strcmp(GLOBAL_STATE.asic_model, "BM1368") == 0) {
        ESP_LOGI(TAG, "ASIC: BM1368");
        AsicFunctions ASIC_functions = {.init_fn = BM1368_init,
                                        .receive_result_fn = BM1368_proccess_work,
                                        .set_max_baud_fn = BM1368_set_max_baud,
                                        .set_difficulty_mask_fn = BM1368_set_job_difficulty_mask,
                                        .send_work_fn = BM1368_send_work};

        uint64_t bm1368_hashrate = GLOBAL_STATE.POWER_MANAGEMENT_MODULE.frequency_value * BM1368_CORE_COUNT * 1000000;
        GLOBAL_STATE.asic_job_frequency_ms = ((double) NONCE_SPACE / (double) bm1368_hashrate) * 1000;

        GLOBAL_STATE.ASIC_functions = ASIC_functions;
    } else if (strcmp(GLOBAL_STATE.asic_model, "BM1397") == 0) {
        ESP_LOGI(TAG, "ASIC: BM1397");
        AsicFunctions ASIC_functions = {.init_fn = BM1397_init,
                                        .receive_result_fn = BM1397_proccess_work,
                                        .set_max_baud_fn = BM1397_set_max_baud,
                                        .set_difficulty_mask_fn = BM1397_set_job_difficulty_mask,
                                        .send_work_fn = BM1397_send_work};

        uint64_t bm1397_hashrate = GLOBAL_STATE.POWER_MANAGEMENT_MODULE.frequency_value * BM1397_CORE_COUNT * 1000000;
        GLOBAL_STATE.asic_job_frequency_ms = ((double) NONCE_SPACE / (double) bm1397_hashrate) * 1000;

        GLOBAL_STATE.ASIC_functions = ASIC_functions;
    } else {
        ESP_LOGI(TAG, "Invalid ASIC model");
        AsicFunctions ASIC_functions = {.init_fn = NULL,
                                        .receive_result_fn = NULL,
                                        .set_max_baud_fn = NULL,
                                        .set_difficulty_mask_fn = NULL,
                                        .send_work_fn = NULL};
        GLOBAL_STATE.ASIC_functions = ASIC_functions;
    }

    GLOBAL_STATE.ASIC_TASK_MODULE.active_jobs = malloc(sizeof(bm_job *) * 128);
    GLOBAL_STATE.valid_jobs = malloc(sizeof(uint8_t) * 128);

    for (int i = 0; i < 128; i++) {

        GLOBAL_STATE.ASIC_TASK_MODULE.active_jobs[i] = NULL;
        GLOBAL_STATE.valid_jobs[i] = 0;
    }

    // Init I2C
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");

    ADC_init();
    DS4432U_set_vcore(1.200000); //nvs_config_get_u16(NVS_CONFIG_ASIC_VOLTAGE, 1200) / 1000.0);
    ESP_LOGI(TAG, "DS4432U_set_vcore %f", nvs_config_get_u16(NVS_CONFIG_ASIC_VOLTAGE, 1200) / 1000.0);

    EMC2101_init(nvs_config_get_u16(NVS_CONFIG_INVERT_FAN_POLARITY, 1));
    EMC2101_set_fan_speed(1);

    // turn ASIC on
    gpio_set_direction(GPIO_NUM_10, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_10, 0);

    SERIAL_init();

    uint8_t chips_detected = (*GLOBAL_STATE.ASIC_functions.init_fn)(GLOBAL_STATE.POWER_MANAGEMENT_MODULE.frequency_value);
    TEST_ASSERT_EQUAL_INT8(1, chips_detected);
    ESP_LOGI(TAG, "%u chips detected", chips_detected);

    SERIAL_set_baud((*GLOBAL_STATE.ASIC_functions.set_max_baud_fn)());


/* Block #839900
    {"id":null,"method":"mining.notify","params":[
        "185abf4", //job_id
        "10439ba3ef4739860fb382d2abd355f7ee767c2400015d7e0000000000000000", //prev_block_hash
        "02000000010000000000000000000000000000000000000000000000000000000000000000ffffffff1703dcd00c5075626c69632d506f6f6c", //coinbase_1
        "ffffffff025ef88d2700000000160014979f36b9a92622b82767820f6477bdefc03e86b70000000000000000266a24aa21a9ed4b7e3a6c3bf8bff6e793b507392ae3cb0deab4c8908ce351e61d0af0ac06bdc000000000", //coinbase_2
        [
            "7e3f8209b0d3e7fcfaf4c89162636bc1756d2bc3bfcdc7a7135136ff6d7b0069",
            "e66c3e07dee92d95bb4895580fb3584f2fe1d29033818846286e23cddf9bf572",
            "5a9ff7e4b64934437af73e3fa4e5a783d9b1421de19a605b8e30edfce5d055a5",
            "d3d38299563f8a6cac7821096c6e9f8fbbe77bd063adb0687035f5cde2ff4dd0",
            "72dca2b4288e4288d1c9b79df8b88b0a24e3f85e901e99eeb62014288651ef26",
            "b417f18e7774cb36e5009f239fe08c1407dde49a7b19cf4230b67de9a348b502",
            "01261cd686cde5b97cf989953b0a0e1630c016f187a6f6e7fc44b40c950d3571",
            "6076764edef31739c715acfe5d2a480624779998987d60520033b731da129f37",
            "a953f2b682496e2777938d01f7a6626435406236d8caa64fb8a7f2a9bd05e6ff",
            "479e0549bd963a3d7f6747bdd3f615fced29a003d959d4c740c29a49943d16cf",
            "a1714ab576e5228e10ee4b6aa032412e9c20015b52a4516842358fb28cef3c7e",
            "fcb3c52ae1f391246b6250c178040d6b7fa9725391a65315e6e9dc0c1e32e336"
        ],
        "20000000", //version
        "17034219", //target
        "66221ad7", //ntime
        false] //clear_jobs
    }
*/

    bool rev_prev_block_hash          = 1;
    bool swap_endian_prev_block_hask  = 1;
    bool rev_merkle_root_hash         = 1;
    bool swap_endian_merkle_root_hash = 0;

    uint8_t buff;
    size_t boffset, bword, bsize;

    uint8_t prev_block_hash[32];
    hex2bin("000000000000000000015d7eee767c24abd355f70fb382d2ef47398610439ba3", prev_block_hash, 32);
    if (rev_prev_block_hash) {reverse_bytes(prev_block_hash, 32);}
    if (swap_endian_prev_block_hask) {
        // reverse (4-byte word swap)
        boffset = 0;
        bword = 4;
        bsize = 32;
        for (size_t i = 1; i <= bsize / bword; i++) {
            for (size_t j = boffset; j < boffset + bword / 2; j++) {
                buff = prev_block_hash[j];
                prev_block_hash[j] = prev_block_hash[2 * boffset + bword - 1 - j];
                prev_block_hash[2 * boffset + bword - 1 - j] = buff;
            }
            boffset += bword;
        }
    }
    
    char * prev_block_hash_rev = malloc(65);
    memset(prev_block_hash_rev, '0', 64);
    bin2hex(prev_block_hash, 32, prev_block_hash_rev, 64);
    ESP_LOGI(TAG, "prev_block_hash_rev %s", prev_block_hash_rev);

    mining_notify notify_message;
    notify_message.job_id = 0; //Block #839900
    notify_message.prev_block_hash   = prev_block_hash_rev;
    notify_message.version = 0x20000000; //0x20106000;
    notify_message.target = 0x17034219;
    notify_message.ntime = 1713511391;
    notify_message.difficulty = 128;
    notify_message.version_mask = 0x1fffe000;

    uint8_t merkle_root[32];
    hex2bin("088083f58ddef995494fec492880da49e3463cc73dee1306dbdf6cf3af77454c", merkle_root, 32);
    if (rev_merkle_root_hash) {reverse_bytes(merkle_root, 32);}
    if (swap_endian_merkle_root_hash) {
        // reverse (4-byte word swap)
        boffset = 0;
        bword = 4;
        bsize = 32;
        for (size_t i = 1; i <= bsize / bword; i++) {
            for (size_t j = boffset; j < boffset + bword / 2; j++) {
                buff = merkle_root[j];
                merkle_root[j] = merkle_root[2 * boffset + bword - 1 - j];
                merkle_root[2 * boffset + bword - 1 - j] = buff;
            }
            boffset += bword;
        }
    }
    
    char * merkle_root_rev = malloc(65);
    memset(merkle_root_rev, '0', 64);
    bin2hex(merkle_root, 32, merkle_root_rev, 64);
    ESP_LOGI(TAG, "merkle_root_rev %s", merkle_root_rev);

    bm_job job = construct_bm_job(&notify_message, merkle_root_rev, 0);

    ESP_LOGI(TAG, "job.prev_block_hash:");
    ESP_LOG_BUFFER_HEX(TAG,  job.prev_block_hash, 32);
    ESP_LOGI(TAG, "job.prev_block_hash_be:");
    ESP_LOG_BUFFER_HEX(TAG,  job.prev_block_hash_be, 32);
    ESP_LOGI(TAG, "job.merkle_root:");
    ESP_LOG_BUFFER_HEX(TAG,  job.merkle_root, 32);
    ESP_LOGI(TAG, "job.merkle_root_be:");
    ESP_LOG_BUFFER_HEX(TAG,  job.merkle_root_be, 32);

    (*GLOBAL_STATE.ASIC_functions.set_difficulty_mask_fn)(notify_message.difficulty);

    ESP_LOGI(TAG, "Sending work");
    (*GLOBAL_STATE.ASIC_functions.send_work_fn)(&GLOBAL_STATE, &job);

    ESP_LOGI(TAG, "Receiving work");
    task_result * asic_result = (*GLOBAL_STATE.ASIC_functions.receive_result_fn)(&GLOBAL_STATE);
    //TEST_ASSERT_NOT_NULL(asic_result);

    int counter =0;
    while (asic_result != NULL && counter < 10) {
        ESP_LOGI(TAG, "Received work");
    
        // check the nonce difficulty
        double nonce_diff = test_nonce_value(&job, asic_result->nonce, asic_result->rolled_version);
        ESP_LOGI(TAG, "Nonce %lu Nonce difficulty %.32f. rolled-version %08lx", asic_result->nonce, nonce_diff, asic_result->rolled_version);
        //TEST_ASSERT_EQUAL_UINT32(3529540887, asic_result->nonce);

        asic_result = (*GLOBAL_STATE.ASIC_functions.receive_result_fn)(&GLOBAL_STATE);
        counter++;
    }

    

    // memory
    free(GLOBAL_STATE.ASIC_TASK_MODULE.active_jobs);
    free(GLOBAL_STATE.valid_jobs);

    // turn ASIC off
    gpio_set_direction(GPIO_NUM_10, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_10, 1);
}

