#include <cstdlib>
#include <cstdint>
#include <cassert>


template <typename T, uint8_t pow2size>
class P2ARR{
	public:
		T& operator[](size_t index){
			return data[index & ((1<<pow2size) - 1)];
		}
	private:
	T data[1<<(pow2size)];
};

static_assert(sizeof(P2ARR<char, 3>) == 8, "P2ARR size check failed.");

template <typename T>
class P2VEC{
	public:
		P2VEC<T>(uint16_t initial_pow2){
			data = new T[1<<initial_pow2];sz = initial_pow2;
		}
		P2VEC<T>(){data = new T[1]; sz = 0;}
		P2VEC<T>(T q){data = new T[1]; data[0] = q; sz = 0;}
		T& operator[](size_t index){return data[index & ((1<<sz) - 1)];}

		void grow(uint16_t additional){
			additional &= 255; //Safety. Like, it'll throw... but...
			auto data_old = data;
			data = new T[1<<(sz + additional)];
			memcpy(data, data_old, sizeof(T) * (1<<sz));
			delete [] data_old;
			sz += additional;
		}
		uint8_t p2size() {return sz;}
		size_t size() {return (size_t)1<<((size_t)sz);}
		~P2VEC<T>(){delete [] data;}
	private:
	T* data;
	uint8_t sz;
};
