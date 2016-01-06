#include <qapplication.h>
#include <iostream>
#include <boost/archive/archive_exception.hpp>


using namespace std;
using namespace boost;
using namespace archive;

class Application: public QApplication {
   Q_OBJECT;
public:
   Application(int &c, char **v): QApplication(c, v) {}
   bool notify(QObject *rec, QEvent *ev) {
       try {
           return QApplication::notify(rec, ev);
       }
       catch (char const *str) {
           cout << "EXCEPTION: " << str << endl;
           return false;
       }
	   catch(archive_exception exp){
		   cout<<"SERIALIZATION EXCEPTION : "<<exp.what()<<endl;
	   }
       catch (...) {
           cout << "Unknown exception!" << endl;
           abort();
       }
   }
};