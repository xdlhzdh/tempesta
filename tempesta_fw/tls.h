/**
 *		Tempesta FW
 *
 * Copyright (C) 2015-2019 Tempesta Technologies, Inc.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59
 * Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#ifndef __TFW_TLS_H__
#define __TFW_TLS_H__

#include "gfsm.h"
#include "ttls.h"

#define TFW_FSM_TLS		TFW_FSM_HTTPS

/**
 * TLS states.
 */
#define TFW_GFSM_TLS_STATE(s)	((TFW_FSM_TLS << TFW_GFSM_FSM_SHIFT) | (s))
enum {
	/* TLS FSM initial state, not hookable. */
	TFW_TLS_FSM_INIT	= TFW_GFSM_TLS_STATE(0),
	/*
	 * A TLS Handshake has been completed on a connection. Client could
	 * either process a new full handshake or resume previous session. The
	 * state is also reached if the handshake process ended up with the
	 * error or never reached the final stage.
	 */
	TFW_TLS_FSM_HS_DONE	= TFW_GFSM_TLS_STATE(1),
	/*
	 * A new portion of data is decrypted and ready to be consumed by the
	 * upper layers.
	 */
	TFW_TLS_FSM_DATA_READY	= TFW_GFSM_TLS_STATE(2),

	TFW_TLS_FSM_DONE	= TFW_GFSM_TLS_STATE(TFW_GFSM_STATE_LAST)
};

void tfw_tls_cfg_require(void);
void tfw_tls_cfg_configured(bool global);
void tfw_tls_match_any_sni_to_dflt(bool match);
int tfw_tls_cfg_alpn_protos(const char *cfg_str, bool *deprecated);
void tfw_tls_free_alpn_protos(void);
int tfw_tls_encrypt(struct sock *sk, struct sk_buff *skb, unsigned int limit);

#endif /* __TFW_TLS_H__ */
