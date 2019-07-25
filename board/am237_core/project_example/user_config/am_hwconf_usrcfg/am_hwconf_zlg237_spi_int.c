/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief ZLG237 SPI INT 用户配置文件
 * \sa am_hwconf_zlg237_spi.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-7-19  fra, first implementation
 * \endinternal
 */

#include "am_zlg237.h"
#include "zlg237_pin.h"
#include "ametal.h"
#include "am_zlg237_spi_int.h"
#include "am_gpio.h"
#include "amhw_zlg237_spi.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zlg237_spi_int
 * \copydoc am_hwconf_zlg237_spi_int.c
 * @{
 */

/** \brief SPI1 平台初始化 */
static void __zlg_plfm_spi1_int_init (void)
{
    am_gpio_pin_cfg(PIOA_5, PIOA_5_SPI1_SCK_REMAP0  | PIOA_5_AF_PP);
    am_gpio_pin_cfg(PIOA_6, PIOA_6_SPI1_MISO_REMAP0 | PIOA_6_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOA_7, PIOA_7_SPI1_MOSI_REMAP0 | PIOA_7_AF_PP);

    am_clk_enable(CLK_SPI1);
}

/** \brief 解除SPI1 平台初始化 */
static void __zlg_plfm_spi1_int_deinit (void)
{
    am_gpio_pin_cfg(PIOA_5, AM_GPIO_INPUT );
    am_gpio_pin_cfg(PIOA_6, AM_GPIO_INPUT );
    am_gpio_pin_cfg(PIOA_7, AM_GPIO_INPUT );

    am_clk_disable(CLK_SPI1);
}

/** \brief SPI1 设备信息 */
const  struct am_zlg237_spi_int_devinfo  __g_spi1_int_devinfo = {
    ZLG237_SPI1_BASE,                        /**< \brief SPI1寄存器指针 */
    CLK_SPI1,                                /**< \brief 时钟ID号 */
    AMHW_ZLG237_SPI_BAUDRATE_PRESCALER_16,   /**< \brief 时钟分频系数 */
    INUM_SPI1,                               /**< \brief SPI1中断号 */
    PIOA_7_SPI1_MOSI_REMAP0 | PIOA_7_AF_PP,  /**< \brief SPI1配置标识 */
    PIOA_7,                                  /**< \brief MOSI引脚号 */
    __zlg_plfm_spi1_int_init,                /**< \brief SPI1平台初始化函数 */
    __zlg_plfm_spi1_int_deinit               /**< \brief SPI1平台解初始化函数 */
};

/** \brief SPI1 设备实例 */
static am_zlg237_spi_int_dev_t __g_spi1_int_dev;

/** \brief SPI1 实例初始化，获得SPI标准服务句柄 */
am_spi_handle_t am_zlg237_spi1_int_inst_init (void)
{
    return am_zlg237_spi_int_init(&__g_spi1_int_dev, &__g_spi1_int_devinfo);
}

/** \brief SPI1 实例解初始化 */
void am_zlg237_spi1_int_inst_deinit (am_spi_handle_t handle)
{
    am_zlg237_spi_int_deinit(handle);
}

/** \brief SPI2 平台初始化 */
static void __zlg_plfm_spi2_int_init (void)
{
    am_clk_enable(CLK_SPI2);

    am_gpio_pin_cfg(PIOB_14, PIOB_14_SPI2_MISO | PIOB_14_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_SPI2_MOSI | PIOB_15_AF_PP);
    am_gpio_pin_cfg(PIOB_13, PIOB_13_SPI2_SCK  | PIOB_13_AF_PP);
}

/** \brief 解除SPI2 平台初始化 */
static void __zlg_plfm_spi2_int_deinit (void)
{
    am_gpio_pin_cfg(PIOB_13, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_14, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_15, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI2);
}
/**
 * \brief SPI2 设备信息
 */
const  struct am_zlg237_spi_int_devinfo  __g_spi2_int_devinfo = {
    ZLG237_SPI2_BASE,                      /**< \brief SPI2寄存器指针 */
    CLK_SPI2,                              /**< \brief 时钟ID号 */
    AMHW_ZLG237_SPI_BAUDRATE_PRESCALER_16, /**< \brief 时钟分频系数 */
    INUM_SPI2,                             /**< \brief SPI2中断号 */
    PIOB_15_SPI2_MOSI | PIOB_15_AF_PP,     /**< \brief SPI2配置标识 */
    PIOB_15,                               /**< \brief mosi引脚号 */
    __zlg_plfm_spi2_int_init,              /**< \brief SPI2平台初始化函数 */
    __zlg_plfm_spi2_int_deinit             /**< \brief SPI2平台解初始化函数 */
};

/** \brief SPI2 设备实例 */
static am_zlg237_spi_int_dev_t __g_spi2_int_dev;

/** \brief SPI2 实例初始化，获得SPI标准服务句柄 */
am_spi_handle_t am_zlg237_spi2_int_inst_init (void)
{
    return am_zlg237_spi_int_init(&__g_spi2_int_dev, &__g_spi2_int_devinfo);
}

/** \brief SPI2 实例解初始化 */
void am_zlg237_spi2_int_inst_deinit (am_spi_handle_t handle)
{
	am_zlg237_spi_int_deinit(handle);
}

/**
 * @}
 */

/* end of file */
