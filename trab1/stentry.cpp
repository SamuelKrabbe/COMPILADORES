#include "stentry.h"

STEntry::STEntry()
{}
        
STEntry::STEntry(Token* tok)
{
    token = tok;
    // type = "";
    reserved = false;
}

// STEntry::STEntry(Token* tok, string t)
// {
//     token = tok;
//     type = t;
//     reserved = false;
// }

STEntry::STEntry(Token* tok, bool res)
{
    token = tok;
    // type = "";
    reserved = res;
}