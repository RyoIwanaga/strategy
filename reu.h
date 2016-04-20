#ifndef _reu_h_
#define _reu_h_

/***** Macros *****/

#define REU__TYPEDEF_SPTR(type)				\
public: typedef std::shared_ptr<type> Ptr


#define REU__PROPERTY(type, var, fnName)							\
private:	type var;												\
public:		virtual type get##fnName() const { return var; }		\
public:		virtual void set##fnName(type var) { this->var = var; } 

#define REU__PROPERTY_READONLY(type, var, fnName)					\
private:	type var;												\
public:		virtual type get##fnName() const { return var; }

#define REU__PROPERTY_PRIVATE(type, var, fnName)			\
private:	type var;										\
private:	type get##fnName() const { return var; }		\
private:	void set##fnName(type var) { this->var = var; }
/******/


typedef short			sshort;
typedef unsigned short	ushort;
typedef int 			sint;
typedef unsigned int 	uint;
typedef long 			slong;
typedef unsigned long 	ulong;


#include <algorithm>
#include <list>
#include <functional>


#define NS_REU 		namespace reu {
#define NS_REU_END 	}

NS_REU; 


/*
template <typename Iterable, typename T>
typename Iterable<T> find(typename Iterable<T> iterable)
{
	return iterable.first();
} */


namespace diagram {

	template <typename T>
		class Vec2
		{
			REU__PROPERTY(T, x, X);
			REU__PROPERTY(T, y, Y);

		public:
			Vec2(T x, T y);
			virtual ~Vec2() {}
		};

	template <typename T>
		Vec2<T>::Vec2(T x, T y) :
			x(x),
			y(y)
	{}
}

namespace list {

template <typename T>
typename std::list<T>::iterator find(std::list<T> lst, const T& item)
{
	
}


	/*
	   template <typename T> 
	   typename std::list<T>::iterator find(std::list<T> lst, std::function<bool(T)> fnPred)
	   {
	   auto ite = lst.begin();

	   for (; ite != lst.end(); ite++) {
	   if (fnPred(*ite))
	   (*ite)->getPos();
	   return typename ite;
	   }

	   return ite;
	   } */
}

NS_REU_END;

#endif

