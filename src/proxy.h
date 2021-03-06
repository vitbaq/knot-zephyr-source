/*
 * Copyright (c) 2019, CESAR. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Internal(Private) functions */

const knot_schema *proxy_get_schema(u8_t id);

void proxy_init(void);

void proxy_stop(void);

u8_t proxy_get_last_id(void);

const knot_value_type *proxy_read(u8_t id, uint8_t *olen, bool wait_resp);

s8_t proxy_write(u8_t id, const knot_value_type *value, u8_t value_len);

s8_t proxy_force_send(u8_t id);

s8_t proxy_confirm_sent(u8_t id);
