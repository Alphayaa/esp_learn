#ifndef _BSP_LED_H_
#define _BSP_LED_H_

#define GPIO_LED_PIN       48   //设置GPIO33为LED
#define GPIO_ACTIVE_LEVEL  1    //设置高电平点亮LED

/**
 * @brief   LED初始化
 *
 */
void led_init(void);

/**
 * @brief       设置LED亮
 *
 */
void led_on(void);

void led_off(void);
#endif