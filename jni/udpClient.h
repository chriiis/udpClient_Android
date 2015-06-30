#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

int init(char *ip, int port);
int release();
void initSocket(char *ip, int port);
void initTimer();
void stopTimer();
void timeout(int signal);
int sendData(unsigned char *buf, int len);

#endif
