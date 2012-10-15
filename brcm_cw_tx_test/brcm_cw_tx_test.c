/**
 *
 * Copyright (C) 2011 Broadcom Corporation.
 * 
 * This software is licensed under the terms of the GNU General Public License,
 * version 2, as published by the Free Software Foundation (the "GPL"), and may
 * be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GPL for more details.
 * 
 * A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php
 * or by writing to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */


/*****************************************************************************
**                                                                           
**  Name:          brcm_cw_tx_test.c
**
**  Description:   This program downloads a patchram files in the HCD format
**                 to Broadcom Bluetooth based silicon and combo chips and
**				   and other utility functions.
**
**                 It can be invoked from the command line in the form
**						<-d> to print a debug log
**						<--patchram patchram_file>
**						<--frequency freq>
**						<--mode mode>
**						<--type modulation_type>
**						uart_device_name
**
**		   The "freq" could be a single frequency number from 2402 to 2480     
**
**		   The "mode" could be:
**			0: Unmodulated
**			1: PRBS9
**			2: PRBS15002
**			3: All Zeros
**			4: All Ones
**			5: Incrementing Symbols
**
**		   The "modulation_type" could be:
**			0: GFSK
**			1: QFSK
**			2: 8FSK
**
**                 For example:
**
**                 brcm_cw_tx_test -d --patchram BCM4330B1.hcd \
**				--frequency 2402 --mode 2 --type 0 /dev/ttyHS0
**
**                 brcm_cw_tx_test -d --patchram BCM4330B1.hcd \
**				--frequency 2420 --mode 0 /dev/ttyHS0
**
**  
******************************************************************************/


#include <stdio.h>
#include <getopt.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>

#ifdef ANDROID
#include <termios.h>
#else
#include <sys/termios.h>
#endif

#include <string.h>
#include <signal.h>

//#include <cutils/properties.h>

#ifndef N_HCI
#define N_HCI	15
#endif

#define HCIUARTSETPROTO		_IOW('U', 200, int)
#define HCIUARTGETPROTO		_IOR('U', 201, int)
#define HCIUARTGETDEVICE	_IOR('U', 202, int)

#define HCI_UART_H4		0
#define HCI_UART_BCSP	1
#define HCI_UART_3WIRE	2
#define HCI_UART_H4DS	3
#define HCI_UART_LL		4


int uart_fd = -1;
int hcdfile_fd = -1;
int debug = 0;

int frequency = 0; 
int ch20_mode = 0;
unsigned int ch20_00 = 0;
unsigned int ch20_01 = 0;
unsigned int ch20_02 = 0;

struct termios termios;
unsigned char buffer[1024];

unsigned char hci_reset[] = { 0x01, 0x03, 0x0c, 0x00 };

unsigned char hci_download_minidriver[] = { 0x01, 0x2e, 0xfc, 0x00 };

unsigned char hci_set_tx_carrier_freq[] = { 0x01, 0x14, 0xfc, 0x07, 
       	0x00,	// carrier on
       	0x00,	// frequency encoded
	0x00,	// mode
	0x00,	// type
       	0x09, 	// power level, specify power table index
	0x00,	// transmit power dBm
       	0x00,	// transmit power table index
};

unsigned char hci_super_poke[] = { 0x01, 0x0a, 0xfc, 0x09, 0x05,
       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };	

unsigned char hci_super_peek[] = { 0x01, 0x0a, 0xfc, 0x05, 0x04,
       0x00, 0x00, 0x00, 0x00 };

int
parse_patchram(char *optarg)
{
	char *p;

	if (!(p = strrchr(optarg, '.'))) {
		fprintf(stderr, "file %s not an HCD file\n", optarg);
		exit(3);
	}

	p++;

	if (strcasecmp("hcd", p) != 0) {
		fprintf(stderr, "file %s not an HCD file\n", optarg);
		exit(4);
	}

	if ((hcdfile_fd = open(optarg, O_RDONLY)) == -1) {
		fprintf(stderr, "file %s could not be opened, error %d\n", optarg, errno);
		exit(5);
	}

	return(0);
}


