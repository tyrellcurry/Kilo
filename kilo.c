// https://viewsourcecode.org/snaptoken/kilo
/*** includes ***/
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/*** defines ***/
#define CTRL_KEY(k) ((k) & 0x1f)

/*** data ***/
struct termios orig_termios;

/*** terminal ***/

void die(const char *s) {
  perror(s);
  exit(1);
}

void raw_mode_disable(void) {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    die("tcsetattr");

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void raw_mode_enable(void) {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
    die("tcgetattr");

  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(raw_mode_disable);
  struct termios raw = orig_termios;

  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    die("tcsetattr");

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

char editor_read_key(void) {
	int nread;
	char c;
	while((nread = read(STDERR_FILENO, &c, 1)) != 1) {
		if (nread == -1 && errno != EAGAIN) die("read");
	}
	return c;
}

/*** input ***/
void editor_process_keypress(void) {
	char c = editor_read_key();

	switch (c) {
		case CTRL_KEY('q'):
			exit(0);
			break;
	}
}

/*** init ***/

int main(void) {
  raw_mode_enable();

  while (1) {
		editor_process_keypress();
  }

  return 0;
}
