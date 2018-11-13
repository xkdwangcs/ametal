/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief LPC82X WKT �û�����ʵ��
 * \sa am_hwconf_lpc82x_wkt.c
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-02  sky, modified.
 * - 1.00 15-07-08  zxl, first implementation.
 * \endinternal
 */

#include "am_lpc_wkt.h"
#include "am_lpc82x.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_pmu.h"


/**
 * \addtogroup am_if_src_hwconf_wkt
 * \copydoc am_hwconf_lpc82x_wkt.c
 * @{
 */

/** \brief WKTƽ̨��ʼ�� */
static void __lpc82x_wkt_plfm_init (void)
{
    /* ʹ��WKTʱ�� */
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_WKT);

    /* ��λWKT */
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_WKT);
}

/** \brief ���WKTƽ̨��ʼ�� */
static void __lpc82x_wkt_plfm_deinit (void)

{    /* ��λWKT */
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_WKT);

    /* ����WKTʱ�� */
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_WKT);

}

/** \brief WKTƽ̨ʱ�ӽ��ʼ�� */
static void __lpc82x_wkt_plfm_clk_init (const am_lpc_wkt_devinfo_t *p_devinfo)
{
    amhw_lpc_wkt_t  *p_hw_wkt  = (amhw_lpc_wkt_t *)(p_devinfo->wkt_regbase);

    if (p_devinfo == NULL) {
        return;
    }

    switch (p_devinfo->clksel_str) {
    case AMHW_LPC_WKT_IRC_CLOCK:

        /* ����WKTʱ��ԴΪ�ڲ�ʱ�� */
        amhw_lpc_wkt_clksel_cfg(p_hw_wkt, AMHW_LPC_WKT_IRC_CLOCK);

        break;
    case AMHW_LPC_WKT_LOW_POWER_CLOCK:

        /* ʹ�ܵ͹������� */
        amhw_lpc82x_pmu_lposcen_enable(LPC82X_PMU);

        /* ����WKTʱ��ԴΪ�͹������� */
        amhw_lpc_wkt_clksel_cfg(p_hw_wkt, AMHW_LPC_WKT_LOW_POWER_CLOCK);

        break;

    case AMHW_LPC_WKT_EXT_CLOCK:
        /* WAKEUPCLKHYS ���ų���ʹ�� */
        amhw_lpc82x_pmu_wakeupclkhys_enable(LPC82X_PMU);

        /* WAKECLKPAD����ʹ��(ʹ��PIO0_28�ⲿʱ�ӹ���) */
        amhw_lpc82x_pmu_wakeclkpad_enable(LPC82X_PMU);

        /* ����WKTʱ��ԴΪ�ⲿʱ�� */
        amhw_lpc_wkt_clksel_cfg(p_hw_wkt, AMHW_LPC_WKT_EXT_CLOCK);

        break;

    }

}

/** \brief WKT�豸��Ϣ */
static const am_lpc_wkt_devinfo_t __g_wkt_devinfo = {
    LPC82X_WKT_BASE,                /**< \brief WKT�Ĵ�����Ļ���ַ */
    INUM_WKT,                       /**< \brief WKT �жϱ�� */
    1,                              /**< \brief ֧��1��ͨ�� */
    AMHW_LPC_WKT_LOW_POWER_CLOCK,   /**< \brief ѡ��IRCʱ�� */
    0,                              /**< \brief ʹ���ⲿʱ��ʱ��Ƶ������ */

    __lpc82x_wkt_plfm_clk_init,     /**< \brief ƽ̨ʱ�ӳ�ʼ������ */

    __lpc82x_wkt_plfm_init,         /**< \brief WKTƽ̨��ʼ������ */
    __lpc82x_wkt_plfm_deinit        /**< \brief WKTƽ̨���ʼ������ */
};

static am_lpc_wkt_dev_t __g_wkt_dev;     /**< \brief WKT �豸���� */


/** \brief WKT ʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_lpc82x_wkt_inst_init (void)
{
    return am_lpc_wkt_init(&__g_wkt_dev, &__g_wkt_devinfo);
}

/** \brief WKT ʵ�����ʼ�� */
void am_lpc82x_wkt_inst_deinit (am_timer_handle_t handle)
{
    am_lpc_wkt_deinit(handle);
}

/**
 * @}
 */

/* end of file */