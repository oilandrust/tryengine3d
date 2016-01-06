#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <string>

using namespace std;

class Ressource{

protected:
	string ressourceName;

public:
	Ressource();

	virtual ~Ressource();

	virtual void load(const string& filename){
		ressourceName = filename;
	}
};

#endif
