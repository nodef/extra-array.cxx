#ifndef _OARRAY_H_
#define _OARRAY_H_


// Dhrtarastra said: O Sanjaya, what did my sons desirous of battle and the sons of Pandu do
// after assembling at the holy land of righteousness, Kuruksetra?
// ref: http://www.bhagavad-gita.org/Gita/verse-01-01.html


#pragma region required headers
#include <stddef.h>
#include <stdlib.h>
#pragma endregion



#pragma region type
// Structure for array.
// args: name, type.
#define OARRAY_TS(N, T) \
	typedef struct _##N { \
		T* at; \
		size_t space; \
	} N
#pragma endregion



#pragma region function
// Open with static memory.
// args: array, at, space.
#define OARRAY_FS_OPEN(N, T) \
	inline T* N##_open(void* o, void* at, size_t space)

#define OARRAY_FB_OPEN(N, T) { \
		N* z = (N*)o; \
		z->at = (T*)at; \
		z->space = space; \
		return z->at; \
	}


// Open with heap memory.
// args: array, space.
#define OARRAY_FS_OPENHEAP(N, T) \
	inline T* N##_openHeap(void* o, size_t space)

#define OARRAY_FB_OPENHEAP(N, T) { \
		return N##_open(o, malloc(space*sizeof(T)), space); \
	}


// Reopen with different space (heap only).
// args: array, space.
#define OARRAY_FS_REOPEN(N, T) \
	inline T* N##_reopen(void* o, size_t space)

#define OARRAY_FB_REOPEN(N, T) { \
		N* z = (N*)o; \
		return N##_open(o, realloc(z->at, space*sizeof(T)), space); \
	}


// Close (heap only).
// args: array.
#define OARRAY_FS_CLOSE(N, T) \
	inline T* N##_close(void* o)

#define OARRAY_FB_CLOSE(N, T) { \
		N* z = (N*)o; \
		free(z->at); \
		return NULL; \
	}


// Get where values are stored at.
// args: array.
#define OARRAY_FS_AT(N, T) \
	inline T* N##_at(void* o)

#define OARRAY_FB_AT(N, T) { \
		N* z = (N*)o; \
		return z->at; \
	}


// Get space.
// args: array.
#define OARRAY_FS_SPACE(N, T) \
	inline size_t N##_space(void* o)

#define OARRAY_FB_SPACE(N, T) { \
		N* z = (N*)o; \
		return z->space; \
	}


// Get size.
// args: array.
#define OARRAY_FS_SIZE(N, T) \
	inline size_t N##_size(void* o)

#define OARRAY_FB_SIZE(N, T) { \
		return N##_space(o); \
	}


// Get begin index, forward.
// args: array.
#define OARRAY_FS_BEGIN(N, T) \
	inline size_t N##_begin(void* o)

#define OARRAY_FB_BEGIN(N, T) { \
		return 0; \
	}


// Get end index, forward.
// args: array.
#define OARRAY_FS_END(N, T) \
	inline size_t N##_end(void* o)

#define OARRAY_FB_END(N, T) { \
		return N##_size(o); \
	}


// Get begin index, backward.
// args: array.
#define OARRAY_FS_BEGINBACK(N, T) \
	inline size_t N##_beginBack(void* o)

#define OARRAY_FB_BEGINBACK(N, T) { \
		return N##_size(o) - 1; \
	}


// Get end index, backward.
// args: array.
#define OARRAY_FS_ENDBACK(N, T) \
	inline size_t N##_endBack(void* o)

#define OARRAY_FB_ENDBACK(N, T) { \
		return -1; \
	}


// Get whether next value exists.
// args: array, index.
#define OARRAY_FS_HASNEXT(N, T) \
	inline int N##_hasNext(void* o, size_t i)

#define OARRAY_FB_HASNEXT(N, T) { \
		return i != N##_end(o); \
	}


// Get whether previous value exists.
// args: array, index.
#define OARRAY_FS_HASPREV(N, T) \
	inline size_t N##_hasPrev(void* o, size_t i)

#define OARRAY_FB_HASPREV(N, T) { \
		return i != N##_endBack(o); \
	}


// Get index of next value.
// args: array, index.
#define OARRAY_FS_NEXT(N, T) \
	inline size_t N##_next(void* o, size_t i)

#define OARRAY_FB_NEXT(N, T) { \
		return i + 1; \
	}


// Get index of previous value.
// args: array, index.
#define OARRAY_FS_PREV(N, T) \
	inline size_t N##_prev(void* o, size_t i)

