/* sll.h, SLL a C simple logging library
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

#ifndef __SLL_H
#define __SLL_H

#include <stdio.h>

/* Define log level */
typedef int SLL_LOG_LVL;

#define SLL_LVL_DEBUG   0
#define SLL_LVL_INFO    1
#define SLL_LVL_WARNING 2
#define SLL_LVL_ERROR   3

#define SLL_LOG_MSG_MAX_LEN 1024 /* Log message max length */

/* Define return code */
#define SLL_RET_OK 0
#define SLL_RET_KO 0

struct _sll_logger {
	FILE *fd;
	char *filename;
	SLL_LOG_LVL level;
};

struct _sll_logger *logger;

/** Public API */
int sll_init(const char *filename, SLL_LOG_LVL level);
void sll_log(SLL_LOG_LVL level, const char *fmt, ...);
int sll_close();

#endif //__SLL_H
