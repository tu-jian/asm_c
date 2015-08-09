void printch(char ch)
{
//	console_print(ch);
//	putchar(ch);
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

#define next_arg(vp, type)	(*(type*)(vp += sizeof(int)))
void print(char* fmt, ...)
{
	int  varint;
	char* varpch;
	char* pfmt;
	char* vp;

	vp = (char*)(&fmt);
	pfmt = fmt;

	while(*pfmt) {
		if(*pfmt == '%') {
			switch(*(++pfmt)) {

			case 'c':
				varint = next_arg(vp, int);
				printch(varint);
				break;
			case 'd':
				varint = next_arg(vp, int);
				printdec(varint);
				break;
			case 's':
				varpch = next_arg(vp, char*);
				printstr(varpch);
				break;
			case 'x':
				varint = next_arg(vp, int);
				printhex(varint);
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
}

int main(void)
{
	print("print: %c:%d:%s\n", 'c', 123, "abcd");
	print("print: %d\n", 1234567);
	print("print: %s\n", "string test");
	print("print: %x\n", 0xabcdef);
	print("print: %%\n");
	return 0;
}