#define OARRAY_FB_PREV(N, T) { \
		return i - 1; \
	}


// Count number of values in range, forward.
// args: array, start, end.
#define OARRAY_FS_COUNT(N, T) \
	inline size_t N##_count(void* o, size_t i, size_t ie)

#define OARRAY_FB_COUNT(N, T) { \
		size_t n = 0; \
		for(; i!=ie; i=N##_next(o, i)) \
			n++; \
		return n; \
	}


// Count number of values in range, backward.
// args: array, start, end.
#define OARRAY_FS_COUNTBACK(N, T) \
	inline size_t N##_countBack(void* o, size_t i, size_t ie)

#define OARRAY_FB_COUNTBACK(N, T) { \
		size_t n = 0; \
		for(; i!=ie; i=N##_prev(o, i)) \
			n++; \
		return n; \
	}


// Get value at index.
// args: array, index.
#define OARRAY_FS_GET(N, T) \
	inline T N##_get(void* o, size_t i)

#define OARRAY_FB_GET(N, T) { \
		return N##_at(o)[i]; \
	}


// Get values to destination, forward.
// args: array, start, end, dest, dest-size.
#define OARRAY_FS_GETMANY(N, T) \
	inline size_t N##_getMany(void* o, size_t i, size_t ie, void* d, size_t ds)

#define OARRAY_FB_GETMANY(N, T) { \
		size_t n = 0; \
		T* pd = (T*)d; \
		for(; n<ds && i!=ie; i=N##_next(o, i)) \
			pd[n++] = N##_get(o, i); \
		return n; \
	}


// Get values to destination, backward.
// args: array, start, end, dest, dest-size.
#define OARRAY_FS_GETBACKMANY(N, T) \
	inline size_t N##_getBackMany(void* o, size_t i, size_t ie, void* d, size_t ds)

#define OARRAY_FB_GETBACKMANY(N, T) { \
		size_t n = 0; \
		T* pd = (T*)d; \
		for(; n<ds && i!=ie; i=N##_prev(o, i)) \
			pd[n++] = N##_get(o, i); \
		return n; \
	}


// Set value at index.
// args: array, index, value.
#define OARRAY_FS_SET(N, T) \
	inline T N##_set(void* o, size_t i, T v)

#define OARRAY_FB_SET(N, T) { \
		return (N##_at(o)[i] = v); \
	}


// Set values from source, forward.
// args: array, start, end, dest, dest-size.
#define OARRAY_FS_SETMANY(N, T) \
	inline size_t N##_setMany(void* o, size_t i, size_t ie, void* d, size_t ds)

#define OARRAY_FB_SETMANY(N, T) { \
		size_t n = 0; \
		T* pd = (T*)d; \
		for(; n<ds && i!=ie; i=N##_next(o, i)) \
			N##_set(o, i, pd[n++]); \
		return n; \
	}


// Set values from source, backward.
// args: array, start, end, dest, dest-size.
#define OARRAY_FS_SETBACKMANY(N, T) \
	inline size_t N##_setBackMany(void* o, size_t i, size_t ie, void* d, size_t ds)

#define OARRAY_FB_SETBACKMANY(N, T) { \
		size_t n = 0; \
		T* pd = (T*)d; \
		for(; n<ds && i!=ie; i=N##_prev(o, i)) \
			N##_set(o, i, pd[n++]); \
		return n; \
	}


// Fill with value.
// args: array, start, end, value.
#define OARRAY_FS_FILL(N, T) \
	inline size_t N##_fill(void* o, size_t i, size_t ie, T v)

#define OARRAY_FB_FILL(N, T) { \
		size_t n = 0; \
		for(; i!=ie; n++, i=N##_next(o, i)) \
			N##_set(o, i, v); \
		return n; \
	}


// Copy values within array, forward to upward.
// args: array, start, end, dest-start.
#define OARRAY_FS_COPY(N, T) \
	inline size_t N##_copy(void* o, size_t i, size_t ie, size_t di)

#define OARRAY_FB_COPY(N, T) { \
		size_t n = 0; \
		for(; i!=ie; n++, i=N##_next(o, i), di=N##_next(o, di)) \
			N##_set(o, di, N##_get(o, i)); \
		return n++; \
	}


// Copy values within array, forward to downward.
// args: array, start, end, dest-start.
#define OARRAY_FS_COPYDOWN(N, T) \
	inline size_t N##_copyDown(void* o, size_t i, size_t ie, size_t di)

