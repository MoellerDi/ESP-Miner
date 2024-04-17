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

    GLOBAL_STATE.POWER_MANAGEMENT_MODULE.frequency_value = nvs_config_get_u16(NVS_CONFIG_ASIC_FREQ, 550);
    ESP_LOGI(TAG, "NVS_CONFIG_ASIC_FREQ %f", GLOBAL_STATE.POWER_MANAGEMENT_MODULE.frequency_value);
    TEST_ASSERT_EQUAL_INT16(550, GLOBAL_STATE.POWER_MANAGEMENT_MODULE.frequency_value);

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
    DS4432U_set_vcore(nvs_config_get_u16(NVS_CONFIG_ASIC_VOLTAGE, 1200) / 1000.0);

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

    // uint8_t prev_block_hash[32];
    // hex2bin("00000000000000000000a5f36b312cdf97effc86a0a7b00384bc13a49dd1f07a", prev_block_hash, 32);
    // reverse_bytes(prev_block_hash, 32);
    // char * prev_block_hash_char = malloc(65);
    // bin2hex(prev_block_hash, 32, prev_block_hash_char, 65);
    // ESP_LOGI(TAG, "prev_block_hash %s", prev_block_hash_char);

    mining_notify notify_message;
    notify_message.job_id = 0;
    //notify_message.prev_block_hash   = "0c859545a3498373a57452fac22eb7113df2a465000543520000000000000000";
    notify_message.prev_block_hash   = "00000000000000000000a5f36b312cdf97effc86a0a7b00384bc13a49dd1f07a";
    //notify_message.prev_block_hash   = prev_block_hash_char;
    notify_message.version = 552255488; //0x20eac000; // 0x20000004;
    notify_message.target = 0x17034219; //0x1705ae3a;
    notify_message.ntime = 1713299970; //0x647025b5;
    notify_message.difficulty = 128;
    notify_message.version_mask = 0x1fffe000;

    //reverse_bytes(notify_message.version, 4);
    //reverse_bytes(notify_message.target, 4);
    //reverse_bytes(notify_message.ntime, 4);


    //TEST_ASSERT_EQUAL_STRING("7af0d19da413bc8403b0a7a086fcef97df2c316bf3a500000000000000000000", notify_message.prev_block_hash);

    //char * merkle_root = calculate_merkle_root_hash(coinbase_tx, merkles, num_merkles);

    char * merkle_root = "b5fc93c5ca3cb9dcb2878d485b650ea5a62aa17233d2f44efc56fd92d5e06e64";
    // uint8_t merkle_root[32];
    // hex2bin("b5fc93c5ca3cb9dcb2878d485b650ea5a62aa17233d2f44efc56fd92d5e06e64", merkle_root, 32);
    // reverse_bytes(merkle_root, 32);
    // char * merkle_root_rev = malloc(65);
    // bin2hex(merkle_root, 32, merkle_root_rev, 65);
    // ESP_LOGI(TAG, "merkle_root_rev %s", merkle_root_rev);

    bm_job job = construct_bm_job(&notify_message, merkle_root, notify_message.version_mask);

    //TEST_ASSERT_EQUAL_STRING("00000000000000000000a5f36b312cdf97effc86a0a7b00384bc13a49dd1f07a", job.prev_block_hash);

    (*GLOBAL_STATE.ASIC_functions.set_difficulty_mask_fn)(notify_message.difficulty);

    ESP_LOGI(TAG, "Sending work");
    //BM1366_send_work(GLOBAL_STATE, &job);
    (*GLOBAL_STATE.ASIC_functions.send_work_fn)(&GLOBAL_STATE, &job);

    ESP_LOGI(TAG, "Receiving work");
    task_result * asic_result = (*GLOBAL_STATE.ASIC_functions.receive_result_fn)(&GLOBAL_STATE);
    TEST_ASSERT_NOT_NULL(asic_result);

    if (asic_result != NULL) {
        ESP_LOGI(TAG, "Received work");
    
        // check the nonce difficulty
        double nonce_diff = test_nonce_value(&job, asic_result->nonce, asic_result->rolled_version);
        ESP_LOGI(TAG, "Nonce %lu Nonce difficulty %.32f.", asic_result->nonce, nonce_diff);
    }



    // memory
    free(GLOBAL_STATE.ASIC_TASK_MODULE.active_jobs);
    free(GLOBAL_STATE.valid_jobs);

    // turn ASIC off
    gpio_set_direction(GPIO_NUM_10, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_10, 1);
}