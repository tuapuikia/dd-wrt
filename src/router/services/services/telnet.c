/*
 * telnet.c
 *
 * Copyright (C) 2007 Sebastian Gottschall <gottschall@dd-wrt.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Id:
 */
#ifdef HAVE_TELNET
#include <stdlib.h>
#include <bcmnvram.h>
#include <shutils.h>
#include <utils.h>
#include <syslog.h>
#include <signal.h>
#include <services.h>

void start_telnetd(void)
{
	int ret = 0;
	pid_t pid;

	char *telnetd_argv[] = { "telnetd", NULL };
#ifdef HAVE_REGISTER
	char *telnetd_argv_reg[] = { "telnetd", "-l", "/sbin/regshell", NULL };
#endif
	stop_telnetd();

	if (!nvram_invmatch("telnetd_enable", "0"))
		return;

#ifdef HAVE_REGISTER
	if (isregistered_real())
#endif
		ret = _evalpid(telnetd_argv, NULL, 0, &pid);
#ifdef HAVE_REGISTER
	else
		return;
	// ret = _evalpid (telnetd_argv_reg, NULL, 0, &pid);
#endif
	dd_syslog(LOG_INFO, "telnetd : telnet daemon successfully started\n");

	cprintf("done\n");
	return;
}

void stop_telnetd(void)
{
	stop_process("telnetd", "telnet daemon");
	cprintf("done\n");
	return;
}
#endif
