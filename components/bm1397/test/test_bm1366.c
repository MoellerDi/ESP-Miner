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


/* 
//Block #839666
{"id":null,"method":"mining.notify","params":[
    "15937dc", //job_id
    "63461e09e27c1454ba1df8fdcd5f5f201f5ade7e0001cde80000000000000000", //prev_block_hash
    "02000000010000000000000000000000000000000000000000000000000000000000000000ffffffff1703f2cf0c5075626c69632d506f6f6c", //coinbase_1
    "ffffffff0283b14b2d00000000160014979f36b9a92622b82767820f6477bdefc03e86b70000000000000000266a24aa21a9ed43a609abf1b0ae9fb2a92451770c95ad623de1e7801af2f35a998d7fe6cc82ab00000000", //coinbase_2
    [
        "021d20e06085ef4970139c4c3e32336edbc113abcf78b32800c792c80e1fdb6b",
        "f02fcbea9a3408c93385dabd064c3f971355b83ee614a1ffdc843327f8c5abc3",
        "669aacb989a9b0e601a680364c3655b97efd5afb6886f054456e86f13bb5e4cb",
        "99573b894dc4ac6a17d8d8ec3d059dc400ddc3433cfdace2db1d12c8365f1503",
        "6ea792c5f736ac1b3a40b5662791bf6fda42e44693d13bc7f88fc7db649e6184",
        "0364d05a228ff502680fd875246dbf7763b2fd4591dcd2dea4c541f2f2be9a38",
        "2a8998a2178d3761d107b8ac3c04af7c996f6be8be4cd17c245a0a41d47f1cd6",
        "73c2df2610c36fd1249622c0d93d67c7b5027cd013089e0320664ac706175d07",
        "f960c56ac0f7ccefab021c945f444c7648bf1a277ab5b8f1fab524a03cc03f54",
        "1b993d3325bef7e320060c529d60d0c42b07e87f5fcb5bab84c45146239e4d75",
        "139467baf2e565b976528b5102c54faa10d4b9560005afdd7df0def1ce00edc1",
        "c89bd65989a888f1c3f03d189e26892bf62c84e1e6f620294199f5178c53583e",
        "37883d69fbc3f396aacc76287d39e9d70a0859948d17dd9170a8da5aba636178"
    ],
    "20000000", //version
    "17034219", //target
    "66200c3f", //ntime
    false] //clear_jobs
    }
*/

    bool rev_prev_block_hash    = 0;
    bool rev_prev_block_hask_2  = 1;
    bool rev_merkle_root_hash   = 0;
    bool rev_merkle_root_hash_2 = 0;

    uint8_t buff;
    size_t boffset, bword, bsize;

    uint8_t prev_block_hash[32];
    hex2bin("00000000000000000001cde81f5ade7ecd5f5f20ba1df8fde27c145463461e09", prev_block_hash, 32);
    if (rev_prev_block_hash) {reverse_bytes(prev_block_hash, 32);}
    if (rev_prev_block_hask_2) {
        // reverse prev hash (4-byte word swap)
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
    bin2hex(prev_block_hash, 32, prev_block_hash_rev, 65);
    ESP_LOGI(TAG, "prev_block_hash_rev %s", prev_block_hash_rev);

    mining_notify notify_message;
    notify_message.job_id = 0; //Block #839666
    notify_message.prev_block_hash   = prev_block_hash_rev;
    notify_message.version = 0x20000000; //0x20106000;
    notify_message.target = 0x17034219;
    notify_message.ntime = 1713376819; //0x647025b5;
    notify_message.difficulty = 32800;
    notify_message.version_mask = 0x1fffe000;

    uint8_t merkle_root[32];
    hex2bin("2836bac5721062dfec270ebf9b554d002612ab6c1a0c05bd43d471892496c205", merkle_root, 32);
    if (rev_merkle_root_hash) {reverse_bytes(merkle_root, 32);}
    if (rev_merkle_root_hash_2) {
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
    bin2hex(merkle_root, 32, merkle_root_rev, 65);
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

    if (asic_result != NULL) {
        ESP_LOGI(TAG, "Received work");
    
        // check the nonce difficulty
        double nonce_diff = test_nonce_value(&job, asic_result->nonce, asic_result->rolled_version);
        ESP_LOGI(TAG, "Nonce %lu Nonce difficulty %.32f. rolled-version %08lx", asic_result->nonce, nonce_diff, asic_result->rolled_version);
        TEST_ASSERT_EQUAL_UINT32(1720357422, asic_result->nonce);
    }

    

    // memory
    free(GLOBAL_STATE.ASIC_TASK_MODULE.active_jobs);
    free(GLOBAL_STATE.valid_jobs);

    // turn ASIC off
    gpio_set_direction(GPIO_NUM_10, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_10, 1);
}

