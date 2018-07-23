#ifndef apto_util
#define apto_util

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_DECLARATION(elementType, arrayType) \
	typedef struct { \
		elementType* data; \
		int length; \
		int capacity; \
	} arrayType; \
	\
	void create ## arrayType(arrayType* array); \
	void destroy ## arrayType(arrayType* array); \
	elementType get ## elementType(int index, arrayType* array); \
	void append ## elementType(elementType element, arrayType* array);

#define ARRAY_IMPLEMENTATION(elementType, arrayType) \
	void create ## arrayType(arrayType* array) { \
		array->data = (elementType*)malloc(sizeof(elementType) * 2); \
		array->length = 0; \
		array->capacity = 2; \
	} \
	\
	void destroy ## arrayType(arrayType* array) { \
		free(array->data); \
	} \
	\
	elementType get ## elementType(int index, arrayType* array) { \
		return array->data[index]; \
	} \
	\
	void append ## elementType(elementType element, arrayType* array) { \
		if (array->length == array->capacity) { \
			array->capacity *= 2; \
			array->data = (elementType*)realloc((void*)array->data, sizeof(elementType) * array->capacity); \
		} \
		\
		array->data[array->length] = element; \
		array->length += 1; \
	}

#endif
