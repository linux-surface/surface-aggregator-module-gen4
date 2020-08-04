// SPDX-License-Identifier: GPL-2.0-or-later

#include <linux/kernel.h>
#include <linux/module.h>


static int __init sb1_dgpu_sw_init(void)
{
    return 0;   // TODO
}

static void __exit sb1_dgpu_sw_exit(void)
{
    // TODO
}

module_init(sb1_dgpu_sw_init);
module_exit(sb1_dgpu_sw_exit);

MODULE_AUTHOR("Maximilian Luz <luzmaximilian@gmail.com>");
MODULE_DESCRIPTION("Discrete GPU Power-Switch for Surface Book 1");
MODULE_LICENSE("GPL");