#define OARRAY_FB_COPYDOWN(N, T) { \
		size_t n = 0; \
		for(; i!=ie; n++, i=N##_next(o, i), di=N##_prev(o, di)) \
			N##_set(o, di, N##_get(o, i)); \
		return n++; \
	}


// Copy values within array, backward to upward.
// args: array, start, end, dest-start.
#define OARRAY_FS_COPYBACK(N, T) \
	inline size_t N##_copyBack(void* o, size_t i, size_t ie, size_t di)

#define OARRAY_FB_COPYBACK(N, T) { \
		size_t n = 0; \
		for(; i!=ie; n++, i=N##_prev(o, i), di=N##_next(o, di)) \
			N##_set(o, di, N##_get(o, i)); \
		return n; \
	}


// Copy values within array, backward to downward.
// args: array, start, end, dest-start.
#define OARRAY_FS_COPYBACKDOWN(N, T) \
	inline size_t N##_copyBackDown(void* o, size_t i, size_t ie, size_t di)

#define OARRAY_FB_COPYBACKDOWN(N, T) { \
		size_t n = 0; \
		for(; i!=ie; n++, i=N##_prev(o, i), di=N##_prev(o, di)) \
			N##_set(o, di, N##_get(o, i)); \
		return n; \
	}


// Find index of value, forward.
// args: array, start, end, value.
#define OARRAY_FS_FIND(N, T) \
	inline size_t N##_find(void* o, size_t i, size_t ie, T v)

