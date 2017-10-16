#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Xm/XmAll.h>
#include "impdef.h"
typedef struct tagW {
	Widget inputBox;
	Widget binLabel8;
	Widget binLabel16;
	Widget binLabel32;
	Widget binLabel64;
	Widget settyText8;
	Widget settyText16;
	Widget settyText32;
	Widget settyText64;
}WIDGET_LIST;


typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned long long int qword;
#define BitSize8  (sizeof(byte) * 8) 
#define BitSize16  (sizeof(word) * 8) 
#define BitSize32  (sizeof(dword) * 8) 
#define BitSize64  (sizeof(qword) * 8) 

static void Button_callback();
byte mk_mask8(const char*);
word mk_mask16(const char*);
dword mk_mask32(const char*);
qword mk_mask64(const char*);
void dtob(qword, size_t, char*);
void setty(WIDGET_LIST*, const char*);
int exec_direct(const char*, const char*);


// リソースの定義
static char *fallback_resource[] = {
    "*fontList:         -misc-fixed-medium-r-normal--14-*-*-*-*-*-*-*:",
    "*title:            BMP",
    "*label.labelString: カソマ区切りで入れてね",
	"*geometry: +100+100",
    NULL
};

int show_usage(void)
{
	puts("usage: bmp.exe [bdh][sil] digit");
	return -1;
}


	
int 
main(argc, argv)
	int argc;
	char **argv;
{
    XtAppContext app_context;
    WIDGET_LIST* gdgd;
	Widget toplevel, panel, control, label;
    Arg al[20];
    int ac;
	
	if (argc == 3) {
		return exec_direct(argv[1], argv[2]);
	}

	gdgd = (WIDGET_LIST*)malloc(sizeof(WIDGET_LIST));

    XtSetLanguageProc( NULL, NULL, NULL);

    ac = 0;
    toplevel=XtAppInitialize( &app_context, "test", NULL, 0,
            &argc, argv, fallback_resource , al, ac);
    ac = 0;
    panel = XmCreateRowColumn( toplevel, "panel", al, ac);
    XtManageChild(panel);
    
	ac = 0;
    control = XmCreateRowColumn( panel, "control", al, ac);
    XtManageChild(control);
    
	ac = 0;
    label = XmCreateLabel( control, "label", al, ac);
    XtManageChild(label);
    
	ac = 0;
    gdgd->inputBox = XmCreateTextField(control, "inputBox", al, ac);
    XtManageChild(gdgd->inputBox);

	ac = 0;
    gdgd->binLabel8 = XmCreateLabel(panel,"binDisp8", al, ac);
    XtManageChild(gdgd->binLabel8);

	ac = 0;
	gdgd->binLabel16 = XmCreateLabel(panel,"binDisp16", al, ac);
    XtManageChild(gdgd->binLabel16);

	ac = 0;
    gdgd->binLabel32 = XmCreateLabel(panel,"binDisp32", al, ac);
    XtManageChild(gdgd->binLabel32);

	ac = 0;
	gdgd->binLabel64 = XmCreateLabel(panel,"binDisp64", al, ac);
    XtManageChild(gdgd->binLabel64);
      
	ac = 0;
    gdgd->settyText8 = XmCreateTextField(panel,"settyText8", al, ac);
    XtManageChild(gdgd->settyText8);

	ac = 0;
    gdgd->settyText16 = XmCreateTextField(panel,"settyText16", al, ac);
    XtManageChild(gdgd->settyText16);

	ac = 0;
    gdgd->settyText32 = XmCreateTextField(panel,"settyText32", al, ac);
    XtManageChild(gdgd->settyText32);

	ac = 0;
	gdgd->settyText64 = XmCreateTextField(panel,"settyText64", al, ac);
    XtManageChild(gdgd->settyText64);

	setty(gdgd, "");
	XtAddCallback(gdgd->inputBox , XmNmodifyVerifyCallback, Button_callback, (void*)gdgd);

    XtRealizeWidget(toplevel);
    XtAppMainLoop(app_context);
    return 0;
}

