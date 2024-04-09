#include "work_queue.h"
#include "global_state.h"
#include "esp_log.h"
#include "esp_system.h"
#include "mining.h"
#include <limits.h>
#include "string.h"

#include <sys/time.h>

static const char *TAG = "create_jobs_task";

void create_jobs_task(void *pvParameters)
{

    GlobalState *GLOBAL_STATE = (GlobalState *)pvParameters;

    while (1)
    {
        mining_notify *mining_notification = (mining_notify *)queue_dequeue(&GLOBAL_STATE->stratum_queue);
        ESP_LOGI(TAG, "New Work Dequeued %s (queue %d/%d)", mining_notification->job_id, GLOBAL_STATE->stratum_queue.count, QUEUE_SIZE);

        uint32_t extranonce_2 = 0;
        while (extranonce_2 < 256 && GLOBAL_STATE->abandon_work == 0)
        {
            char *extranonce_2_str = extranonce_2_generate(extranonce_2, GLOBAL_STATE->extranonce_2_len);

            char *coinbase_tx = construct_coinbase_tx(mining_notification->coinbase_1, mining_notification->coinbase_2, GLOBAL_STATE->extranonce_str, extranonce_2_str);

            char *merkle_root = calculate_merkle_root_hash(coinbase_tx, (uint8_t(*)[32])mining_notification->merkle_branches, mining_notification->n_merkle_branches);
            bm_job next_job = construct_bm_job(mining_notification, merkle_root, GLOBAL_STATE->version_mask);

            bm_job *queued_next_job = malloc(sizeof(bm_job));
            memcpy(queued_next_job, &next_job, sizeof(bm_job));
            queued_next_job->extranonce2 = strdup(extranonce_2_str);
            queued_next_job->jobid = strdup(mining_notification->job_id);
            queued_next_job->version_mask = GLOBAL_STATE->version_mask;

            queue_enqueue(&GLOBAL_STATE->ASIC_jobs_queue, queued_next_job);
            //ESP_LOGI(TAG, "New ASIC Job Enqueued %s (queue %d/%d)", queued_next_job->jobid, GLOBAL_STATE->ASIC_jobs_queue.count, QUEUE_SIZE);

            free(coinbase_tx);
            free(merkle_root);
            free(extranonce_2_str);
            extranonce_2++;
        }

        if (GLOBAL_STATE->abandon_work == 1)
        {
            GLOBAL_STATE->abandon_work = 0;
            ASIC_jobs_queue_clear(&GLOBAL_STATE->ASIC_jobs_queue);
        }

        STRATUM_V1_free_mining_notify(mining_notification);
    }
}
