// SPDX-License-Identifier: MIT
/*
 *
 * This file is part of rurima, with ABSOLUTELY NO WARRANTY.
 *
 * MIT License
 *
 * Copyright (c) 2024 Moe-hacker
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
 *
 *
 */
#include "include/rurima.h"
void check_dep(void)
{
	/*
	 * Check dependencies.
	 */
	const char *tar_command[] = { "tar", "--version", NULL };
	const char *curl_command[] = { "curl", "--version", NULL };
	const char *file_command[] = { "file", "--version", NULL };
	const char *gz_command[] = { "gzip", "--version", NULL };
	const char *xz_command[] = { "xz", "-V", NULL };
	char *result = NULL;
	result = fork_execvp_get_stdout(tar_command);
	if (result == NULL) {
		error("{red}tar not found!\nIf you are aarch64, armv7, x86_64, i386 or riscv64 user\nYou can find it in\nhttps://github.com/Moe-sushi/tar-static\n");
	}
	free(result);
	result = fork_execvp_get_stdout(curl_command);
	if (result == NULL) {
		error("{red}curl not found!\nIf you are aarch64, armv7, x86_64, i386 or riscv64 user\nYou can find it in\nhttps://github.com/Moe-sushi/curl-static\n");
	}
	free(result);
	result = fork_execvp_get_stdout(file_command);
	if (result == NULL) {
		error("{red}file not found!\nIf you are aarch64, armv7, x86_64, i386 or riscv64 user\nYou can find it in\nhttps://github.com/Moe-sushi/file-static\n");
	}
	free(result);
	result = fork_execvp_get_stdout(gz_command);
	if (result == NULL) {
		error("{red}gzip not found!\nIf you are aarch64, armv7, x86_64, i386 or riscv64 user\nYou can find it in\nhttps://github.com/Moe-sushi/gzip-static\n");
	}
	free(result);
	result = fork_execvp_get_stdout(xz_command);
	if (result == NULL) {
		error("{red}xz not found!\nIf you are aarch64, armv7, x86_64, i386 or riscv64 user\nYou can find it in\nhttps://github.com/Moe-sushi/xz-static\n");
	}
	free(result);
}