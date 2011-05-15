#include "gpio.h"

FILE *fp;

int config_gpio_pin(status_gpio *status, const char *dir, char *pinN)
{
	char gpio_path[30];
	char len_dir = strlen(dir);
	char len_pinN = strlen(pinN);

	strcpy(gpio_path, "/sys/class/gpio/gpio");
	strcat(gpio_path, pinN); 
	strcat(gpio_path, "/direction");
	
	if ((fp = fopen("/sys/class/gpio/export", "ab")) == NULL)
		return -1;
	rewind(fp);	/*Set pointer to begining of the file*/
	fwrite(pinN, sizeof(char), len_pinN, fp); /*Write number pin to the file*/
	fclose(fp);	
	
	if ((fp = fopen(gpio_path, "rb+")) == NULL) /*file in binary for reading and writing*/
		return -1;
	rewind(fp);	/*Set pointer to begining of the file*/
	fwrite(dir, sizeof(char), len_dir, fp); /*Write "out" or "in" to the file*/
	fclose(fp);

	status->direction = *dir;
	return 0;		
}
	
int read_gpio_pin(status_gpio *status, char *pinN)
{
	char gpio_value;
	char gpio_path[30];
	strcpy(gpio_path, "/sys/class/gpio/gpio");
	strcat(gpio_path, pinN); 
	strcat(gpio_path, "/value");
		
	if ((fp = fopen(gpio_path, "rb")) == NULL) /*file in binary for reading only*/
		return -1;
		
	rewind(fp);	/*Set pointer to begining of the file*/
	fread(&gpio_value, sizeof(char), 1, fp); /*Value read of the file*/
	fclose(fp);
	
	status->value = gpio_value;
	return 0;	
}
	
int set_gpio_pin(status_gpio *status, char *pinN)
{
	char gpio_path[30];
	
	if(status->direction == 'i') {printf("Error: GPIO input can't be set\n"); return -1;}
	strcpy(gpio_path, "/sys/class/gpio/gpio");
	strcat(gpio_path, pinN); 
	strcat(gpio_path, "/value");
		
	if ((fp = fopen(gpio_path, "rb+")) == NULL) /*file in binary for reading and writing*/
		return -1;
		
	rewind(fp);	/*Set pointer to begining of the file*/
	fwrite("1", sizeof(char), 1, fp); /*Write "1" to the file*/
	fclose(fp);
	
	status->value = '1';
	return 0;
}
	
int clear_gpio_pin(status_gpio *status, char *pinN)
{
	char gpio_path[30];
	
	if(status->direction == 'i') {printf("Error: GPIO input can't be cleaned\n"); return -1;}
	strcpy(gpio_path, "/sys/class/gpio/gpio");
	strcat(gpio_path, pinN); 
	strcat(gpio_path, "/value");
		
	if ((fp = fopen(gpio_path, "rb+")) == NULL) /*file in binary for reading and writing*/
		return -1;
		
	rewind(fp);	/*Set pointer to begining of the file*/
	fwrite("0", sizeof(char), 1, fp); /*Write "0" to the file*/
	fclose(fp);	
	
	status->value = '0';
	return 0;
}	
