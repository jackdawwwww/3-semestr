#pragma once
#include<iostream>
#include<unordered_map>
namespace MySetEmulation {
	enum Trit { Unknown = 0, False = 1, True = 2 };
	class reference {};

	class Trit_set {
	private:
		unsigned int* tr_chain;
		size_t length;
		size_t capacity;

		void raise_chain(size_t);
		Trit complete_tr(Trit) const;//3

		class reference {
		private:
			size_t position;
			Trit_set* parent;
		public:
			reference(size_t, Trit_set*);
			~reference();
			Trit operator =(Trit value);//8
			operator Trit() const;//9
		};
	public:
		Trit_set();//15
		Trit_set(unsigned int);//14
		Trit_set(const Trit_set&);//13
		~Trit_set();

		size_t get_length()const;//12
		size_t get_capacity()const;//12
		size_t _length();//11

		void trim(unsigned int);//10
		void shrink();//11
	
		reference operator[](size_t);//8
		Trit operator[](size_t) const;
		Trit_set operator!();//7
		Trit_set operator&(const Trit_set &);//6
		Trit_set operator|(const Trit_set &);//5
		bool operator==(const Trit_set&)const;//4
		bool operator!=(const Trit_set&)const;//3
		size_t cardinality(Trit);//2
		std::unordered_map< Trit, size_t > cardinality();//1
	};
};
