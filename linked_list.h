#pragma once

#define LOG(x) std::cout << __FUNCTION__ << " :" << x << std::endl;

namespace linked_list
{
	template <typename D>
	class node
	{
	public: // constructor
		node() = delete;
		node(D data) : m_data(data)
		{
			LOG("data = " << m_data);
		}

	public:
		static node* create_node(D data)
		{
			return new node(data);
		}

		static void free_node(node* n) {
			delete n;
			n = nullptr;
		}

		node* get_next() { return m_next; }
		D& get_data() { return m_data; }
		void set_next(node* n) { m_next = n; }

	private:
		D m_data;
		node* m_next = nullptr;
	};

	template <typename T, typename D>
	class linked_list
	{
		T* head{ nullptr };

	public:
		void print() {

			auto itr = head;

			while (itr != nullptr) {
				std::cout << "Data = " << itr->get_data() << std::endl;
				itr = itr->get_next();
			}
		}
		T* end()
		{
			T* itr = head;
			while (itr->get_next() != nullptr)
			{
				itr = itr->get_next();
			}
			return itr;
		}

		void add(D data)
		{
			if (head == nullptr)
			{
				head = node<D>::create_node(data);
			}
			else
			{
				if (auto last = end())
				{
					last->set_next(node<D>::create_node(data));
				}
			}
		}

		void free(T& arg_node) {
			arg_node.free_node();
		}
	};

	void test_linked_list()
	{
		LOG("TEST NODE CREATION");
		auto n = node<unsigned int>::create_node(30);
		LOG("TEST LINKED LIST CREATION");
		linked_list<node<unsigned int>, unsigned int> ll;
		ll.add(10);
		ll.add(20);
		ll.add(30);
		ll.print();
	}
} // namespace linked_list