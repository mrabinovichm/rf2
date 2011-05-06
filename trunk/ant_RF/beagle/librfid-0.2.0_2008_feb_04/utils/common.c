#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifndef __MINGW32__
#include <libgen.h>
#endif

#include <librfid/rfid.h>
#include <librfid/rfid_scan.h>
#include <librfid/rfid_reader.h>
#include <librfid/rfid_layer2.h>
#include <librfid/rfid_protocol.h>

#include <librfid/rfid_protocol_mifare_classic.h>
#include <librfid/rfid_protocol_mifare_ul.h>

#include "librfid-tool.h"
#include "common.h"

/*AGREGADO*/
#define ON  1
#define OFF 0
/*FIN AGREGADO*/

const char *
hexdump(const void *data, unsigned int len)
{
	static char string[1024];
	unsigned char *d = (unsigned char *) data;
	unsigned int i, left;

	string[0] = '\0';
	left = sizeof(string);
	for (i = 0; len--; i += 3) {
		if (i >= sizeof(string) -4)
			break;
		snprintf(string+i, 4, " %02x", *d++);
	}
	return string;
}

static char parse_hexdigit(const char hexdigit)
{
	if (hexdigit <= '9' && hexdigit >= '0')
		return hexdigit - '0';
	if (hexdigit <= 'f' && hexdigit >= 'a')
		return 10 + (hexdigit - 'a');

	return 0;
}

int
hexread(unsigned char *result, const unsigned char *in, unsigned int len)
{
	const unsigned char *pos;
	char dig1, dig2;
	unsigned char *res = result;

	for (pos = in; pos-in <= len-2; pos+=2) {
		if (*pos == ':')
			pos++;
		dig1 = *pos;
		dig2 = *(pos+1);

		*res++ = parse_hexdigit(dig1) << 4 | parse_hexdigit(dig2);
	}

	return (res - result);
}

/*AGREGADO*/
int reset_RC632(int turn)
{
	FILE *fd_rst;
	
	/*create a variable to store whether we are sending a '1' or a '0'*/
	char set_value[4]; 
	
	/*Using sysfs we need to write "168" to /sys/class/gpio/export
	This will create the folder /sys/class/gpio/gpio168*/
	if ((fd_rst = fopen("/sys/class/gpio/export", "ab")) == NULL)
	{
		printf("Cannot open export file.\n");
		return -1;
	}
	/*Set pointer to begining of the file*/
	rewind(fd_rst);
	/*Write our value of "168" to the file*/
	strcpy(set_value,"168");
	fwrite(&set_value, sizeof(char), 3, fd_rst);
	fclose(fd_rst);
	
	/*SET DIRECTION*/
	/*Open the LED's sysfs file in binary for reading and writing, store file pointer in fp*/
	if ((fd_rst = fopen("/sys/class/gpio/gpio168/direction", "rb+")) == NULL)
	{
		printf("Cannot open direction file.\n");
		return -1;
	}
	/*Set pointer to begining of the file*/
	rewind(fd_rst);
	/*Write our value of "out" to the file*/
	strcpy(set_value,"out");
	fwrite(&set_value, sizeof(char), 3, fd_rst);
	fclose(fd_rst);
		
	/*SET VALUE*/
	/*Open the LED's sysfs file in binary for reading and writing, store file pointer in fp*/
	if ((fd_rst = fopen("/sys/class/gpio/gpio168/value", "rb+")) == NULL)
	{
		printf("Cannot open value file.\n");
		return -1;
	}
	/*Set pointer to begining of the file*/
	rewind(fd_rst);
	
	/*Write our value of "valor" to the file*/
	if (turn)
		strcpy(set_value, "1");
	else
		strcpy(set_value, "0");

	fwrite(&set_value, sizeof(char), 1, fd_rst);
	fclose(fd_rst);
				
	return 0;
}
/*FIN AGREGADO*/

struct rfid_reader_handle *rh;
struct rfid_layer2_handle *l2h;
struct rfid_protocol_handle *ph;

int reader_init(void) 
{
	printf("opening reader handle OpenPCD, CM5x21\n");
	rh = rfid_reader_open(NULL, RFID_READER_OPENPCD);
	if (!rh) {
		fprintf(stderr, "No OpenPCD found\n");
		rh = rfid_reader_open(NULL, RFID_READER_CM5121);
		if (!rh) {
			fprintf(stderr, "No Omnikey Cardman 5x21 found\n");
			printf("opening reader handle SPIDEV\n");			
			reset_RC632(OFF); /*AGREGADO; OFF no resetea el RC632*/
			rh = rfid_reader_open("/dev/spidev3.0", RFID_READER_SPIDEV);
			if (!rh) {
				fprintf(stderr, "No SPIDEV found\n");
				return -1;
			}
		}
	}
	
	return 0;
}

int l2_init(int layer2)
{
	int rc;

	printf("opening layer2 handle\n");
	l2h = rfid_layer2_init(rh, layer2);
	if (!l2h) {
		fprintf(stderr, "error during layer2(%d)_init (0=14a,1=14b,3=15)\n",layer2);
		return -1;
	}

	printf("running layer2 anticol(_open)\n");
	rc = rfid_layer2_open(l2h);
	if (rc < 0) {
		fprintf(stderr, "error during layer2_open\n");
		return rc;
	}

	return 0;
}

int l3_init(int protocol)
{
	printf("running layer3 (ats)\n");
	ph = rfid_protocol_init(l2h, protocol);
	if (!ph) {
		fprintf(stderr, "error during protocol_init\n");
		return -1;
	}
	if (rfid_protocol_open(ph) < 0) {
		fprintf(stderr, "error during protocol_open\n");
		return -1;
	}

	printf("we now have layer3 up and running\n");

	return 0;
}

