#ifndef RTTI_H
#define RTTI_H

#include <string>
using namespace std;

class RTTI{

	public:
		RTTI (const string& name, const RTTI* baseType);
		~RTTI ();

		const string& getName () const;
		bool isExactly (const RTTI& type) const;
		bool isDerived (const RTTI& type) const;

	private:
		string name;
		const RTTI* baseType;
};

#endif