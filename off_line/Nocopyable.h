 ///
 /// @file    Nocopyable.h
 /// @author  Borix(244303237@qq.com)
 /// @date    2018-07-09 17:36:09
 ///
#ifndef __NOCOPYABLE_H__
#define __NOCOPYABLE_H__
class Nocopyable
{
public:
	Nocopyable() = default;
	~Nocopyable() = default;
private:
	Nocopyable(const Nocopyable &rhs);
	Nocopyable& operator=(const Nocopyable &rhs);
};


#endif