int
parse_frequency(char *optarg)
{
	frequency = atoi(optarg);
	if ((frequency >= 2402) && (frequency <=2480)) {
		hci_set_tx_carrier_freq[5] = frequency - 2400;	// frequency
	}
	else {
		fprintf(stderr, "frequency parameter [%s] could not be recognized.\n", optarg);
		exit(6);
	}

	return(0);
}

int
parse_mode(char *optarg)
{
	int mode;

	mode = atoi(optarg);
	if ((mode >=0) && (mode <=5)) {
		hci_set_tx_carrier_freq[6] = mode;
	}
	else {
		fprintf(stderr, "mode parameter [%s] could not be recognized.\n", optarg);
		exit(7);
	}

	return (0);
}

int
parse_type(char *optarg)
{
	int type;

	type = atoi(optarg);
	if ((type>=0) && (type<=2)) {
		hci_set_tx_carrier_freq[7] = type;
	}
	else {
		fprintf(stderr, "type parameter [%s] could not be recognized.\n", optarg);
		exit(7);
	}

	return (0);
}



int
parse_cmd_line(int argc, char **argv)
{
	int c;
	int digit_optind = 0;

	typedef int (*PFI)();

	PFI parse_param[] = { parse_patchram, parse_frequency,
		parse_mode, parse_type};

    while (1)
    {
    	int this_option_optind = optind ? optind : 1;
        int option_index = 0;

       	static struct option long_options[] = {
         {"patchram", 1, 0, 0},
         {"frequency", 1, 0, 0},
         {"mode", 1, 0, 0},
         {"type", 1, 0, 0},
         {0, 0, 0, 0}
       	};

       	c = getopt_long_only (argc, argv, "d", long_options, &option_index);

       	if (c == -1) {
      		break;
		}

       	switch (c) {
        case 0:
        	printf ("option %s", long_options[option_index].name);

        	if (optarg) {
           		printf (" with arg %s", optarg);
			}

           	printf ("\n");

			(*parse_param[option_index])(optarg);
		break;

		case 'd':
			debug = 1;
		break;

        case '?':
			//nobreak
        default:

			printf("Usage %s:\n", argv[0]);
			printf("\t<-d> to print a debug log\n");
			printf("\t<--patchram patchram_file>\n");
			printf("\t<--frequency freq_num>\n");
			printf("\t<--mode mode>\n");
			printf("\t<--type modulation_type>\n");
			printf("\tuart_device_name\n");
           	break;

        }
	}

   	if (optind < argc) {
       	if (optind < argc) {
       		printf ("%s ", argv[optind]);

			if ((uart_fd = open(argv[optind], O_RDWR | O_NOCTTY)) == -1) {
				fprintf(stderr, "port %s could not be opened, error %d\n", argv[2], errno);
			}
		}

       	printf ("\n");
    }

	return(0);
}

void
init_uart()
{
	tcflush(uart_fd, TCIOFLUSH);
	tcgetattr(uart_fd, &termios);

#ifndef __CYGWIN__
	cfmakeraw(&termios);
#else
	termios.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                | INLCR | IGNCR | ICRNL | IXON);
	termios.c_oflag &= ~OPOST;
	termios.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	termios.c_cflag &= ~(CSIZE | PARENB);
	termios.c_cflag |= CS8;
#endif

	termios.c_cflag |= CRTSCTS;
	tcsetattr(uart_fd, TCSANOW, &termios);
	tcflush(uart_fd, TCIOFLUSH);
	tcsetattr(uart_fd, TCSANOW, &termios);
	tcflush(uart_fd, TCIOFLUSH);
	tcflush(uart_fd, TCIOFLUSH);
	cfsetospeed(&termios, B115200);
	cfsetispeed(&termios, B115200);
	tcsetattr(uart_fd, TCSANOW, &termios);
}