void 
setty(w, str) 
	WIDGET_LIST *w;
	const char* str;
{
	Arg args[10];
	int argNum = 0;
	XmString tmpStr;
	char bitstr[BitSize64 + 1];
	qword bytes;

	// 8
	bytes = mk_mask8(str);
	dtob(bytes, BitSize8, bitstr);

	argNum = 0;
	tmpStr = XmStringCreateLocalized((String)bitstr);
	XtSetArg(args[argNum], XmNlabelString, (XtArgVal)tmpStr); argNum++;
	XtSetValues(w->binLabel8, args, argNum);
	XmStringFree(tmpStr);

	snprintf(bitstr, sizeof(bitstr), "0x%02x", bytes);

	argNum = 0;
	XtSetArg(args[argNum], XmNvalue, (XtArgVal)bitstr); argNum++;
	XtSetValues(w->settyText8, args, argNum);

	fprintf(stderr, "8: 0x%02llx\n", bytes);


	// 16
	bytes = mk_mask16(str);
	dtob(bytes, BitSize16, bitstr);

	argNum = 0;
	tmpStr = XmStringCreateLocalized((String)bitstr);
	XtSetArg(args[argNum], XmNlabelString, (XtArgVal)tmpStr); argNum++;
	XtSetValues(w->binLabel16, args, argNum);
	XmStringFree(tmpStr);

	snprintf(bitstr, sizeof(bitstr), "0x%04x", bytes);

	argNum = 0;
	XtSetArg(args[argNum], XmNvalue, (XtArgVal)bitstr); argNum++;
	XtSetValues(w->settyText16, args, argNum);

	fprintf(stderr, "16: 0x%04llx\n", bytes);


	// 32
	bytes = mk_mask32(str);
	dtob(bytes, BitSize32, bitstr);

	argNum = 0;
	tmpStr = XmStringCreateLocalized((String)bitstr);
	XtSetArg(args[argNum], XmNlabelString, (XtArgVal)tmpStr); argNum++;
	XtSetValues(w->binLabel32, args, argNum);
	XmStringFree(tmpStr);

	snprintf(bitstr, sizeof(bitstr), "0x%08x", bytes);

	argNum = 0;
	XtSetArg(args[argNum], XmNvalue, (XtArgVal)bitstr); argNum++;
	XtSetValues(w->settyText32, args, argNum);

	fprintf(stderr, "32: 0x%08llx\n", bytes);

	// 64
	bytes = mk_mask64(str);
	dtob(bytes, BitSize64, bitstr);

	argNum = 0;
	tmpStr = XmStringCreateLocalized((String)bitstr);
	XtSetArg(args[argNum], XmNlabelString, (XtArgVal)tmpStr); argNum++;
	XtSetValues(w->binLabel64, args, argNum);
	XmStringFree(tmpStr);

	snprintf(bitstr, sizeof(bitstr), "0x%016llx", bytes);

	argNum = 0;
	XtSetArg(args[argNum], XmNvalue, (XtArgVal)bitstr); argNum++;
	XtSetValues(w->settyText64, args, argNum);
	
	fprintf(stderr, "64: 0x%016llx\n", bytes);
}


//コールバック
static void 
Button_callback(w, client_data, call_data)
	Widget w;
	XtPointer client_data; 
	XtPointer call_data;
{
    WIDGET_LIST* gdgd = (WIDGET_LIST*)client_data;
	XmTextVerifyCallbackStruct* info = (XmTextVerifyCallbackStruct*)call_data;
    char *str;

    // テキストフィールドの内容を取得する
    str = XmTextFieldGetString(gdgd->inputBox);
	if (info->text->length > 0) {	
		//printf("m=%s\n", info->text->ptr);
		if (',' == str[strlen(str)-1] || ',' == info->text->ptr[0]) {
			setty(gdgd, str);
		}
	}
    XtFree(str);
}

