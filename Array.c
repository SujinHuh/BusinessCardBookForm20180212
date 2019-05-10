//Array.c
#include "Array.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void Create(Array *array, Long capacity, size_t size) {
	array->front = calloc(capacity, size);
	array->capacity = capacity;
	array->length = 0;
}

Long Store(Array *array, Long index, void *object, size_t size) {
	memcpy(((char*)array->front) + (index*size), object, size);
	array->length++;

	return index;
}

Long Insert(Array *array, Long index, void *object, size_t size) {
	void(*temp);
	Long i = 0;
	Long j = 0;

	temp = calloc(array->capacity + 1, size);
	while (i < index) {
		memcpy(((char*)temp) + (j*size), ((char*)array->front) + (i*size), size);
		j++;
		i++;
	}
	j++;
	while (i < array->length) {
		memcpy(((char*)temp) + (j*size), ((char*)array->front) + (i*size), size);
		j++;
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->front = temp;
	array->capacity++;
	memcpy(((char*)array->front) + (index*size), object, size);
	array->length++;

	return index;
}

Long AppendFromFront(Array *array, void *object, size_t size) {
	Long index = 0;
	void(*temp);
	Long i = 0;
	Long j = 1;

	temp = calloc(array->capacity + 1, size);
	while (i < array->length) {
		memcpy(((char*)temp) + (j*size), ((char*)array->front) + (i*size), size);
		j++;
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->front = temp;
	array->capacity++;
	memcpy(((char*)array->front) + (index*size), object, size);
	array->length++;

	return index;
}

Long AppendFromRear(Array *array, void *object, size_t size) {
	Long index;
	void(*temp);
	Long i = 0;

	temp = calloc(array->capacity + 1, size);
	while (i < array->length) {
		memcpy(((char*)temp) + (i*size), ((char*)array->front) + (i*size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->front = temp;
	array->capacity++;
	index = array->capacity - 1;
	memcpy(((char*)array->front) + (index*size), object, size);
	array->length++;

	return index;
}

Long Delete(Array *array, Long index, size_t size) {
	void(*temp);
	Long i = 0;
	Long j = 0;

	if (array->capacity > 1) {
		temp = calloc(array->capacity - 1, size);
	}
	while (i < index) {
		memcpy(((char*)temp) + (j*size), ((char*)array->front) + (i*size), size);
		j++;
		i++;
	}
	i = index + 1;
	while (i < array->length) {
		memcpy(((char*)temp) + (j*size), ((char*)array->front) + (i*size), size);
		j++;
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	if (array->capacity > 1) {
		array->front = temp;
	}
	array->capacity--;
	array->length--;
	index = -1;

	return index;
}

Long DeleteFromFront(Array *array, size_t size) {
	Long index;
	void(*temp);
	Long i = 1;
	Long j = 0;

	if (array->capacity > 1) {
		temp = calloc(array->capacity - 1, size);
	}
	while (i < array->length) {
		memcpy(((char*)temp) + (j*size), ((char*)array->front) + (i*size), size);
		j++;
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	if (array->capacity > 1) {
		array->front = temp;
	}
	array->capacity--;
	array->length--;
	index = -1;

	return index;
}

Long DeleteFromRear(Array *array, size_t size) {
	Long index;
	void(*temp);
	Long i = 0;

	if (array->capacity > 1) {
		temp = calloc(array->capacity - 1, size);
	}
	while (i < array->length - 1) {
		memcpy(((char*)temp) + (i*size), ((char*)array->front) + (i*size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	if (array->capacity > 1) {
		array->front = temp;
	}
	array->capacity--;
	array->length--;
	index = -1;

	return index;
}

void Clear(Array *array) {
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->capacity = 0;
	array->length = 0;
}

Long Modify(Array *array, Long index, void *object, size_t size) {
	memcpy(((char*)array->front) + (index*size), object, size);

	return index;
}

Long LinerSearchUnique(Array *array, void *key, size_t size, int(*compare)(void*, void*)) {
	Long index = -1;
	Long i = 0;

	while (i < array->length && compare(((char*)array->front) + (i*size), key) != 0) {
		i++;
	}
	if (i < array->length) {
		index = i;
	}
	return index;
}

void LinerSearchDuplicate(Array *array, void *key, Long *(*indexes), Long *count, size_t size, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	*indexes = NULL;
	*count = 0;

	while (i < array->length) {
		if (compare(((char*)array->front) + (i*size), key) == 0) {
			(*count)++;
		}
		i++;
	}
	if (*count > 0) {
		*indexes = (Long(*))calloc(*count, sizeof(Long));
	}
	i = 0;
	while (i < array->length && j < *count) {
		if (compare(((char*)array->front) + (i*size), key) == 0) {
			(*indexes)[j] = i;
			j++;
		}
		i++;
	}
}

Long BinarySearchUnique(Array *array, void *key, size_t size, int(*compare)(void*, void*)) {
	Long index = -1;
	Long firstIndex = 0;
	Long lastIndex;
	Long middleIndex;

	lastIndex = array->length - 1;
	middleIndex = (firstIndex + lastIndex) / 2;
	while (firstIndex <= lastIndex && compare(((char*)array->front) + (middleIndex*size), key) != 0) {
		if (compare(((char*)array->front) + (middleIndex*size), key) > 0) {
			lastIndex = middleIndex - 1;
		}
		else {
			firstIndex = middleIndex + 1;
		}
		middleIndex = (firstIndex + lastIndex) / 2;
	}
	if (firstIndex <= lastIndex) {
		index = middleIndex;
	}
	return index;
}

void BinarySearchDuplicate(Array *array, void *key, Long *(*indexes), Long *count, size_t size, int(*compare)(void*, void*)) {
	Long firstIndex = 0;
	Long lastIndex;
	Long middleIndex;
	Long i;
	Long j;
	Long k = 0;
	*indexes = NULL;
	*count = 0;

	lastIndex = array->length - 1;
	middleIndex = (firstIndex + lastIndex) / 2;
	while (firstIndex <= lastIndex && compare(((char*)array->front) + (middleIndex*size), key) != 0) {
		if (compare(((char*)array->front) + (middleIndex*size), key) > 0) {
			lastIndex = middleIndex - 1;
		}
		else {
			firstIndex = middleIndex + 1;
		}
		middleIndex = (firstIndex + lastIndex) / 2;
	}
	i = middleIndex;
	j = middleIndex + 1;
	while (i >= 0 && compare(((char*)array->front) + (i*size), key) == 0) {
		(*count)++;
		i--;
	}
	while (j < array->length && compare(((char*)array->front) + (j*size), key) == 0) {
		(*count)++;
		j++;
	}
	if (*count > 0) {
		*indexes = (Long(*))calloc(*count, sizeof(Long));
	}
	i++;
	while (i < array->length && compare(((char*)array->front) + (i*size), key) == 0) {
		(*indexes)[k] = i;
		k++;
		i++;
	}
}

void BubbleSort(Array *array, size_t size, int(*compare)(void*, void*)) {
	void *temp;
	Long count;
	Long i;
	Long j;

	temp = malloc(size);
	count = array->length - 1;
	while (count != 0) {
		i = 0;
		while (i < count) {
			j = i + 1;
			if (compare(((char*)array->front) + (i*size), ((char*)array->front) + (j*size)) > 0) {
				memcpy(temp, ((char*)array->front) + (i*size), size);
				memcpy(((char*)array->front) + (i*size), ((char*)array->front) + (j*size), size);
				memcpy(((char*)array->front) + (j*size), temp, size);
			}
			i++;
		}
		count--;
	}
	if (temp != NULL) {
		free(temp);
		temp = NULL;
	}
}

void SelectionSort(Array *array, size_t size, int(*compare)(void*, void*)) {
	void *temp;
	Long i = 0;
	Long j;

	temp = malloc(size);
	while (i < array->length - 1) {
		j = i + 1;
		while (j < array->length) {
			if (compare(((char*)array->front) + (i*size), ((char*)array->front) + (j*size)) > 0) {
				memcpy(temp, ((char*)array->front) + (i*size), size);
				memcpy(((char*)array->front) + (i*size), ((char*)array->front) + (j*size), size);
				memcpy(((char*)array->front) + (j*size), temp, size);
			}
			j++;
		}
		i++;
	}
	if (temp != NULL) {
		free(temp);
		temp = NULL;
	}
}

void InsertionSort(Array *array, size_t size, int(*compare)(void*, void*)) {
	void *temp;
	Long i = 1;
	Long j;

	temp = malloc(size);
	while (i < array->length) {
		memcpy(temp, ((char*)array->front) + (i*size), size);
		j = i - 1;
		while (j >= 0 && compare(((char*)array->front) + (j*size), temp) > 0) {
			memcpy(((char*)array->front) + ((j + 1)*size), ((char*)array->front) + (j*size), size);
			j--;
		}
		memcpy(((char*)array->front) + ((j + 1)*size), temp, size);
		i++;
	}
	if (temp != NULL) {
		free(temp);
		temp = NULL;
	}
}

void Merge(Array *array, Array one, Array other, size_t size, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	Long k = 0;

	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->front = calloc((one.length) + (other.length), size);
	array->capacity = one.length + other.length;
	while (i < one.length && j < other.length) {
		if (compare(((char*)one.front) + (i*size), ((char*)other.front) + (j*size)) < 0) {
			memcpy(((char*)array->front) + (k*size), ((char*)one.front) + (i*size), size);
			k++;
			i++;
		}
		else {
			memcpy(((char*)array->front) + (k*size), ((char*)other.front) + (j*size), size);
			k++;
			j++;
		}
	}
	while (i < one.length) {
		memcpy(((char*)array->front) + (k*size), ((char*)one.front) + (i*size), size);
		k++;
		i++;
	}
	while (j < other.length) {
		memcpy(((char*)array->front) + (k*size), ((char*)other.front) + (j*size), size);
		k++;
		j++;
	}
	array->length = one.length + other.length;
}

void GetAt(Array *array, Long index, void *object, size_t size) {
	memcpy(object, ((char*)array->front) + (index*size), size);
}

void Destroy(Array *array) {
	if (array->front) {
		free(array->front);
	}
}