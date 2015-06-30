#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "udpClient.h"
#include "util.h"

#define TICK_INTERVAL 20

static bool mIsInit = false;
static int mSockfd = -1000;
static int mSendNo;
static unsigned char mBuffer[300];
static struct sockaddr_in mServAddr;

int init(char *ip, int port)
{
	mSendNo = 0;
	memset(mBuffer, 0, sizeof(mBuffer));
	release();
	initSocket(ip, port);
	return mSockfd;
}

int release()
{
	mIsInit = false;
	if (mSockfd != -1000){
		close(mSockfd);
		mSockfd = -1000;
	}

	return mSockfd;
}

void initTimer()
{
	signal(SIGALRM, timeout);
	struct itimerval tv;
	tv.it_interval.tv_sec = 0;
	tv.it_interval.tv_usec = TICK_INTERVAL * 1000;
	tv.it_value.tv_sec = 0;
	tv.it_value.tv_usec = 1;
	setitimer(ITIMER_REAL, &tv, NULL); // not accurate
}

void stopTimer()
{
	 struct itimerval value;
	 value.it_value.tv_sec = 0;
	 value.it_value.tv_usec = 0;
	 value.it_interval = value.it_value;
	 setitimer(ITIMER_REAL, &value, NULL);
}

void timeout(int signal)
{
	switch (signal)
	{
	case SIGALRM:
		{
			memset(mBuffer, 0, 300);
			short lo = mSendNo % 65536;
			short hi = mSendNo / 65536;
			mBuffer[0] = lo % 256;
			mBuffer[1] = lo / 256;
			mBuffer[2] = hi % 256;
			mBuffer[3] = hi / 256;
			for (int i=0; i<100; i++)
			{
				mBuffer[i+4] = i+1;
			}

			int len = sendData(mBuffer, 104);
			mSendNo ++;
		}
		break;
	}
}

void initSocket(char *ip, int port)
{
	mIsInit = true;
	mSockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&mServAddr, sizeof(mServAddr));
	mServAddr.sin_family = AF_INET;
	mServAddr.sin_port = htons(port);
	mServAddr.sin_addr.s_addr = inet_addr(ip);
}

int sendData(unsigned char *buf, int len)
{
	if (!mIsInit)
		return -1000;

	int length = sendto(mSockfd, buf, len, 0, (struct sockaddr *)&mServAddr, sizeof(mServAddr));
	return length;
}

