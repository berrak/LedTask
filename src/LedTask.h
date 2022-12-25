/*!
 * @file LedTask.h
 *
 * This is part of LedTask library for the Arduino platform.
 *
 * The MIT license.
 *
 */

#pragma once

/**************************************************************************/
/*!
    @brief  Class that maintain and change state of LED's.
*/
/**************************************************************************/
class LedTask {
public:
    // Constructor: pin number for attached LED
    explicit LedTask(uint16_t pin);
    ~LedTask(void);

    void begin(uint32_t ms_on_tm, uint32_t ms_off_tm);
    void begin(float hz_pwm_frequency = 1000);
    void updateBlinkLed(void);
    void updatePwmTask(float percentage_high);

    // Uses delay() - blocking code
    void pulseLedBlk(uint8_t pulse_cnt, uint32_t ms_on_tm, uint32_t ms_off_tm);

    static inline uint16_t instance_count = 0; ///< counter to keep track of instances
    static uint16_t getInstanceCount(void);

private:
    uint16_t led_pin;  ///< LED pin
    uint32_t on_time;  ///< milliseconds of on-time
    uint32_t off_time; ///< milliseconds of off-time

    int led_state;                 ///< led_state (ON/OFF) for LED
    unsigned long previous_millis; ///< stores last time LED was updated
    float pwm_frequency;           ///< repetition frequency for pwm output
};