void 
dtob(x, BitSize, out)
	qword x;  
	size_t BitSize;
	char* out;
{
    qword bit = 1;
    int  i;  
	char* p;
	char* c;
	char bmp[BitSize64];
	
	p = bmp;
    for (i = 0; i < BitSize; i++) {
        *(p++) = (x & bit) ? '1' : '0';
        bit <<= 1;
    } 
	*(++p)=0;
	
	c = out;
	p = bmp;
    for ( i = BitSize - 1; i >= 0; i-- ) { 
        //printf("%c", c[i]);
        *(c++) = p[i];
		if (0 == ( i % 4)) {
			*(c++) = 0x20;
		}
    } 
	*(c)=0;
    
	//printf("%s\n", c);
}

byte
mk_mask8(arg)
	const char* arg;
{
    qword i = mk_mask64(arg);
	return i & 0xff;
}

word
mk_mask16(arg)
	const char* arg;
{
    qword i = mk_mask64(arg);
	return i & 0xffff;
}

dword
mk_mask32(arg)
	const char* arg;
{
    qword i = mk_mask64(arg);
	return i & 0xffffffff;
}

#define MASKL 0xff
#define MASKU 0xff
qword
mk_mask64(arg)
	const char* arg;
{
    dword l, u, tok;
    char* saveptr = NULL;
    char* word = NULL;
	char buffer[1024];

	
	strncpy(buffer, arg, sizeof(buffer));

	l = u = tok = 0;
    
    word = strtok_r(buffer, ",", &saveptr);
    while(NULL != word) {
        tok = strtoul(word, NULL, 10);
		if (tok <= 32) {
			tok -= 1;
			l |= (1 << (tok & MASKL));
		}
		else {
			tok -= 33;
			u |= (1 << (tok & MASKU));
		}

//        printf("W=%s<%d>(upper:%08x lower:%08x)\n", word, (tok & MASKL), u, l);
        word = strtok_r(NULL, ",", &saveptr);
    }

	printf("upper=%08x lower=%08x\n", u, l);
	return (qword)((l) | ((qword)u) << 32) ;
}

int 
exec_direct(_rad, _dig)
	const char *_rad;
	const char *_dig;
{
	size_t bits;
	int radix;
	qword digit;
	const char* op;
	char hqx[256];
	char is_swap;

	op = _rad;

	switch(*op) {
		case 'b':
			radix = 2;
			break;
		case 'd':
			radix = 10;
			break;
		case 'h':
			radix = 16;
			break;
		default:
			return show_usage();
	}

	switch(*(++op)) {
		case 's':
			bits = BitSize16;
			break;
		case 'i':
			bits = BitSize32;
			break;
		case 'l':
			bits = BitSize64;
			break;
		default:
			return show_usage();
	}

	switch(*(++op)) {
		case 'r':
			is_swap = 1;
			break;
		defult:
			is_swap = 0;
			break;
	}

	digit = strtoull(_dig, NULL, radix);
	if (is_swap) {
		digit = SWAP64(digit);
	}
	dtob(digit, bits, hqx);
	
	switch(bits) {
		case BitSize16:
			fprintf(stderr, "L %d = %04x\n", digit & 0xffff, digit & 0xffff);
			fprintf(stderr, "B %d = %04x\n", (digit & 0xffff), SWAP16(digit & 0xffff));
			break;
		case BitSize32:
			fprintf(stderr, "L %d = %08x\n", digit & 0xffffffff, digit & 0xffffffff);
			fprintf(stderr, "B %d = %08x\n", (digit & 0xffffffff), SWAP32(digit & 0xffffffff));
			break;
		default:
			fprintf(stderr, "L %lld = %16lx\n", digit, digit);
			fprintf(stderr, "B %lld = %16lx\n", (digit), SWAP64(digit));
			break;
	}
	fprintf(stderr, "%s\n", hqx);

	return 0;
}

