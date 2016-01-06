#ifndef RESSOURCEMANAGER_H
#define RESSOURCEMANAGER_H

#include <map>
#include <string>
#include <iostream>

class Ressource;
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;

class RessourceManager{
	private:
		RessourceManager();
		~RessourceManager();
		static RessourceManager* instance;
		map<string,shared_ptr<Ressource>> ressourceRegistery;

		template< class T >	
		shared_ptr<T> createAndLoad(const string& path)
		{
			shared_ptr<T> newRessource(new T());
			newRessource->load(path);

			return newRessource;
		}
	
	public:

		static RessourceManager* getInstance(){
			if(!instance){
				try{
					instance = new RessourceManager();
				}catch( char * str ) {
					cout << "Exception raised: " << str << '\n';
				}
			}
			return instance;
		};

		template< class T >	
		shared_ptr<T> loadRessource(const string& path)
		{
			map<string, shared_ptr<Ressource> >::iterator resIt = ressourceRegistery.find(path);

			if( resIt != ressourceRegistery.end() )
				return static_pointer_cast<T,Ressource>( resIt->second );
			else{
				shared_ptr<T> newRessource = createAndLoad<T>( path );

				pair<string,shared_ptr<Ressource> > newEntry(
																path, 
																static_pointer_cast<Ressource,T>(newRessource) 
															);
				ressourceRegistery.insert( newEntry );
				return newRessource;
			}
		}

		void releaseRessources(){
			this->ressourceRegistery.clear();
		}

		void shutDown(){
			delete this;
		}
};

#endif

