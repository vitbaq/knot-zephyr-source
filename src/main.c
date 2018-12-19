/*
 * Copyright (c) 2018 CESAR. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <misc/printk.h>

void main(void)
{
	printk("KNoT hello world! %s\n", CONFIG_BOARD);
}
