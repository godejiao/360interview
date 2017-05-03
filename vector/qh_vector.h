#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_

#include<memory>
#include<utility>
namespace qh
{
	template<typename T>
	class vector {
	public:
		vector() :elements(nullptr), first_free(nullptr), cap(nullptr) {}
		vector(const vector&);
		vector &operator=(const vector&);
		~vector();
		void push_back(const T&);
		void pop_back();
		size_t size()const {
			return first_free - elements;
		}
		size_t capacity()const {
			return cap - elements;
		}
		T *begin()const {
			return elements;
		}
		T *end()const {
			return first_free;
		}
		void reserve(size_t);
		void resize(size_t);
		void resize(size_t, const T&);
		bool empty() { return begin() == end(); };
		void clear() { free(); };

		T& operator[](size_t index)
		{
			if (index >= size())throw runtime_error("out of the vector range");
			return elements[index];
		}
		
	private:
		static std::allocator<T>alloc;
		void chk_n_alloc() {
			if (size() == capacity()) {
				reallocate();
			}
		}
		std::pair<T*, T*>alloc_n_copy(const T*, const T*);
		void alloc_n_move(size_t);
		void free();
		void reallocate();
		T *elements;
		T *first_free;
		T *cap;
	};
	template<typename T>
	std::allocator<T>vector<T>::alloc;

	template<typename T>
	inline vector<T>::vector(const vector &s)
	{
		auto newdata = alloc_n_copy(s.begin(), s.end());
		elements = newdata.first;
		first_free = newdata.second;
	}

	template<typename T>
	vector<T> & vector<T>::operator=(const vector &rhs)
	{
		auto data = alloc_n_copy(rhs.begin(), rhs.end());
		free();
		elements = data.first;
		first_free = data.second;
		return *this;
	}

	template<typename T>
	inline vector<T>::~vector()
	{
		free();
	}

	template<typename T>
	inline void vector<T>::push_back(const T &s)
	{
		chk_n_alloc();
		alloc.construct(first_free, s);
		first_free++;
	}

	template<typename T>
	inline void vector<T>::pop_back()
	{
		if (elements) {
			auto p = first_free;
			first_free = --p;
			alloc.destroy(p);
		}
	}

	template<typename T>
	inline void vector<T>::reserve(size_t n)
	{
		if (n <= capacity()) {
			return;
		}
		alloc_n_move(n);
	}

	template<typename T>
	inline void vector<T>::resize(size_t n)
	{
		resize(n, T());
	}

	template<typename T>
	inline void vector<T>::resize(size_t n, const T & s)
	{
		if (n > size()) {
			if (n > capacity()) {
				reserve(n * 2);
			}
			for (size_t i = size(); i != n; ++i) {
				alloc.construct(first_free++, s);
			}
		}
		else if (n < size()) {
			while (first_free != elements + n) {
				alloc.destroy(--first_free);
			}
		}
	}

	template<typename T>
	inline std::pair<T*, T*> vector<T>::alloc_n_copy(const T * b, const T * e)
	{
		auto data = alloc.allocate(e - b);
		return { data,uninitialized_copy(b,e,data) };
	}

	template<typename T>
	inline void vector<T>::alloc_n_move(size_t n)
	{
		auto newdata = alloc.allocate(n);
		auto dest = newdata;
		auto elem = elements;
		for (size_t i = 0; i != size(); ++i) {
			alloc.construct(dest++, std::move(*elem++));
		}
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + n;
	}

	template<typename T>
	inline void vector<T>::free()
	{
		if (elements) {
			for (auto p = first_free; p != elements;) {
				alloc.destroy(--p);
			}
			alloc.deallocate(elements, cap - elements);
		}
	}

	template<typename T>
	inline void vector<T>::reallocate()
	{
		auto newcapacity = size() ? 2 * size() : 1;
		auto newdata = alloc.allocate(newcapacity);
		auto dest = newdata;
		auto elem = elements;
		for (size_t i = 0; i != size(); ++i) {
			alloc.construct(dest++, std::move(*elem++));
		}
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + newcapacity;
	}
}

#endif


