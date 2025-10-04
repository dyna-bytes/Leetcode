/*
 *	struct Iterator {
 *		// Returns true if the iteration has more elements.
 *		bool (*hasNext)();
 *
 * 		// Returns the next element in the iteration.
 *		int (*next)();
 *	};
 */

struct PeekingIterator {
    struct Iterator *iterator;
    int hasPeeked;
};

struct PeekingIterator* Constructor(struct Iterator* iter) {
    struct PeekingIterator* piter = malloc(sizeof(struct PeekingIterator));
    piter->iterator = iter;
    piter->hasPeeked = false;
    return piter;
}

int peek(struct PeekingIterator* obj) {
    if (obj->hasPeeked) return obj->hasPeeked;
    return obj->hasPeeked = obj->iterator->next();
}

int next(struct PeekingIterator* obj) {
    if (obj->hasPeeked) {
        int ret = obj->hasPeeked;
        obj->hasPeeked = false;
        return ret;
    }
    obj->hasPeeked = false;
    return obj->iterator->next();
}

bool hasNext(struct PeekingIterator* obj) {
    if (obj->hasPeeked) return true;

    return obj->iterator->hasNext();
}

/**
 * Your PeekingIterator struct will be instantiated and called as such:
 * PeekingIterator* obj = peekingIteratorCreate(arr, arrSize);
 * int param_1 = peek(obj);
 * int param_2 = next(obj);
 * bool param_3 = hasNext(obj);
 * peekingIteratorFree(obj);
*/