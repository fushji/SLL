/* sll.c, SLL a C simple logging library
 *
 * Copyright (c) 2015, Antonio Perrone <fushji [at] gmail [dot] com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "sll.h"

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

/* Init logging subsystem */
int sll_init(const char *filename, SLL_LOG_LVL level) {

	if (logger != NULL)
		return SLL_RET_OK;

	logger = (struct _sll_logger *) calloc(1, sizeof(struct _sll_logger));
	if (logger == NULL)
		return SLL_RET_KO;

	// if no filename is specified, logs on stdout
	logger->fd = (filename == NULL) ? stdout : fopen(filename, "w");

	if (level >= SLL_LVL_DEBUG && level <= SLL_LVL_ERROR)
		logger->level = level;
	else
		logger->level = SLL_LVL_INFO;

	if (logger->fd == NULL)
		return SLL_RET_KO;

	return SLL_RET_OK;
}

/* Log function */
void sll_log(SLL_LOG_LVL level, const char *fmt, ...) {

	const char *sll_log_levels[] = { "DEBUG", "INFO", "WARNING", "ERROR" };

	va_list val;
	struct timeval tv;
	int offset;
	char msg[SLL_LOG_MSG_MAX_LEN];
	char buff[64];

	if (level < logger->level)
		return;

	va_start(val, fmt);
	vsnprintf(msg, sizeof(msg), fmt, val);
	va_end(val);

	gettimeofday(&tv, NULL);
	offset = strftime(buff, sizeof(buff), "%d %b %H:%M:%S.", localtime(&tv.tv_sec));
	snprintf(buff + offset, sizeof(buff) - offset, "%03d", (int) tv.tv_usec / 1000);

	flockfile(logger->fd);

	fprintf(logger->fd, "%d - %s [%s] %s\n", (int) getpid(), buff,
			sll_log_levels[level], msg);

	funlockfile(logger->fd);
	fflush(logger->fd);
}

/* Close logging subsystem */
int sll_close() {

	if (logger->fd != NULL) {
		fflush(logger->fd);
		fclose(logger->fd);
	}
	free(logger);

	return SLL_RET_OK;
}
