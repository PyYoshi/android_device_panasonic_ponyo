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
**  Name:          brcm_afh_tx_test.c
**
**  Description:   This program downloads a patchram files in the HCD format
**                 to Broadcom Bluetooth based silicon and combo chips and
**				   and other utility functions.
**
**                 It can be invoked from the command line in the form
**						<-d> to print a debug log
**						<--patchram patchram_file>
**						<--bd_addr bd_address>
**						<--frequency freq>
**						<--pkttype type>
**						uart_device_name
**
**		   The "freq" could be:
**			h: Hopping 
**			20l: 20 ch hopping - lower freq block
**			20m: 20 ch hopping - middle freq block
**			20h: 20 ch hopping - higher freq block
**			or a single frequency number from 2402 to 2490     
**
**		   The "type" could be:
**			1: DH1   
**			2: DH3   
**			3: DH5 
**			4: 2-DH1
**			5: 2-DH3
**			6: 2-DH5
**			7: 3-DH1
**			8: 3-DH3
**			9: 3-DH5
**
**                 For example:
**
**                 brcm_afh_tx_test -d --patchram BCM4330B1.hcd \
**				--frequency 20l --pkttype 2 /dev/ttyHS0
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

unsigned char hci_tx_test[] = { 0x01, 0x51, 0xfc, 0x10, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // local bd address
       	0x00,	// hopping mode
       	0x00,	// frequency
       	0x04,	// modulation type, "PRBS9 pattern"
       	0x00,	// logical channel
	0x00,	// packet type
       	0x00,  	// packet length
       	0x00,
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
	if (strcasecmp("h", optarg) == 0) {
		hci_tx_test[10] = 0x00; 		// hopping mode: 79 channels
	}
	else if (strcasecmp("20l", optarg) == 0) {
		ch20_mode = 1; 
		ch20_00 = 0x000FFFFF;
		ch20_01 = 0x00000000;
		ch20_02 = 0x00000000;

	}
	else if (strcasecmp("20m", optarg) == 0) {
		ch20_mode = 1; 
		ch20_00 = 0xC0000000;
		ch20_01 = 0x0003FFFF;
		ch20_02 = 0x00000000;

	}
	else if (strcasecmp("20h", optarg) == 0) {
		ch20_mode = 1; 
		ch20_00 = 0x00000000;
		ch20_01 = 0xF8000000;
		ch20_02 = 0x00007FFF;
	}
	else {
		frequency = atoi(optarg);
		if ((frequency >= 2402) && (frequency <=2480)) {
			hci_tx_test[10] = 0x01; 		// hopping mode: single frequency
			hci_tx_test[11] = frequency - 2402;	// frequency
		}
		else {
			fprintf(stderr, "frequency parameter [%s] could not be recognized.\n", optarg);
			exit(6);
		}
	}

	return(0);
}

int
parse_bdaddr(char *optarg)
{
	int bd_addr[6];
	int i;

	sscanf(optarg, "%02X:%02X:%02X:%02X:%02X:%02X",
		&bd_addr[5], &bd_addr[4], &bd_addr[3],
		&bd_addr[2], &bd_addr[1], &bd_addr[0]);

	for (i = 0; i < 6; i++) {
		hci_tx_test[4 + i] = bd_addr[i];
	}

	return(0);
}

int
parse_pkttype(char *optarg)
{
	int pkt_len;
	int pkt_type;

	pkt_type = atoi(optarg);
	switch (pkt_type) {
	case 1:
		hci_tx_test[13] = 0x01;	// ACL Basic
		hci_tx_test[14] = 0x04;	// DH1 / 2-DH1
		pkt_len = 27;
		break;
	case 2:
		hci_tx_test[13] = 0x01;	// ACL Basic
		hci_tx_test[14] = 0x0B;	// DH3 / 3-DH3
		pkt_len = 183;
		break;
	case 3:
		hci_tx_test[13] = 0x01;	// ACL Basic
		hci_tx_test[14] = 0x0F;	// DH5 / 3-DH5
		pkt_len = 339;
		break;
	case 4:
		hci_tx_test[13] = 0x00;	// ACL EDR 
		hci_tx_test[14] = 0x04;	// DH1 / 2-DH1
		pkt_len = 54;
		break;
	case 5:
		hci_tx_test[13] = 0x00;	// ACL EDR 
		hci_tx_test[14] = 0x0A;	// DM3 / 2-DH3
		pkt_len = 367;
		break;
	case 6:
		hci_tx_test[13] = 0x00;	// ACL EDR 
		hci_tx_test[14] = 0x0E;	// DM5 / 2-DH5
		pkt_len = 679;
		break;
	case 7:
		hci_tx_test[13] = 0x00;	// ACL EDR 
		hci_tx_test[14] = 0x08;	// DV / 3-DH1
		pkt_len = 83;
		break;
	case 8:
		hci_tx_test[13] = 0x00;	// ACL EDR 
		hci_tx_test[14] = 0x0B;	// DH3 / 3-DH3
		pkt_len = 552;
		break;
	case 9:
		hci_tx_test[13] = 0x00;	// ACL EDR 
		hci_tx_test[14] = 0x0F;	// DH5 / 3-DH5
		pkt_len = 1021;
		break;
	default:
		fprintf(stderr, "packet type parameter [%s] could not be recognized.\n", optarg);
		exit(7);
	}

	hci_tx_test[15] = (pkt_len & 0xFF);
	hci_tx_test[16] = ((pkt_len>>8) & 0xFF);
        return 0;
}


int
parse_cmd_line(int argc, char **argv)
{
	int c;
	int digit_optind = 0;

	typedef int (*PFI)();

	PFI parse_param[] = { parse_patchram, parse_frequency,
		parse_bdaddr, parse_pkttype};

    while (1)
    {
    	int this_option_optind = optind ? optind : 1;
        int option_index = 0;

       	static struct option long_options[] = {
         {"patchram", 1, 0, 0},
         {"frequency", 1, 0, 0},
         {"bd_addr", 1, 0, 0},
         {"pkttype", 1, 0, 0},
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
			printf("\t<--bd_addr bd_address>\n");
			printf("\t<--pkttype packet_type\n");
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
proc_tx_test()
{
	hci_send_cmd(hci_tx_test, sizeof(hci_tx_test));

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

	proc_tx_test();

	if (ch20_mode == 1) {
		read_data = 0;

		proc_super_poke(0x003186B0, ch20_00);
		proc_super_poke(0x003186B4, ch20_01);
		proc_super_poke(0x003186B8, ch20_02);

		value = proc_super_peek(0x00318628);
		read_data |= (value);
		value = proc_super_peek(0x00318629);
		read_data |= (value << 8);
		value = proc_super_peek(0x0031862A);
		read_data |= (value << 16);
		value = proc_super_peek(0x0031862B);
		read_data |= (value << 24);

		proc_super_poke(0x00318628, read_data ^ 0x01);

		proc_super_poke(0x00318638, 20);

		read_data = 0;

		value = proc_super_peek(0x00318620);
		read_data |= (value);
		value = proc_super_peek(0x00318621);
		read_data |= (value << 8);
		value = proc_super_peek(0x00318622);
		read_data |= (value << 16);
		value = proc_super_peek(0x00318623);
		read_data |= (value << 24);

		proc_super_poke(0x00318620, read_data ^ 0x01);
	}

	fprintf(stderr, "finished.\n");
	exit(0);
}
