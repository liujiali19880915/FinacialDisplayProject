#ifndef _NOCOPYABLE_H  
#define _NOCOPYABLE_H  


class nocopyable{
	private:
		nocopyable(const nocopyable& x) = delete;
		nocopyable& operator=(const nocopyable&x) = delete;
	public:
		nocopyable() = default;
		~nocopyable() = default;
};


#endif // _NOCOPYABLE_H  #pragma once
