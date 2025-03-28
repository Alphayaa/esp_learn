#ifndef _BSP_TIMER_H_
#define _BSP_TIMER_H_

#include "driver/gptimer.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"


QueueHandle_t timer_init(uint32_t resolution_hz, uint64_t alarm_count);

#endif