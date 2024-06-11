#include "token.h"

class STEntry 
{
    public:
        Token* token;
        // string type;
        bool reserved;
    
        STEntry();
        STEntry(Token*);   
        // STEntry(Token*, string);
        STEntry(Token*, bool);
};
