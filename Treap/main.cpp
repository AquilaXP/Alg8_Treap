#include <iostream>

#include "Treap.h"

#define CHECK( x ) Check( x,#x " (" __FUNCSIG__  ")" );
void Check( bool b, const char* str )
{
    if( b == false )
        throw std::runtime_error( str );
}

int main()
{
    try
    {
        Treap<int> treap;
        treap.insert( 10 );
        treap.insert( 11 );
        treap.insert( 9 );
        treap.insert( 1 );
        treap.insert( 16 );

        CHECK( treap.contains( 10 ) );
        CHECK( treap.contains( 11 ) );
        CHECK( treap.contains( 9 ) );
        CHECK( treap.contains( 1 ) );
        CHECK( treap.contains( 16 ) );
        CHECK( treap.contains( 12 ) == false );

        treap.erase( 9 );
        CHECK( treap.contains( 10 ) );
        CHECK( treap.contains( 11 ) );
        CHECK( treap.contains( 9 ) == false );
        CHECK( treap.contains( 1 ) );
        CHECK( treap.contains( 16 ) );
        CHECK( treap.contains( 12 ) == false );

        treap.erase( 16 );
        CHECK( treap.contains( 10 ) );
        CHECK( treap.contains( 11 ) );
        CHECK( treap.contains( 9 ) == false );
        CHECK( treap.contains( 1 ) );
        CHECK( treap.contains( 16 ) == false );
        CHECK( treap.contains( 12 ) == false );
    }
    catch( ... )
    {
        std::cerr << "Vse ploho!" << '\n';
        return 1;
    }
    
    return 0;
}
