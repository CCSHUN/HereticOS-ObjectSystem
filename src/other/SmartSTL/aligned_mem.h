#pragma  once
//2005.4.16 对齐边界分配内存





#ifndef YSS_ASSERT
#define YSS_ASSERT
#endif // !YSS_ASSERT


//内存对齐......Head+(边界)Block
inline void* aligned_new(size_t size, size_t alignment)
{
	// 检查alignment是否是2^N  
	YSS_ASSERT((alignment & (alignment - 1)));
	// 计算出一个最大的offset，sizeof(void*)是为了存储原始指针地址  
	size_t offset = sizeof(void*)+(--alignment);

  
	//u_char* p =(u_char*) malloc(offset + size);
	unsigned char * p = (unsigned char *)new unsigned char[offset + size];
	if (!p) return nullptr;

	// 通过& alignment的补码得到对齐的边界地址
	void* r = (void *)(((size_t)(p + offset)) & (~alignment));
	// 将r当做一个指向void*的指针，在r当前地址前面放入原始地址  
	((void **)r)[-1] = p;
	// 返回经过对齐的内存地址  
	return r;
}

inline void aligned_delete(void* p)
{
	// 还原回原始地址，并free  
	//free(((void **)p)[-1]);
	delete p;
}

#ifdef _USE_HEAPMEM_CACHE_LINE_
inline void* operator new(size_t size)
{
	//void*   tmp=malloc(size);   
	//memset(tmp,0,size);   
	//return   tmp;   

	return aligned_new(size, __CACHE_LINE__);
}


/*
inline void *__cdecl operator new(size_t, void *_P)
{
return (_P);
}
*/


inline void operator delete(void * ptr)
{
	//free(ptr);   
	aligned_free(ptr);
}

inline void* operator new[](size_t size)
{
	return aligned_new(size, __CACHE_LINE__);
}

inline void operator delete[](void * ptr)
{
	aligned_delete(ptr);
}

#endif



class CAlignedMemory
{
public:
	
	inline void* operator new(size_t size)
	{
		 
		return aligned_new(size, __CACHE_LINE__);
	}


	inline void operator delete(void * ptr)
	{
		//free(ptr);   
		aligned_delete(ptr);
	}

	inline void* operator new[](size_t size)
	{
		return aligned_new(size, __CACHE_LINE__);
	}

	inline void operator delete[](void * ptr){
		
		aligned_delete(ptr);
	}

	CAlignedMemory(){};
	~CAlignedMemory(){};

protected:
	
private:
};


#define USING_ALIGNEDMEM  inline void* operator new(size_t size)\
{\
	return aligned_new(size, __CACHE_LINE__);\
}\
inline void operator delete(void * ptr)\
{\
	aligned_delete(ptr);\
}\
	inline void* operator new[](size_t size)\
{\
	return aligned_new(size, __CACHE_LINE__); \
}\
inline void operator delete[](void * ptr)\
{\
	aligned_delete(ptr); \
}\


#define USING_PAGE_ALIGNEDMEM  inline void* operator new(size_t size)\
{\
	return aligned_new(size, __PAGE_SIZE__);\
}\
inline void operator delete(void * ptr)\
{\
	aligned_delete(ptr);\
}\
	inline void* operator new[](size_t size)\
{\
	return aligned_new(size, __PAGE_SIZE__); \
}\
inline void operator delete[](void * ptr)\
{\
	aligned_delete(ptr); \
}\

/*



*/

