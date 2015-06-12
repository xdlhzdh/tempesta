/**
 *		Tempesta FW
 *
 * Copyright (C) 2012-2014 NatSys Lab. (info@natsys-lab.com).
 * Copyright (C) 2015 Tempesta Technologies, Inc.
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
#ifndef __TFW_ADDR_H__
#define __TFW_ADDR_H__

#include <net/inet_sock.h>

/**
 * The default port for textual IP address representations.
 * I.e., "127.0.0.1" is equal to "127.0.0.1:80", but that is true only for
 * strings, and deserialized representation (TfwAddr) is not affected.
 */
#define TFW_ADDR_STR_DEF_PORT 80

/* Maximum size of a buffer needed for tfw_addr_ntop(), including '\0'. */
#define TFW_ADDR_STR_BUF_SIZE \
	sizeof("[FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:255.255.255.255]:65535")

typedef union {
	struct sockaddr_in v4;
	struct sockaddr_in6 v6;
	struct sockaddr sa;
	sa_family_t family;
} TfwAddr;

bool tfw_addr_eq(const TfwAddr *addr1, const TfwAddr *addr2);
int tfw_addr_pton(const char *str, TfwAddr *addr);
size_t tfw_addr_ntop(const TfwAddr *addr, char *out_buf, size_t buf_size);

/* A couple of lower-level functions faster than tfw_addr_ntop().
 * Note that they don't check input arguments and don't terminate output. */
char *tfw_addr_fmt_v4(__be32 in_addr, __be16 in_port, char *out_buf);
char *tfw_addr_fmt_v6(const struct in6_addr *in6_addr, __be16 in_port,
			char *out_buf);

static inline ssize_t
tfw_addr_sa_len(const TfwAddr *addr)
{
	return (addr->family == AF_INET6) ? sizeof(addr->v6) : sizeof(addr->v4);
}

#endif /* __TFW_ADDR_H__ */