
/*
    Example of use of BSON from C++.  Example is solely BSON, no MongoDB involved.
*/

#if defined(_WIN32)
#include <winsock2.h>
#include <windows.h>
#endif

#include "mongo/client/dbclient.h"

#include <iostream>
#include <vector>

using mongo::BSONElement;
using mongo::BSONObj;
using mongo::BSONObjBuilder;

void iter(BSONObj o) {
    /* iterator example */
    std::cout << "\niter()\n";
    for (BSONObj::iterator i(o); i.more();) {
        std::cout << ' ' << i.next().toString() << '\n';
    }
}

int main() {
    // As of legacy-1.0-rc1-pre, you must initialize the driver in order to use
    // the BSON library OID class.
    mongo::client::GlobalInstance instance;
    if (!instance.initialized()) {
        std::cout << "failed to initialize the client driver: " << instance.status() << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "build bits: " << 8 * sizeof(char*) << '\n' << std::endl;

    /* a bson object defaults on construction to { } */
    BSONObj empty;
    std::cout << "empty: " << empty << std::endl;

    /* make a simple { _id : <generated>, when : <now>, name : 'joe', age : 33.7 } object */
    {
        const mongo::OID generated = mongo::OID::gen();
        std::cout << "Generated an OID: " << generated << std::endl;

        BSONObjBuilder b;
        b.append("_id", generated);
        b.append("when", mongo::jsTime());
        b.append("name", "joe");
        b.append("age", 33.7);
        BSONObj result = b.obj();

        std::cout << "json for object with _id: " << result << std::endl;
    }

    /* make { name : 'joe', age : 33.7 } with a more compact notation. */
    BSONObj x = BSONObjBuilder().append("name", "joe").append("age", 33.7).obj();

    /* convert from bson to json */
    std::string json = x.toString();
    std::cout << "json for x:" << json << std::endl;

    /* access some fields of bson object x */
    std::cout << "Some x things: " << x["name"] << ' ' << x["age"].Number() << ' ' << x.isEmpty()
              << std::endl;

    /* make a bit more complex object with some nesting
       { x : 'asdf', y : true, subobj : { z : 3, q : 4 } }
    */
    BSONObj y = BSON("x"
                     << "asdf"
                     << "y" << true << "subobj" << BSON("z" << 3 << "q" << 4));

    /* print it */
    std::cout << "y: " << y << std::endl;

    /* reach in and get subobj.z */
    std::cout << "subobj.z: " << y.getFieldDotted("subobj.z").Number() << std::endl;

    /* alternate syntax: */
    std::cout << "subobj.z: " << y["subobj"]["z"].Number() << std::endl;

    /* fetch all *top level* elements from object y into a vector */
    std::vector<BSONElement> v;
    y.elems(v);
    std::cout << v[0] << std::endl;

    /* into an array */
    std::list<BSONElement> L;
    y.elems(L);

    BSONObj sub = y["subobj"].Obj();

    iter(y);
    return 0;
}