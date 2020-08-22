#pragma once

namespace linked_list {
	template <typename T>
	class node {
	public:
		std::unique_ptr<node> get_next() { return m_next; }
		T& get_data() { return m_data; }
	private:
		T m_data;
		std::unique_ptr<node> m_next;
	};

	template <typename T>
	class linked_list {
		T node;

		T* head{ nullptr };

		void add(T& node) {
			if (head == nullptr) {

			}
		}
	};
}