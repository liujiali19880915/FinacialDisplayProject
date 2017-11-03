/* ����boost����http ��Post��Get����*/

#ifndef _HTTPBASE_H_
#define _HTTPBASE_H_


#include<iostream>
using namespace std;

class HttpBase {
public:
	HttpBase();
	virtual ~HttpBase();

	//����post ����
	virtual int post(const std::string& url) = 0;

	//����get����
	virtual int get(const std::string& url) = 0;
	virtual std::string getResponse(void) = 0;

protected:
	typedef int(*pBuildRequest)(const std::string&, const std::string&, std::ostream&);

	/*����URL
	parseURL
	url��		 ��������url   
	out_server�� ��������  
	out_port��	 �˿ں� 
	out_path��	 ��������ҳ
	*/
	static int parseURL(const std::string& url, std::string& out_server,
		 std::string& out_port,  std::string& out_path);


	//���� post ����
	static int buildPostRequest(const std::string& server,
		const std::string& path,
		 std::ostream& out_request);

	//���� get ����
	static int buildGetRequest(const std::string& server,
		const std::string& path,
		 std::ostream& out_request);
};



#endif // !_HTTPBASE_H_
