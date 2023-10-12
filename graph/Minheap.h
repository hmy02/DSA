template<class T>
class Minheap {
private:
    T* heapArray;
    int CurrentSize;
    int Maxsize;
    void swap(int x, int y) { T temp = heapArray[x]; heapArray[x] = heapArray[y]; heapArray[y] = temp; };

public:
    Minheap(int maxsize) {
        Maxsize = maxsize;
        CurrentSize = 0;
        heapArray = new T[maxsize];
    }
    void Insert(T& item);
    T RemoveMin();
    bool isempty() { return CurrentSize == 0; };
    void SiftDown(int pos);
    void SiftUp(int pos);
};

template<class T>
void Minheap<T>::SiftDown(int pos) {
    if (2 * pos + 1 >= CurrentSize) return;
    int temppos = 2 * pos + 1;
    if (temppos + 1 < CurrentSize && heapArray[temppos + 1] < heapArray[temppos]) {
        temppos++;
    }
    if (heapArray[pos] > heapArray[temppos]) {
        swap(pos, temppos);
        SiftDown(temppos);
    }

}

template<class T>
void Minheap<T>::SiftUp(int pos) {
    if ((pos - 1) / 2 < 0) return;
    int temppos = (pos - 1) / 2;
    if (heapArray[temppos] > heapArray[pos]) {
        swap(temppos, pos);
        SiftUp(pos);
    }

}

template<class T>
void Minheap<T>::Insert(T& item) {
    heapArray[CurrentSize] = item;
    SiftUp(CurrentSize);
    CurrentSize++;
}

template<class T>
T Minheap<T>::RemoveMin() {
    swap(0, --CurrentSize);
    SiftDown(0);
    return heapArray[CurrentSize];
}


