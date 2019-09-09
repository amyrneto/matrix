#pragma once
#include <vector>

template <class T> class matrix
{
public:
	matrix(void){
		_size_x = 0;
		_size_y = 0;
	};
	~matrix(void){};
	matrix(unsigned int size_x, unsigned int size_y, T value)	{
		unsigned int matSize = size_x * size_y;
		_data = std::vector<T> (matSize, value);
		_size_x = size_x;
		_size_y = size_y;
	};

	// Copy Constructor
	matrix(matrix<T> &other){
		this->_size_x = other.Get_size_x();
		this->_size_y = other.Get_size_y();
		unsigned int matSize = _size_x * _size_y;
		_data = std::vector<T> (matSize);
		for(unsigned int x=0; x<_size_x; x++){
			for(unsigned int y=0; y<_size_y; y++){
				SetElement(x, y, other.GetElement(x, y));
			}
		}
	};

	T GetElement(unsigned int x, unsigned int y){
		unsigned int i = _size_x * y + x;
		return _data[i];
	};
	void SetElement(unsigned int x, unsigned int y, T e){
		unsigned int i = _size_x * y + x;
		_data[i] = e;
	};
	unsigned int Get_size_x(){return _size_x;};
	unsigned int Get_size_y(){return _size_y;};
	std::vector<T> operator[](unsigned int e){
		std::vector<T> line = new std::vector<T>();
		typename std::vector<T>::iterator it;
		
		it = _data.begin() + (e * _size_x);
		line.assign(it, it + _size_x);
		return line;
	};
	bool Resize(unsigned int size_x, unsigned int size_y, T value){
		if (_data.empty()){
			unsigned int matSize = size_x * size_y;
			_data = std::vector<T> (matSize, value);
			_size_x = size_x;
			_size_y = size_y;
			return true;
		} else {
			bool result = false;
			// If X dimension changed
			if (size_x != _size_x)
			{
				//////////////////////////////////////////
				// Resize X dimension
				if (size_x < _size_x)
				{
					// Delete elements
					unsigned int delta = _size_x - size_x;
					typename std::vector<T>::iterator it;
					for (unsigned int i=0; i<_size_y; i++)
					{
						it = _data.begin() + (i*size_x) + size_x;
						_data.erase(it, it+delta);
					}
				} else {
					// Insert Elements
					unsigned int delta = size_x - _size_x;
					typename std::vector<T>::iterator it;
					for (unsigned int i=0; i<_size_y; i++)
					{
						it = _data.begin() + (i*size_x) + _size_x;
						_data.insert(it, delta, value);
					}
				}
				_size_x = size_x;
				result = true;
			}
			// If Y dimension changed
			if (size_y != _size_y)
			{
				//////////////////////////////////////////
				// Resize Y dimension
				unsigned int new_size = _size_x * size_y;
				_data.resize(new_size, value);
				_size_y = size_y;
				result = true;
			}
			return result;
		}
	};

	// Perform a matrix product
	matrix<T> operator*(matrix<T> &other){
		matrix<T> result;
		int s = other.Get_size_x();
		if( this->_size_y == s ){
			// perform matrix product
			T val=0;
			result = matrix<T>(this->_size_x, other.Get_size_y(), val);
			for (unsigned int i=0; i<this->_size_x; i++){
				for (unsigned int j=0; j<other.Get_size_y(); j++){
					T sum=0;
					for(unsigned int k=0; k<s; k++){
						//T n;
						//n = other.GetElement(k,j);
						sum += GetElement(i,k) * other.GetElement(k,j);
					}
					result.SetElement(i, j, sum);
				}
			}
		}
		return result;
	};

	// Perform a matrix product with a single line matrix.
	std::vector<T> operator*(const std::vector<T>& other){
		std::vector<T> result = std::vector<T> ();
		if( this->_size_y == other.size() ){
			// perform matrix product with a vector
			result = std::vector<T> (this->_size_x);
			for (unsigned int i=0; i<this->_size_x; i++){
				T sum=0;
				for(unsigned int k=0; k<this->_size_y; k++){
					sum += this->GetElement(i,k) * other[k];
				}
				result[i] = sum;
			}
		}
		return result;
	};

private:
	std::vector<T> _data;
	unsigned int _size_x, _size_y;
};


	///////////////////////////////////////////////////////////////////////////
	// Tests for class matrix!
	/*************************************************************************
	matrix<float> m1(4,3,1.0f), m2(3,4,2.0f), m3;
	std::vector<float> v (3, 1.5f), u(3,0.0f);

	m1.SetElement(0,0,2.0f);
	m1.SetElement(1,0,0.0f);
	m1.SetElement(2,0,0.0f);
	m1.SetElement(3,0,0.0f);
	m1.SetElement(0,1,0.0f);
	m1.SetElement(1,1,2.0f);
	m1.SetElement(2,1,0.0f);
	m1.SetElement(3,1,0.0f);
	m1.SetElement(0,2,0.0f);
	m1.SetElement(1,2,0.0f);
	m1.SetElement(2,2,2.0f);
	m1.SetElement(3,2,2.0f);
	u = m1*v;
	//u[0]=1.5f;

	m3 = m1*m2;

	/*************************************************************************/

