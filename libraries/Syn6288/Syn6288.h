#ifndef SYN6288_H_
#define SYN6288_H_
#define uchar unsigned char
#define HEAD_LEN 5
#define BKM_MAX 5

class Syn6288
{
	public:
	Syn6288();
	void Speech(const char * txt,uchar bkm,uchar port);
	void Speech(const char * txt,uchar bkm);
	void Speech(const char * txt);
	private:
	uchar _nPort;
	uchar _nBkm;
};

#endif
