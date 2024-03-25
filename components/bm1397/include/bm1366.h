#ifndef BM1366_H_
#define BM1366_H_

#include "common.h"
#include "driver/gpio.h"
#include "mining.h"

#define CRC5_MASK 0x1F

/*
"asic_id": "BM1366",
"asic_addr": "0x1366",
"asic_core_num": 112,
"asic_small_core_num": 894,
"core_small_core_num": 8,
"asic_domain_num": 1,
"asic_addr_interval": 1
*/

// static const uint64_t BM1366_FREQUENCY = CONFIG_ASIC_FREQUENCY;
static const uint64_t BM1366_CORE_COUNT = 894;
// static const uint64_t BM1366_HASHRATE_S = BM1366_FREQUENCY * BM1366_CORE_COUNT * 1000000;
//  2^32
// static const uint64_t NONCE_SPACE = 4294967296; // already defined in BM1397.h
//  2^8
static const uint64_t BM1366_ROLLING_VERSION_SPACE = 256;
//static const double BM1366_FULLSCAN_MS = 2140;
//static const double BM1366_FULLSCAN_MS = (double) ((double) (NONCE_SPACE * BM1366_ROLLING_VERSION_SPACE) / (double) (BM1366_FREQUENCY * BM1366_CORE_COUNT * 1000000) * 1000);

typedef struct
{
    float frequency;
} bm1366Module;

typedef struct __attribute__((__packed__))
{
    uint8_t job_id;
    uint8_t num_midstates;
    uint8_t starting_nonce[4];
    uint8_t nbits[4];
    uint8_t ntime[4];
    uint8_t merkle_root[32];
    uint8_t prev_block_hash[32];
    uint8_t version[4];
} BM1366_job;

uint8_t BM1366_init(uint64_t frequency);

void BM1366_send_init(void);
void BM1366_send_work(void * GLOBAL_STATE, bm_job * next_bm_job);
void BM1366_set_job_difficulty_mask(int);
int BM1366_set_max_baud(void);
int BM1366_set_default_baud(void);
void BM1366_send_hash_frequency(float frequency);
task_result * BM1366_proccess_work(void * GLOBAL_STATE);
double BM1366_get_fullscan_ms(float frequency);

#endif /* BM1366_H_ */