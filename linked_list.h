#pragma once

#define LOG(x) std::cout << std::hex << __FUNCTION__ << " :" << x << std::dec << std::endl;
namespace linked_list {
	template <typename D>
	class node {
	public: // constructor
		node( ) = delete;
		node( D data ) : m_data( data ) {
			LOG( "data = " << m_data );
		}

	public:
		static node* create_node( D data ) {
			return new node( data );
		}

		static void free_node( node* n ) {
			LOG( ":: Free node with data " << n->get_data( ) );
			delete n;
			n = nullptr;
		}

		node* get_next( ) { return m_next; }
		D& get_data( ) { return m_data; }
		void set_next( node* n ) { m_next = n; }
		void print( ) {
			LOG( "Node data is " << get_data( ) );
		}
	private:
		D m_data;
		node* m_next = nullptr;
	};

	template <typename T , typename D>
	class linked_list {
	public: //destructor
		~linked_list( ) {
			auto itr = head;

			while ( itr != nullptr ) {
				auto del_this = itr;
				itr = itr->get_next( );
				node<D>::free_node( del_this );
			}
		}

	private:
		T* head { nullptr };

	public:
		T* get_head( ) { return head; }

		void print( ) {
			auto itr = head;

			while ( itr != nullptr ) {
				LOG( "Data = " << itr->get_data( ) );
				itr = itr->get_next( );
			}
		}
		T* end( ) {
			LOG( "" );
			T* itr = head;
			while ( itr->get_next( ) != nullptr ) {
				itr = itr->get_next( );
			}
			return itr;
		}

		void add( D data ) {
			LOG( "" );
			if ( head == nullptr ) {
				head = node<D>::create_node( data );
			} else {
				if ( auto last = end( ) ) {
					last->set_next( node<D>::create_node( data ) );
				}
			}
		}

		void free( T& arg_node ) {
			LOG( ":: Free node with data - " << arg_node.get_data( ) );
			node<D>::free_node( &arg_node );
		}

		void free( D d ) {
			LOG( "Attempting to find node with data d" );

			auto itr = head;
			T* prev = nullptr;
			while ( itr->get_data( ) != d ) {
				prev = itr;
				itr = itr->get_next( );
				if ( itr == nullptr ) {
					LOG( d << " Not found" );
					return;
				}
			}

			std::cout << "found data " << d << " at " << ( uintptr_t ) &itr << std::endl;
			prev->set_next( itr->get_next( ) );
			free( *itr );
		}
	};

	//  practice questions
	template<typename T , typename D>
	T* find_middle_of_linked_list( linked_list<T , D>& ll ) {
		LOG( "" );
		auto head = ll.get_head( );
		auto itr_fast = head;
		auto itr_slow = head;

		while ( itr_fast != nullptr ) {
			if ( itr_fast->get_next( ) == nullptr ) { break; }
			itr_fast = itr_fast->get_next( )->get_next( );
			itr_slow = itr_slow->get_next( );
		}

		itr_slow->print( );
		return itr_slow;
	}

	template<typename T , typename D>
	void delete_middle_of_linked_list( linked_list<T , D>& ll ) {
		//ll.free( find_middle_of_linked_list( ll ) );
	}

#define DEF_TEST(x) LOG(x)
	void test_linked_list( ) {
		DEF_TEST( "TEST -- NODE Create and Free" ) {
			auto n = node<unsigned int>::create_node( 30 );
			node<unsigned int>::free_node( n );
		}

		DEF_TEST( "TEST -- LL -- Creation and Free" ) {
			linked_list<node<unsigned int> , unsigned int> ll;
			ll.add( 10 );
			ll.add( 20 );
			ll.add( 30 );
			ll.print( );
			ll.free( 50 );
			ll.free( 20 );
			ll.add( 40 );
			ll.add( 50 );
			ll.add( 70 );
			ll.add( -30 );

			find_middle_of_linked_list( ll );
			delete_middle_of_linked_list( ll );
			ll.print( );
			LOG( "Now the ll will be deleted" );
		}
	}
} // namespace linked_list