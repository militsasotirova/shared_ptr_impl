template<class T>
class shared_ptr_impl {
    // Templates can only be implemented in the header file.
    // https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
public:
    // Constructs a shared pointer with no managed object.
    shared_ptr_impl(): _managedObj(nullptr), _refCount(new long(0)) {}

    // explicit keyword is used to mark constructors to not implicitly convert types in C++
    explicit shared_ptr_impl(T* ptr): _managedObj(ptr), _refCount(new long(1)) {}

    shared_ptr_impl(const shared_ptr_impl& r):
        _managedObj(r.get()),
        _refCount(r._refCount) {
            (*this->_refCount)++;
        }

    ~shared_ptr_impl() {
        (*this->_refCount)--;
        if ((*this->_refCount) == 0) {
            if (_managedObj) {
                delete _managedObj;
            }
            delete _refCount;
        }
    }

    // Copy assignment
    shared_ptr_impl& operator=(shared_ptr_impl& r) {
        // If *this already owns an object and it is the last shared_ptr owning it, and r is not the same as *this, the object is destroyed through the owned deleter.
        if (_managedObj != nullptr && this->unique() && *this != r) {
            delete _managedObj;
        }
        _managedObj = r.get();
        _refCount = r._refCount;
        if (_managedObj) {
            (*this->_refCount)++;
        }
        return *this;
    }

    T* get() const {
        return _managedObj;
    }

    T& operator*() const {
        return *get();
    }

    T* operator->() const {
        return get();
    }

    long use_count() const {
        return (*this->_refCount);
    }

    bool unique() const {
        return (*this->_refCount) == 1;
    }

    operator bool() const {
        return get() != nullptr;
    }

private:
    // Number of shared_ptr objects referring to the same managed object.
    long* _refCount;

    // Pointer to managed object.
    T* _managedObj;
};

template<class T>
shared_ptr_impl<T> make_shared() {
    return shared_ptr_impl<T>(new T());
}