void
dump(unsigned char *out, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		if (i && !(i % 16)) {
			fprintf(stderr, "\n");
		}

		fprintf(stderr, "%02x ", out[i]);
	}

	fprintf(stderr, "\n");
}

void
read_event(int fd, unsigned char *buffer)
{
	int i = 0;
	int len = 3;
	int count;

	while ((count = read(fd, &buffer[i], len)) < len) {
		i += count;
		len -= count;
	}

	i += count;
	len = buffer[2];

	while ((count = read(fd, &buffer[i], len)) < len) {
		i += count;
		len -= count;
	}

	if (debug) {
		count += i;

		fprintf(stderr, "received %d\n", count);
		dump(buffer, count);
	}
}

void
hci_send_cmd(unsigned char *buf, int len)
{
	if (debug) {
		fprintf(stderr, "writing\n");
		dump(buf, len);
	}

	write(uart_fd, buf, len);
}

void
expired(int sig)
{
	hci_send_cmd(hci_reset, sizeof(hci_reset));
	alarm(4);
}

void
proc_reset()
{
	signal(SIGALRM, expired);


	hci_send_cmd(hci_reset, sizeof(hci_reset));

	alarm(4);

	read_event(uart_fd, buffer);

	alarm(0);
}

void
proc_patchram()
{
	int len;

	hci_send_cmd(hci_download_minidriver, sizeof(hci_download_minidriver));

	read_event(uart_fd, buffer);

	usleep(50000);

	while (read(hcdfile_fd, &buffer[1], 3)) {
		buffer[0] = 0x01;

		len = buffer[3];

		read(hcdfile_fd, &buffer[4], len);

		hci_send_cmd(buffer, len + 4);

		read_event(uart_fd, buffer);
	}

	proc_reset();
}


void
proc_set_tx_carrier_freq()
{
	hci_send_cmd(hci_set_tx_carrier_freq, sizeof(hci_set_tx_carrier_freq));

	read_event(uart_fd, buffer);
}


void
proc_super_poke(unsigned int addr, unsigned int value)
{
	hci_super_poke[5] = (addr & 0xFF);
	hci_super_poke[6] = ((addr >> 8) & 0xFF);
	hci_super_poke[7] = ((addr >> 16) & 0xFF);
	hci_super_poke[8] = ((addr >> 24) & 0xFF);
	hci_super_poke[9] = (value & 0xFF);
	hci_super_poke[10] = ((value>> 8) & 0xFF);
	hci_super_poke[11] = ((value>> 16) & 0xFF);
	hci_super_poke[12] = ((value>> 24) & 0xFF);

	hci_send_cmd(hci_super_poke, sizeof(hci_super_poke));

	read_event(uart_fd, buffer);
}


unsigned char
proc_super_peek(unsigned int addr)
{
	hci_super_peek[5] = (addr & 0xFF);
	hci_super_peek[6] = ((addr >> 8) & 0xFF);
	hci_super_peek[7] = ((addr >> 16) & 0xFF);
	hci_super_peek[8] = ((addr >> 24) & 0xFF);

	hci_send_cmd(hci_super_peek, sizeof(hci_super_peek));

	read_event(uart_fd, buffer);

	if (buffer[6] != 0x0) {
		fprintf(stderr, "super_peek %x failed.\n", addr);
		exit(8);
	}	

	return buffer[7];
}

int
main (int argc, char **argv)
{
	unsigned char value;
	int read_data = 0;

	parse_cmd_line(argc, argv);

	if (uart_fd < 0) {
		exit(1);
	}

	init_uart();

	proc_reset();

	if (hcdfile_fd > 0) {
		proc_patchram();
	}

	if (hci_set_tx_carrier_freq[6] == 0) 
		hci_set_tx_carrier_freq[7] = 0; // if unmodulation mode, then set type to zero

	proc_set_tx_carrier_freq();

	fprintf(stderr, "finished.\n");
	exit(0);
}
