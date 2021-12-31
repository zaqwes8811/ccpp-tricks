

using T = int;

/// OpenCV
class Heap {
    struct CompareT {
        bool operator()(const T& t_1, const T& t_2) const {
            return t_2 < t_1;
        }
    };

    void insert(T value) {
//        /* If heap is full, then return without adding this element. */
//        if (count == length) {
//            return;
//        }
//
//        heap.push_back(value);
//        static CompareT compareT;  // Если stateless, то lazy!
//        std::push_heap(heap.begin(), heap.end(), compareT);
//        ++count;
    }
};


/// Hypertable