#define OARRAY_FB_FIND(N, T) { \
		for(; i!=ie; i=N##_next(o, i)) \
			if(N##_get(o, i) == v) return i; \
		return -1; \
	}


// Find index of values, forward.
// args: array, start, end, value, dest, dest-size.
#define OARRAY_FS_FINDMANY(N, T) \
	inline size_t N##_findMany(void* o, size_t i, size_t ie, T v, void* d, size_t ds)

#define OARRAY_FB_FINDMANY(N, T) { \
		size_t n = 0; \
		T* pd = (T*)d; \
		for(; n<ds && i!=ie; i=N##_next(o, i)) \
			if(N##_get(o, i) == v) pd[n++] = i; \
		return n; \
	}


// Find index of value, backward.
// args: array, start, end, value.
#define OARRAY_FS_FINDBACK(N, T) \
	inline size_t N##_findBack(void* o, size_t i, size_t ie, T v)

#define OARRAY_FB_FINDBACK(N, T) { \
		for(; i!=ie; i=N##_prev(o, i)) \
			if(N##_get(o, i) == v) return i; \
		return -1; \
	}


// Find index of values, backward.
// args: array, start, value, dest, dest-size.
#define OARRAY_FS_FINDBACKMANY(N, T) \
	inline size_t N##_findBackMany(void* o, size_t i, size_t ie, T v, void* d, size_t ds)

#define OARRAY_FB_FINDBACKMANY(N, T) { \
		size_t n = 0; \
		T* pd = (T*)d; \
		for(; n<ds && i!=ie; i=N##_prev(o, i)) \
			if(N##_get(o, i) == v) pd[n++] = i; \
		return n; \
	}
#pragma endregion



#pragma region macro
// Declare array types.
// args: name, type.
#define OARRAY_DECLARE_TS(N, T) \
	OARRAY_TS(N, T);


// Declare array functions.
// args: name, type.
#define OARRAY_DECLARE_FS(N, T) \
	OARRAY_FS_OPEN(N, T); \
	OARRAY_FS_OPENHEAP(N, T); \
	OARRAY_FS_REOPEN(N, T); \
	OARRAY_FS_CLOSE(N, T); \
	OARRAY_FS_AT(N, T); \
	OARRAY_FS_SPACE(N, T); \
	OARRAY_FS_SIZE(N, T); \
	OARRAY_FS_BEGIN(N, T); \
	OARRAY_FS_END(N, T); \
	OARRAY_FS_BEGINBACK(N, T); \
	OARRAY_FS_ENDBACK(N, T); \
	OARRAY_FS_HASNEXT(N, T); \
	OARRAY_FS_HASPREV(N, T); \
	OARRAY_FS_NEXT(N, T); \
	OARRAY_FS_PREV(N, T); \
	OARRAY_FS_COUNT(N, T); \
	OARRAY_FS_COUNTBACK(N, T); \
	OARRAY_FS_GET(N, T); \
	OARRAY_FS_GETMANY(N, T); \
	OARRAY_FS_GETBACKMANY(N, T); \
	OARRAY_FS_SET(N, T); \
	OARRAY_FS_SETMANY(N, T); \
	OARRAY_FS_SETBACKMANY(N, T); \
	OARRAY_FS_FILL(N, T); \
	OARRAY_FS_COPY(N, T); \
	OARRAY_FS_COPYDOWN(N, T); \
	OARRAY_FS_COPYBACK(N, T); \
	OARRAY_FS_COPYBACKDOWN(N, T); \
	OARRAY_FS_FIND(N, T); \
	OARRAY_FS_FINDMANY(N, T); \
	OARRAY_FS_FINDBACK(N, T); \
	OARRAY_FS_FINDBACKMANY(N, T);


// Declare array types and functions.
// args: name, type.
#define OARRAY_DECLARE(N, T) \
	OARRAY_DECLARE_TS(N, T) \
	OARRAY_DECLARE_FS(N, T)


// Define array functions.
// args: name, type.
#define OARRAY_DEFINE(N, T) \
	OARRAY_FS_OPEN(N, T) \
	OARRAY_FB_OPEN(N, T) \
	OARRAY_FS_OPENHEAP(N, T) \
	OARRAY_FB_OPENHEAP(N, T) \
	OARRAY_FS_REOPEN(N, T) \
	OARRAY_FB_REOPEN(N, T) \
	OARRAY_FS_CLOSE(N, T) \
	OARRAY_FB_CLOSE(N, T) \
	OARRAY_FS_AT(N, T) \
	OARRAY_FB_AT(N, T) \
	OARRAY_FS_SPACE(N, T) \
	OARRAY_FB_SPACE(N, T) \
	OARRAY_FS_SIZE(N, T) \
	OARRAY_FB_SIZE(N, T) \
	OARRAY_FS_BEGIN(N, T) \
	OARRAY_FB_BEGIN(N, T) \
	OARRAY_FS_END(N, T) \
	OARRAY_FB_END(N, T) \
	OARRAY_FS_BEGINBACK(N, T) \
	OARRAY_FB_BEGINBACK(N, T) \
	OARRAY_FS_ENDBACK(N, T) \
	OARRAY_FB_ENDBACK(N, T) \
	OARRAY_FS_HASNEXT(N, T) \
	OARRAY_FB_HASNEXT(N, T) \
	OARRAY_FS_HASPREV(N, T) \
	OARRAY_FB_HASPREV(N, T) \
	OARRAY_FS_NEXT(N, T) \
	OARRAY_FB_NEXT(N, T) \
	OARRAY_FS_PREV(N, T) \
	OARRAY_FB_PREV(N, T) \
	OARRAY_FS_COUNT(N, T) \
	OARRAY_FB_COUNT(N, T) \
	OARRAY_FS_COUNTBACK(N, T) \
	OARRAY_FB_COUNTBACK(N, T) \
	OARRAY_FS_GET(N, T) \
	OARRAY_FB_GET(N, T) \
	OARRAY_FS_GETMANY(N, T) \
	OARRAY_FB_GETMANY(N, T) \
	OARRAY_FS_GETBACKMANY(N, T) \
	OARRAY_FB_GETBACKMANY(N, T) \
	OARRAY_FS_SET(N, T) \
	OARRAY_FB_SET(N, T) \
	OARRAY_FS_SETMANY(N, T) \
	OARRAY_FB_SETMANY(N, T) \
	OARRAY_FS_SETBACKMANY(N, T) \
	OARRAY_FB_SETBACKMANY(N, T) \
	OARRAY_FS_FILL(N, T) \
	OARRAY_FB_FILL(N, T) \
	OARRAY_FS_COPY(N, T) \
	OARRAY_FB_COPY(N, T) \
	OARRAY_FS_COPYDOWN(N, T) \
	OARRAY_FB_COPYDOWN(N, T) \
	OARRAY_FS_COPYBACK(N, T) \
	OARRAY_FB_COPYBACK(N, T) \
	OARRAY_FS_COPYBACKDOWN(N, T) \
	OARRAY_FB_COPYBACKDOWN(N, T) \
	OARRAY_FS_FIND(N, T) \
	OARRAY_FB_FIND(N, T) \
	OARRAY_FS_FINDMANY(N, T) \
	OARRAY_FB_FINDMANY(N, T) \
	OARRAY_FS_FINDBACK(N, T) \
	OARRAY_FB_FINDBACK(N, T) \
	OARRAY_FS_FINDBACKMANY(N, T) \
	OARRAY_FB_FINDBACKMANY(N, T)
#pragma endregion


#endif // !_OARRAY_H_
