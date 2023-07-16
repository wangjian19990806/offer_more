#include <iostream>
#include <memory>

using namespace std;

template <typename T>
class smartpointer {
public:
	//构造函数
	smartpointer(T* ptr = NULL) :_ptr(ptr)
	{
		if (_ptr)//如果实例化了，就建立计数器
		{
			_count = new size_t(1);
		}
		else {
			_count = new size_t(0);
		}
	}

	//拷贝构造函数（相同的话就不拷贝）
	smartpointer(const smartpointer& smp)
	{
		if (this == &smp)
			return;
		else {
			this->_ptr = smp._ptr;
			this->_count = smp._count;
			(*this->_count)++;
		}
	}

	//赋值函数(左值减少，右值增加)  //特别说明：不是构造函数
	smartpointer& operator = (const smartpointer& smp)
	{
		if (this->_ptr == smp._ptr)
		{
			return *this;
		}

		if (this->_ptr)
		{
			(*this->_count)--;
			if ((*this->_count) == 0)
			{
				delete this->_ptr;
				delete this->_count;
			}
		}

		this->_ptr = smp._ptr;
		this->_count = smp._count;
		(*this->_count)++;
		return *this;
	}

	//重载->和*
	T& operator -> ()
	{
		assert(this->_ptr == NULL);
		return (*this->_ptr);
	}

	T* operator * ()
	{
		assert(this->_ptr == NULL);
		return this->_ptr;
	}

	size_t use_count()
	{
		return *this->_count;
	}

	//析构函数
	~smartpointer()
	{
		if (*this->_count == 0)
		{
			delete this->_ptr;
			delete this->_count;
			cout << "释放" << endl;
		}
		else {
			(*this->_count)--;
			if (*this->_count == 0)
			{
				delete this->_ptr;
				delete this->_count;
				cout << "释放" << endl;
			}
		}
	}
private:
	T* _ptr;
	size_t* _count;
};

int main() {
	{

		//只初始化了两次
		smartpointer<int> sp(new int(10));

		smartpointer<int> sp2(sp);

		smartpointer<int> sp3(new int(20));
		sp2 = sp3;
		std::cout << sp.use_count() << std::endl;
		std::cout << sp3.use_count() << std::endl;

		//SmartPointer<int> sp(NULL);
		//std::cout << sp.use_count() << std::endl;

	}
	system("pause");
	return 0;
}