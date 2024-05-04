#include "global_state.h"
#include "work_queue.h"
#include "serial.h"
#include "bm1397.h"
#include <string.h>
#include "esp_log.h"
#include "nvs_config.h"
#include "utils.h"

const char *TAG = "asic_result";

void ASIC_result_task(void *pvParameters)
{
    GlobalState *GLOBAL_STATE = (GlobalState *)pvParameters;
    SERIAL_clear_buffer();

    char *user = nvs_config_get_string(NVS_CONFIG_STRATUM_USER, STRATUM_USER);

    uint32_t first_nonce = 0;
    uint32_t first_job_id = 0;

    while (1)
    {
        task_result *asic_result = (*GLOBAL_STATE->ASIC_functions.receive_result_fn)(GLOBAL_STATE);

        if (asic_result == NULL) // check if we got serial timeout
        {
            pthread_mutex_lock(&GLOBAL_STATE->asic_needs_new_job_lock);
            GLOBAL_STATE->asic_needs_new_job = true;
            pthread_mutex_unlock(&GLOBAL_STATE->asic_needs_new_job_lock);
            continue;
        }

        if (GLOBAL_STATE->asic_needs_new_job == true) { // cchecck if new job is already requested (rollover detected)
            continue;
        }

        uint8_t job_id = asic_result->job_id;

        if (GLOBAL_STATE->valid_jobs[job_id] == 0)
        {
            ESP_LOGI(TAG, "Invalid job nonce found, id=%d", job_id);
        }

        if (job_id != first_job_id) // check if this is the first result of the job, if so we use it for rollover detection
        {
            first_job_id = job_id;
            first_nonce = asic_result->nonce;

        } else if (asic_result->nonce == first_nonce) // rollover is detected whenever we see the first result again 
        {
            pthread_mutex_lock(&GLOBAL_STATE->asic_needs_new_job_lock);
            GLOBAL_STATE->asic_needs_new_job = true; // set flag to signal asic_task to push a new job
            pthread_mutex_unlock(&GLOBAL_STATE->asic_needs_new_job_lock);

            ESP_LOGI(TAG, "Job ID: %02x, Rollover detected - Nonce %08lx, Rolled_version 0x%08lx - request new job", asic_result->job_id, asic_result->nonce, asic_result->rolled_version);
            continue;
        }

        // check the nonce difficulty
        double nonce_diff = test_nonce_value(
            GLOBAL_STATE->ASIC_TASK_MODULE.active_jobs[job_id],
            asic_result->nonce,
            asic_result->rolled_version);

        ESP_LOGI(TAG, "Nonce difficulty %.2f of %ld.", nonce_diff, GLOBAL_STATE->ASIC_TASK_MODULE.active_jobs[job_id]->pool_diff);

        if (nonce_diff > GLOBAL_STATE->ASIC_TASK_MODULE.active_jobs[job_id]->pool_diff)
        {

            STRATUM_V1_submit_share(
                GLOBAL_STATE->sock,
                user,
                GLOBAL_STATE->ASIC_TASK_MODULE.active_jobs[job_id]->jobid,
                GLOBAL_STATE->ASIC_TASK_MODULE.active_jobs[job_id]->extranonce2,
                GLOBAL_STATE->ASIC_TASK_MODULE.active_jobs[job_id]->ntime,
                asic_result->nonce,
                asic_result->rolled_version ^ GLOBAL_STATE->ASIC_TASK_MODULE.active_jobs[job_id]->version);

            SYSTEM_notify_found_nonce(&GLOBAL_STATE->SYSTEM_MODULE, GLOBAL_STATE->ASIC_TASK_MODULE.active_jobs[job_id]->pool_diff,
                                      nonce_diff, GLOBAL_STATE->ASIC_TASK_MODULE.active_jobs[job_id]->target,
                                      GLOBAL_STATE->POWER_MANAGEMENT_MODULE.power);
        }
    }
}