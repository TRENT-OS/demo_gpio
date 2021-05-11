/**
 * Copyright (C) 2019-2020, Hensoldt Cyber GmbH
 */

#include <stdio.h>
#include <lib_debug/Debug.h>

#include <platsupport/gpio.h>
#include <platsupport/plat/gpio.h>

#include <camkes.h>
#include <camkes/io.h>

#include "TimeServer.h"

gpio_sys_t  gpio_sys;
gpio_t      gpio;
ps_io_ops_t         io_ops;

static const if_OS_Timer_t timer =
    IF_OS_TIMER_ASSIGN(
        timeServer_rpc,
        timeServer_notify);

void post_init(void)
{
    Debug_LOG_DEBUG("[%s] %s", get_instance_name(), __func__);

    int ret = camkes_io_ops(&io_ops);
    if (ret )
    {
        Debug_LOG_ERROR("camkes_io_ops() failed: rslt = %i", ret);
        return;
    }

    //gpio initialization
    ret = gpio_sys_init(&io_ops,&gpio_sys);
    if (ret)
    {
        ZF_LOGE("gpio_sys_init() failed: rslt = %i", ret);
        return;
    }

    Debug_LOG_INFO("%s done",__func__);
}

int run()
{
    gpio_new(&gpio_sys, GPIOID_GPIO_08, 0, &gpio);
    bcm2837_gpio_fsel(&gpio,BCM2837_GPIO_FSEL_OUTP);

    while (1)
    {
        Debug_LOG_DEBUG("LED off!");
        gpio_clr(&gpio);
        Debug_LOG_DEBUG("Current State: %d",gpio_get(&gpio));
        TimeServer_sleep(&timer, TimeServer_PRECISION_MSEC, 1000);
        Debug_LOG_DEBUG("LED on!");
        gpio_set(&gpio);
        Debug_LOG_DEBUG("Current State: %d",gpio_get(&gpio));
        TimeServer_sleep(&timer, TimeServer_PRECISION_MSEC, 1000);
    }

    return 0;
}
