/**************************************************************************/

#include "rs232.h"

int tty_error;

struct termios new_port_settings;
struct termios old_port_settings;

/***************************************************************************
* FUNCTION: open_serial()
***************************************************************************/
int open_serial(char *serial_device,
		int baudrate,
		const char *mode)
{
  int baudr, status;
  
  switch (baudrate) {
  case      50 : baudr = B50;
    break;
  case      75 : baudr = B75;
    break;
  case     110 : baudr = B110;
    break;
  case     134 : baudr = B134;
    break;
  case     150 : baudr = B150;
    break;
  case     200 : baudr = B200;
    break;
  case     300 : baudr = B300;
    break;
  case     600 : baudr = B600;
    break;
  case    1200 : baudr = B1200;
    break;
  case    1800 : baudr = B1800;
    break;
  case    2400 : baudr = B2400;
    break;
  case    4800 : baudr = B4800;
    break;
  case    9600 : baudr = B9600;
    break;
  case   19200 : baudr = B19200;
    break;
  case   38400 : baudr = B38400;
    break;
  case   57600 : baudr = B57600;
    break;
  case  115200 : baudr = B115200;
    break;
  case  230400 : baudr = B230400;
    break;
  case  460800 : baudr = B460800;
    break;
  case  500000 : baudr = B500000;
    break;
  case  576000 : baudr = B576000;
    break;
  case  921600 : baudr = B921600;
    break;
  case 1000000 : baudr = B1000000;
    break;
  case 1152000 : baudr = B1152000;
    break;
  case 1500000 : baudr = B1500000;
    break;
  case 2000000 : baudr = B2000000;
    break;
  case 2500000 : baudr = B2500000;
    break;
  case 3000000 : baudr = B3000000;
    break;
#ifndef __CYGWIN__
  case 3500000 : baudr = B3500000;
    break;
  case 4000000 : baudr = B4000000;
    break;
#endif
  default      : printf("invalid baudrate\n");
    return(-1);
    break;
  }

  int cbits=CS8,
    cpar=0,
    ipar=IGNPAR,
    bstop=0;
  
  if (strlen(mode) != 3) {
    printf("invalid mode \"%s\"\n", mode);
    return(-1);
  }
  
  switch (mode[0]) {
  case '8': cbits = CS8;
    break;
  case '7': cbits = CS7;
    break;
  case '6': cbits = CS6;
    break;
  case '5': cbits = CS5;
    break;
  default : printf("invalid number of data-bits '%c'\n", mode[0]);
    return(-1);
    break;
  }
  
  switch (mode[1]) {
  case 'N':
  case 'n': cpar = 0;
    ipar = IGNPAR;
    break;
  case 'E':
  case 'e': cpar = PARENB;
    ipar = INPCK;
    break;
  case 'O':
  case 'o': cpar = (PARENB | PARODD);
    ipar = INPCK;
    break;
  default : printf("invalid parity '%c'\n", mode[1]);
    return(-1);
    break;
  }

  switch (mode[2]) {
  case '1': bstop = 0;
    break;
  case '2': bstop = CSTOPB;
    break;
  default : printf("invalid number of stop bits '%c'\n", mode[2]);
    return(-1);
    break;
  }

  int serial_fd = open(serial_device, O_RDWR | O_NOCTTY | O_NDELAY);
  if(serial_fd == -1) {
    perror("unable to open comport ");
    return(-1);
  }
  
  /* lock access so that another process can't also use the port */
  if(flock(serial_fd, LOCK_EX | LOCK_NB) != 0) {
    close(serial_fd);
    perror("Another process has locked the comport.");
    return(-1);
  }

  tty_error = tcgetattr(serial_fd, &old_port_settings);
  if (tty_error==-1) {
    close(serial_fd);
    flock(serial_fd, LOCK_UN);  /* free the port so that others can use it. */
    perror("unable to read portsettings ");
    return(-1);
  }
  memset(&new_port_settings, 0, sizeof(new_port_settings));  /* clear the new struct */
  
  new_port_settings.c_cflag = cbits | cpar | bstop | CLOCAL | CREAD;
  new_port_settings.c_iflag = ipar;
  new_port_settings.c_oflag = 0;
  new_port_settings.c_lflag = 0;
  new_port_settings.c_cc[VMIN] = 1;      /* block untill n bytes are received */
  new_port_settings.c_cc[VTIME] = 0;     /* block untill a timer expires (n * 100 mSec.) */

  cfsetispeed(&new_port_settings, baudr);
  cfsetospeed(&new_port_settings, baudr);

  tty_error = tcsetattr(serial_fd, TCSANOW, &new_port_settings);
  if (tty_error==-1) {
    tcsetattr(serial_fd, TCSANOW, &old_port_settings);
    close(serial_fd);
    flock(serial_fd, LOCK_UN);  /* free the port so that others can use it. */
    perror("unable to adjust portsettings ");
    return(-1);
  }
  
  if(ioctl(serial_fd, TIOCMGET, &status) == -1) {
    tcsetattr(serial_fd, TCSANOW, &old_port_settings);
    flock(serial_fd, LOCK_UN);  /* free the port so that others can use it. */
    perror("unable to get portstatus");
    return(-1);
  }

  status |= TIOCM_DTR;    /* turn on DTR */
  status |= TIOCM_RTS;    /* turn on RTS */

  if(ioctl(serial_fd, TIOCMSET, &status) == -1) {
    tcsetattr(serial_fd, TCSANOW, &old_port_settings);
    flock(serial_fd, LOCK_UN);  /* free the port so that others can use it. */
    perror("unable to set portstatus");
    return(-1);
  }
  
  return(serial_fd);
}

/****************************************************************************
 * FUNCTION:
 ***************************************************************************/
int serial_read(int serial_fd,
		unsigned char *buf,
		int size)
{
  int n;
  
  n = read(serial_fd, buf, size);
  
  if(n < 0) {
    if(errno == EAGAIN)  return 0;
  }
  
  return(n);
}

/************** end of file ******************/
