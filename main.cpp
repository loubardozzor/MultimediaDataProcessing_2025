define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cassert>
#include <crtdbg.h>

// Comparison function for qsort
int compare(const void *a, const void *b) 
{
    if (*(int *)a < *(int *)b) {
        return -1;
    }
    if (*(int *)a > *(int *)b) {
        return 1;
    }
    return 0;
}

struct vector {
    size_t size_, capacity_;
    int *data_;

    // default constructor
    vector() {
        size_ = 0;
        capacity_ = 10;
        data_ = (int*)malloc(capacity_ * sizeof(int));
    }
    // copy constructor
    vector(const vector &other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = (int *)malloc(capacity_ * sizeof(int));
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    //vector &operator=(const vector &other) {
    //    if (this == &other) {
    //        return *this;
    //    }
    //    free(data_);
    //    size_ = other.size_;
    //    capacity_ = other.capacity_;
    //    data_ = (int *)malloc(capacity_ * sizeof(int));
    //    for (size_t i = 0; i < size_; ++i) {
    //        data_[i] = other.data_[i];
    //    }
    //    return *this;
    //}
    vector& operator=(const vector &other) {
        if (capacity_ < other.size_) {
            free(data_);
            capacity_ = other.capacity_;
            data_ = (int *)malloc(capacity_ * sizeof(int));
        }
        size_ = other.size_;
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
        return *this;
    }
    // destructor
    ~vector() {
        free(data_);
    }
    void push_back(int num) {
        if (size_ == capacity_) {
            capacity_ *= 2;
            data_ = (int*)realloc(data_, capacity_ * sizeof(int));
        }
        data_[size_] = num;
        size_++;
    }
    size_t size() const {
        return size_;
    }
    int at(size_t index) const {
        assert(index < size_);
        return data_[index];
    }
};

void print(FILE *f, const vector &v)
{
    for (size_t i = 0; i < v.size(); i++) {
        fprintf(f, "%d\n", v.at(i));
    }
}

int main(int argc, char *argv[]) 
{
    {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
            return 1;
        }

        FILE *input = fopen(argv[1], "r");
        if (!input) {
            perror("Error opening input file");
            return 1;
        }

        FILE *output = fopen(argv[2], "w");
        if (!output) {
            perror("Error opening output file");
            fclose(input);
            return 1;
        }

        vector numbers;

        int num;
        while (fscanf(input, "%d", &num) == 1) {
            numbers.push_back(num);
        }
        fclose(input);

        int x, y;
        x = 5;
        (y = x) = 7;
        x = x;

        vector original, another;
        another = original = numbers;
        numbers = numbers;

        qsort(numbers.data_, numbers.size(), sizeof(int), compare);

        print(output, numbers);

        fclose(output);
    }
    _CrtDumpMemoryLeaks();
    return 0;
}