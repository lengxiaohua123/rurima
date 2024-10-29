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
static char **get_extract_command(const char *_Nonnull file, const char *_Nonnull dir)
{
	/*
	 * Warning: free() after use.
	 * Only need to free **ret.
	 * ret[] does not need free().
	 * Get the command to extract the archive.
	 * Only support tar, gzip, xz.
	 * If the file is not supported, return NULL.
	 */
	char **ret = malloc(sizeof(char *) * 8);
	const char *file_command[] = { "file", "--brief", "--mime-type", file, NULL };
	char *type = fork_execvp_get_stdout(file_command);
	if (type == NULL) {
		free(ret);
		return NULL;
	}
	type[strlen(type) - 1] = '\0';
	if (strcmp(type, "application/gzip") == 0) {
		ret[0] = "tar";
		ret[1] = "-xzf";
		ret[2] = "-";
		ret[3] = "-C";
		ret[4] = (char *)dir;
		ret[5] = NULL;
	} else if (strcmp(type, "application/x-xz") == 0) {
		ret[0] = "tar";
		ret[1] = "-xJf";
		ret[2] = "-";
		ret[3] = "-C";
		ret[4] = (char *)dir;
		ret[5] = NULL;
	} else if (strcmp(type, "application/x-tar") == 0) {
		ret[0] = "tar";
		ret[1] = "-xf";
		ret[2] = "-";
		ret[3] = "-C";
		ret[4] = (char *)dir;
		ret[5] = NULL;
	} else {
		free(type);
		free(ret);
		return NULL;
	}
	free(type);
	return ret;
}
static void show_progress(double per)
{
	/*
	 * Show progress bar.
	 */
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	unsigned short width = size.ws_col - 10;
	unsigned short pos = (unsigned short)(width * per);
	printf("\033[?25l");
	printf("\r[\033[32m");
	for (unsigned short i = 0; i < pos; i++) {
		printf(">");
	}
	for (unsigned short i = pos; i < width; i++) {
		printf("\033[33m=");
	}
	printf("\033[0m] %.2f%%", per * 100);
	fflush(stdout);
	printf("\033[?25h");
}
int extract_archive(const char *_Nonnull file, const char *_Nonnull dir)
{
	/*
	 * Extract the archive.
	 * Return 0 if success, 1 if failed.
	 *
	 * We read the file, output it to stdout,
	 * and then pipe it to the extract command.
	 * So that we can show a progress bar by the size we output.
	 *
	 */
	off_t size = get_file_size(file);
	if (size == 0) {
		return 1;
	}
	char **command = get_extract_command(file, dir);
	if (command == NULL) {
		return 1;
	}
	if (mkdirs(dir, 0755) == -1) {
		free(command);
		return 1;
	}
	cprintf("{yellow}Extracting {cyan}%s :\n", file);
	FILE *fp = fopen(file, "rb");
	int pipefd[2];
	if (pipe(pipefd) == -1) {
		perror("pipe");
		free(command);
		return 1;
	}
	pid_t pid = fork();
	if (pid == 0) {
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		int fd = open("/dev/null", O_WRONLY);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
		execvp(command[0], command);
		free(command);
		exit(114);
	} else {
		close(pipefd[0]);
		char buf[1024];
		size_t bytes_read;
		size_t total_read = 0;
		while ((bytes_read = fread(buf, 1, 1024, fp)) > 0) {
			total_read += bytes_read;
			double progress = (double)total_read / (double)size;
			show_progress(progress);
			if (write(pipefd[1], buf, bytes_read) == -1) {
				perror("write");
				free(command);
				return 1;
			}
		}
		close(pipefd[1]);
		fclose(fp);
		wait(NULL);
		show_progress(1.0);
		printf("\n");
		free(command);
		return 0;
	}
	free(command);
	return 0;
}