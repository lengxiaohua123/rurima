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
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
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
static void show_help(void)
{
	cprintf("{green}Usage: rurima [subcommand] [options]\n");
	cprintf("{green}Subcommands:\n");
	cprintf("{green}  docker: DockerHub support.\n");
	cprintf("{green}  lxc: LXC mirror support.\n");
	cprintf("{green}  unpack: Unpack rootfs.\n");
	cprintf("{green}  help: Show help message.\n");
	cprintf("{green}Options:\n");
	cprintf("{green}  -h, --help: Show help message.\n");
}
int main(int argc, char **argv)
{
	register_signal();
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "docker") == 0) {
			if (i + 1 >= argc) {
				error("{red}No subcommand specified!\n");
			}
			docker(argc - i - 1, &argv[i + 1]);
			return 0;
		} else if (strcmp(argv[i], "lxc") == 0) {
			if (i + 1 >= argc) {
				error("{red}No subcommand specified!\n");
			}
			lxc(argc - i - 1, &argv[i + 1]);
			return 0;
		} else if (strcmp(argv[i], "unpack") == 0) {
			unpack(argc - i - 1, &argv[i + 1]);
			return 0;
		} else if (strcmp(argv[i], "help") == 0 || strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			show_help();
			return 0;
		}
	}
	return 0;
}