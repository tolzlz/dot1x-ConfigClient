



//
// Created by kui on 2018/12/6.
//

#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <malloc.h>
#include<stdio.h>
#include<pthread.h>
#include<netinet/in.h>
#include<stdlib.h>
//#include<string.h>
//#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<errno.h>
#include<string>
//#include <iostream>
#include <cstring>


#define  LOG_TAG    "KuiTag"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)


#define BUFLEN 1024



//using namespace std;
std::string &replace_all_distinct(std::string &str, const std::string &old_value, const std::string &new_value) {
    for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length()) {
        if ((pos = str.find(old_value, pos)) != std::string::npos) {
            str.replace(pos, old_value.length(), new_value);
        } else { break; }
    }
    return str;
}


//Java_com_jcqihang_myapplication_MainActivity_stringFromJNI
int main(){

    //获取Assert

//    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
//    if (mgr == NULL)
//    {
//        sleep(2);
//        jstring s = charTojstring(env,"安卓获取assetManager失败");
//        (*env)->CallVoidMethod(env,mcallback,callId,s,mobject);
//    }
//    /**
//     * 获取文件名打开
//     */
//     jboolean isCopy;
//    const char *mfile = "default.conf";//不能写“assets/text.txt”，路径已经在assets下了
//    AAsset* asset = AAssetManager_open(mgr, mfile,AASSET_MODE_UNKNOWN);
//    if(asset==NULL)
//    {
//        sleep(2);
//        jstring s = charTojstring(env,"打开文件失败");
//        (*env)->CallVoidMethod(env,mcallback,callId,s,mobject);
//    }
//    /*获取文件大小*/
//    off_t bufferSize = AAsset_getLength(asset);
//    char *buffer=(char *)malloc(bufferSize+1);
//    buffer[bufferSize]=0;
    //int numBytesRead = AAsset_read(asset, buffer, bufferSize);
    //替换\r\n为\n




//    FILE * fp = fopen("/data/local/tmp/net8021x.conf", "rb");
    FILE * fp = fopen("net8021x.conf", "rb");
    if (fp != NULL)
    {
        fseek(fp, 0, SEEK_END);
        int len_file = ftell(fp) + 1;
        //fseek(fp,0,SEEK_SET);
        rewind(fp);
        //char* buffertmp = (char *)malloc(sizeof(char )*len_file);
        char *buffertmp = (char *) malloc(sizeof(char) * len_file);
        //memset(buffertmp, 0, (unsigned int)len_file);
        //fread(buffer,sizeof(char ),len_file,fp);
        //如果不为空就去认证
        //替换\r\n为\n
        fread(buffertmp, 1, len_file, fp);


        std::string fpp = buffertmp;
        replace_all_distinct(fpp, "\r\n", "\n");
        const char *buffer = fpp.data();
        //char buffer_reply[50];
        char buffer_reply[BUFLEN];







        //---------------------------------------------------------------------------------------------
        //创建socket
//    int socketfd,ret;
//    fd_set fd;
//    FD_ZERO(&fd);
//    FD_SET(0,&fd);
//
//
//    socketfd = socket(PF_INET,SOCK_STREAM,0);
//    FD_SET(socketfd,&fd);
//    ret = select(socketfd+1,&fd,NULL,NULL,NULL);
//    struct sockaddr_in saddr;
//    memset(&saddr,0,sizeof(saddr));
//    saddr.sin_family = PF_INET;
//    saddr.sin_port = htons(6000);
//    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
//
//    if(connect(socketfd,(struct sockaddr *)&saddr,sizeof(struct sockaddr))<0)
//
//        perror("connect() error!\n");
//
//    //只要与服务器连上立马将自己的昵称发送过去
//    send(socketfd,buffer,bufferSize,0);
//    char buf[50],buf1[50];
//    while(1)
//    {
//        bzero(buf,50);
//        bzero(buf1,50);
//
//        FD_SET(0,&fd);
//        FD_SET(socketfd,&fd);
//        ret = select(socketfd+1,&fd,NULL,NULL,NULL);
//        if(FD_ISSET(socketfd,&fd))
//        {
//            if(recv(socketfd,buf1,sizeof(buf1),0)<0){
//                perror("recv() error!\n");
//            }
//            sleep(2);
//            printf("%s\n",buf1);
////            jstring s = charTojstring(env,buf1);
////            (*env)->CallVoidMethod(env,mcallback,callId,s,mobject);
//            _status_change(atoi(buf1),env,mcallback,callId,mobject);
//            continue;
//        }
////        if(FD_ISSET(0,&fd))
////        {
////            scanf("%s",buf);
////            strcat(buf,":");
////            strcat(buf,buffer);
////            if(send(socketfd,buf,strlen(buf),0)<0)
////                perror("send() error!\n");
////            continue;
////        }
//
//    }

        int sockfd;
        struct sockaddr_in s_addr;
        socklen_t len;
        unsigned int port;
        //char buf[BUFLEN];
        fd_set rfds;
        struct timeval tv;
        int retval, maxfd;

        /*建立socket*/
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket");
            exit(errno);
        } else
            printf("socket create success!\n");

        /*设置服务器端口*/
        port = 4567;
        /*设置服务器ip*/
        bzero(&s_addr, sizeof(s_addr));
        s_addr.sin_family = AF_INET;
        s_addr.sin_port = htons(port);
        char *address = "127.0.0.1";
        if (inet_aton(address, (struct in_addr *) &s_addr.sin_addr.s_addr) == 0) {
            perror(address);
            exit(errno);
        }
        /*开始连接服务器*/
        if (connect(sockfd, (struct sockaddr *) &s_addr, sizeof(struct sockaddr)) == -1) {
            perror("connect");
            exit(errno);
        } else {
            printf("conncet success!\n");
        }


        //---------------------tmp---------------------------
        /*fgets函数：从流中读取BUFLEN-1个字符*/
        //strcpy(buf,"vfdvdvsvbsdvbsdk");


        /*打印发送的消息*/
        //这个地方的buffer就是从配置文件中读取的文件流
        //fputs(buf,stdout);
        //替换\r\n
        len = send(sockfd, buffer, strlen(buffer), 0);
        if (len > 0)
            printf("消息发送成功，本次共发送的字节数是：%d\n", len);
        else {
            printf("消息发送失败!\n");
        }
        //--------------------------------------------------

        while (true) {
            /*把可读文件描述符的集合清空*/
            FD_ZERO(&rfds);
            /*把标准输入的文件描述符加入到集合中*/
            FD_SET(0, &rfds);
            maxfd = 0;
            /*把当前连接的文件描述符加入到集合中*/
            FD_SET(sockfd, &rfds);
            /*找出文件描述符集合中最大的文件描述符*/
            if (maxfd < sockfd)
                maxfd = sockfd;
            /*设置超时时间*/
            tv.tv_sec = 5;
            tv.tv_usec = 0;
            /*等待聊天*/
            retval = select(maxfd + 1, &rfds, NULL, NULL, &tv);
            if (retval == -1) {
                printf("select出错，客户端程序退出\n");
                break;
            } else if (retval == 0) {
                printf("客户端没有任何输入信息，并且服务器也没有信息到来，waiting...\n");
                continue;
            } else {
                /*服务器发来了消息*/
                //此处就是监听从服务传过来的数据。_status_change是去解析从那边传过来
                printf("要开始接受数据了4");
                if (FD_ISSET(sockfd, &rfds)) {
                    /******接收消息*******/
                    bzero(buffer_reply, BUFLEN);
                    len = recv(sockfd, buffer_reply, BUFLEN, 0);


                    if (len > 0) {
                        //env,mcallback,callId,s,mobject
                        //_status_change(buffer,env,mcallback,callId,mobject);
                        printf("服务器发来的消息是：%s,共有字节数是: %d\n", buffer_reply, len);

                    } else {
                        if (len < 0)
                            printf("接受消息失败！\n");
                        else
                            printf("服务器退出了，聊天终止！\n");
                        break;
                    }
                }
            }

        }
        /*关闭连接*/
        close(sockfd);

        //---------------------------------------------------------------------------------------------




        free(buffertmp);
        free(buffer_reply);
        /*关闭文件*/
        fclose(fp);
    }
}
