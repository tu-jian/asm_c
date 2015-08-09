#include <stdio.h>
#include <stdarg.h>

void printch(char ch)
{
//	console_print(ch);
	putchar(ch);
}

void printdec(int dec)
{
	if(dec==0) {
		return;
	}
	printdec(dec/10);
	printch( (char)(dec%10 + '0'));
}

void printstr(char* str)
{
	while(*str) {
		printch(*str++);
	}
}

void printhex(int hex)
{
	if(hex==0) {
		printstr("0x");
		return;
	}
	printhex(hex/16);
	if(hex < 10) {
		printch((char)(hex%16 + '0'));
	} else {
		printch((char)(hex%16 - 10 + 'a' ));
	}
}

void print(char* fmt, ...)
{
	int  vargint = 0;
	char* vargpch = NULL;
	char vargch = 0;
	char* pfmt = NULL;
	va_list vp;

	va_start(vp, fmt);
	pfmt = fmt;

	while(*pfmt) {
		if(*pfmt == '%') {
			switch(*(++pfmt)) {

			case 'c':
				vargch = va_arg(vp, int);
				/*    va_arg(ap, type), if type is narrow type (char, short, float) an error is given in strict ANSI
				mode, or a warning otherwise.In non-strict ANSI mode, 'type' is allowed to be any expression. */
				printch(vargch);
				break;
			case 'd':
				vargint = va_arg(vp, int);
				printdec(vargint);
				break;
			case 's':
				vargpch = va_arg(vp, char*);
				printstr(vargpch);
				break;
			case 'x':
				vargint = va_arg(vp, int);
				printhex(vargint);
				break;
			case '%':
				printch('%');
				break;
			default:
				break;
			}
			pfmt++;
		} else {
			printch(*pfmt++);
		}
	}
	va_end(vp);
}

int main(void)
{
	print("print: %c\n", 'c');
	print("print: %d\n", 1234567);
	print("print: %s\n", "string test");
	print("print: %x\n", 0xabcdef);
	print("print: %%\n");
	return 0;
}
