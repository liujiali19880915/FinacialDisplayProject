//define error file

#ifndef _HTTP_ERROR_INFO_H_  
#define _HTTP_ERROR_INFO_H_

#define HTTP_SUCCESS  (0)  //(0) 操作成功
#define HTTP_ERROR_UNKNOWN (-1) //未知的错误
#define HTTP_ERROR_NETWORK (-2)//网络连接失败
#define HTTP_ERROR_HEETP_HEAD (-3) //未找到协议头 http || https

#define HTTP_ERROR_SERVICE (-1000)//服务器请求失败
#define HTTP_ERROR_LOGIN   (-1001)//登陆失败
#define HTTP_ERROR_ID	   (-1002)  //企业ID不存在
#define HTTP_ERROR_USER    (-1003)//账号不存在
#define HTTP_ERROR_PASSWORD (-1004)//密码错误


#endif // !1

