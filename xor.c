/* xor.c -- single byte xor tool
 * by Daniel Roberson - @dmfroberson - daniel@planethacker.net
 *
 * Reads input file and outputs every possible single character xor.
 * This helped me solve a CTF puzzle, so I cleaned up the code
 * slightly and released it. Maybe it will come in handy in the
 * future.
 *
 * Every xor combination is output to a file named after its hexadecimal
 * representation: 00 - ff.
 *
 * Example use:
 * $ ./xor /bin/ls
 * $ file ??
 * 00:    ELF 64-bit LSB executable, x86-64, version 1 (SYSV), ....
 * 01:    data
 * 02:    data
 * 03:    data
 * 04:    data
 * 05:    data
 * ...
 * ...
 * fd:    data
 * fe:    data
 * ff:    8086 relocatable (Microsoft)
 */

#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char *argv[]) {
  FILE *input, *fp;
  char filename[2];
  char *buf;
  int i, x;
  struct stat s;


  if (argv[1] == NULL) {
    fprintf (stderr, "usage: %s <input file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  input = fopen (argv[1], "r");
  if (input == NULL) {
    fprintf (stderr, "unable to open input file %s for reading: %s\n",
	     argv[0],
	     strerror (errno));
    return EXIT_FAILURE;
  }

  if (stat(argv[1], &s) < 0) {
    fprintf (stderr, "failed to stat input file %s: %s\n",
	     argv[0],
	     strerror (errno));
    return EXIT_FAILURE;
  }

  buf = malloc(s.st_size);
  if (buf == NULL) {
    fprintf (stderr, "failed to allocate %ld bytes of memory: %s\n",
	     s.st_size,
	     strerror (errno));
    return EXIT_FAILURE;
  }

  if (fread(buf, sizeof(char), s.st_size, input) != s.st_size) {
    fprintf (stderr, "failed to read %ld bytes from %s: %s\n",
	     s.st_size,
	     argv[1],
	     strerror (errno));
    return EXIT_FAILURE;
  }


  for (x = 0; x < 256; x++) {
    sprintf (filename, "%.2x", x);

    fp = fopen (filename, "w");

    for (i = 0; i < s.st_size; i++) {
      fputc (buf[i] ^ x, fp); 
    }

    fclose (fp);
  }

  fclose (input);
  free (buf);

  return EXIT_SUCCESS;
}
