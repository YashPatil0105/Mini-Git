#include "core/Hash.hpp"
#include <sstream>
#include <iomanip>

using namespace std;

// Deprecated: Use SHA1::from_string instead
string HashUtil::hashData(const vector<char>& data){
    // hash<string> hasher;
    // string s(data.begin(), data.end());
    // size_t hashValue = hasher(s);
    // stringstream ss;
    // ss << hex << hashValue;
    // return ss.str(); // dummy SHA
    return "[DEPRECATED]";
}