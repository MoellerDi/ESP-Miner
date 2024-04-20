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

// bm1366: 8 cores, 112 asic_cores each = 896 small cores (what are the 2 additional (896 vs. 894) small cores for?)
static const uint64_t BM1366_CHIP_COUNT = 1;
static const uint64_t BM1366_CORE_COUNT = 894;
// chip count and core count play together to distribute nonce space equally. see https://youtu.be/6o92HhvOc1I?t=5710
// 2^8 to be distributed to all chips -> 256 / chip count -> 256 / 1 (Bitaxe has just 1 single bm1366 chip)
// 2^8 distributed chip internal to all small cores (a.k.a. asic_small_core) -> 256 / asic_small_core -> 256 / 894 
// 2^16 rolling nonce on each asic_small_core
static const uint64_t BM1366_NONCE_SPACE_PER_CHIP = (256/BM1366_CHIP_COUNT)*65536;
// 2^16 version rolling for each nonce on each asic_small_core
static const uint64_t BM1366_ROLLING_VERSION_SPACE = 65536;
// Nonce space * rooling version space
static const uint64_t SPACE_TO_BE_CALCULATED = BM1366_NONCE_SPACE_PER_CHIP * BM1366_ROLLING_VERSION_SPACE;
// fullscan_ms = (((2^8/1)*2^16)*2^16)/(485*894*1000000)*1000

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
void BM1366_set_chip_address(uint8_t new_address);

#endif /* BM1366_H_ */