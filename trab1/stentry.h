#include "token.h"

class STEntry 
{
    public:
        Token* token;
        int lvalue;
        bool reserved;
    
        STEntry();
        STEntry(Token*);   
        STEntry(Token*, int);
        STEntry(Token*, bool);
};
