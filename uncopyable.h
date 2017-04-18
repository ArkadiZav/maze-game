#ifndef __UNCOPYABLE_H__
#define __UNCOPYABLE_H__

class Uncopyable
{
public:
	Uncopyable(){};
	virtual ~Uncopyable(){};
	
private:
	Uncopyable(const Uncopyable& _mutex);
	Uncopyable& operator=(const Uncopyable& _mutex);
};
#endif /*ifndef __UNCOPYABLE_H__*/
