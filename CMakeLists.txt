#
# Demo GPIO
#
# Copyright (C) 2019-2024, HENSOLDT Cyber GmbH
#
# SPDX-License-Identifier: GPL-2.0-or-later
#
# For commercial licensing, contact: info.cyber@hensoldt.net
#

cmake_minimum_required(VERSION 3.7.2)

os_set_config_file(system_config.h)

# set(KernelMaxNumNodes 2 CACHE STRING "" FORCE)

#-------------------------------------------------------------------------------
project(demo_gpio C)

DeclareCAmkESComponent(
    RPi_GPIO
    INCLUDES
        # no include paths needed
    SOURCES
        components/gpio_app/src/main.c
    C_FLAGS
        -Wall
        -Werror
    LIBS
        os_core_api
        lib_debug
        platsupport
        TimeServer_client
)

TimeServer_DeclareCAmkESComponent(
    TimeServer
)

DeclareAndCreateCamkESSystem(demo_gpio.camkes)
GenerateSimulateScript()
