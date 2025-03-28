/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "esp_sleep.h"
#include "unistd.h"
#include "../hardware/inc/bsp_led.h"
#include "../hardware/inc/bsp_timer.h"

static void periodic_timer_callback(void* arg);
static void oneshot_timer_callback(void* arg);

static const char *TAG = "main";

void app_main(void)
{
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), %s%s%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
           (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }

    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

    fflush(stdout);
    led_init();

    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &periodic_timer_callback,
        .name = "periodic"
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));

    const esp_timer_create_args_t oneshot_timer_args = {
        .callback = &oneshot_timer_callback,
        .arg = (void *)periodic_timer,
        .name = "oneshot"
    };
    esp_timer_handle_t oneshot_timer;
    ESP_ERROR_CHECK(esp_timer_create(&oneshot_timer_args, &oneshot_timer));

    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 500000)); // 1s
    ESP_ERROR_CHECK(esp_timer_start_once(oneshot_timer, 5000000)); // 5s


    ESP_LOGI(TAG, "current counting time: %lld us", esp_timer_get_time());


    usleep(10000000); // 10s

    ESP_ERROR_CHECK(esp_timer_stop(periodic_timer));
    ESP_ERROR_CHECK(esp_timer_delete(periodic_timer));
    ESP_ERROR_CHECK(esp_timer_delete(oneshot_timer));

    ESP_LOGI(TAG, "Stopped and deleted timers");

}


static void periodic_timer_callback(void* arg)
{
    ESP_LOGI(TAG, "current counting time: %lld us", esp_timer_get_time());
}

static void oneshot_timer_callback(void* arg)
{
    int64_t time_since_boot = esp_timer_get_time();
    ESP_LOGI(TAG, "One-shot time since boot: %lld us", time_since_boot);

    esp_timer_handle_t periodic_timer = (esp_timer_handle_t)arg;
    ESP_ERROR_CHECK(esp_timer_stop(periodic_timer)); // 1s
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 1000000)); // 1s

    time_since_boot = esp_timer_get_time();
    ESP_LOGI(TAG, "One-shot time since boot: %lld us", time_since_boot);
}