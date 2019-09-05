#pragma once

#include <utility>
#include <random>

/// Рандомит "y"
class RandomatorPriority
{
public:
    size_t operator()()
    {
        return dist( mt );
    }
private:
    std::mt19937_64 mt{ 1 };
    std::uniform_int_distribution< size_t > dist{ 1, (std::numeric_limits<size_t>::max)() };
};

/// Узел
template< class Kty, class Prio >
struct NodeTreap
{
    NodeTreap() = default;
    NodeTreap( const Kty& x, const Prio& y ) 
        : x( x ), y( y )
    {}
    ~NodeTreap()
    {
        delete left;
        delete right;
    }

    NodeTreap< Kty, Prio >* left = nullptr;
    NodeTreap< Kty, Prio >* right = nullptr;
    Kty x;
    Prio y;
    
};

template<
    class Kty,                          // x
    class Pr = std::less<Kty>,          // компаратор для x
    class Prio = size_t,                // y
    class PrPrio = RandomatorPriority   // рандоматор для y
>
class Treap
{
public:
    using key_type = Kty;
    using value_type = Kty;
    using key_compare = Pr;
    using priority_type = Prio;
    using priority_generator = PrPrio;
    using size_type = size_t;
    using reference = value_type & ;
    using const_reference = const value_type&;
    using node_type = NodeTreap < Kty, Prio >;

    ~Treap()
    {
        delete root;
    }
    /// есть элемент в дереве
    bool contains( const Kty& val )
    {
        node_type* cur_node = root;
        while( cur_node )
        {
            bool r = comparator( cur_node->x, val );
            bool l = comparator( val, cur_node->x );
            if( r == l )
                return true;
            if( r )
                cur_node = cur_node->right;
            else
                cur_node = cur_node->left;
        }
        return false;
    }
    void insert( const Kty& val )
    {
        root = add( root, val );
    }
    void erase( const Kty& val )
    {
        root = remove( root, val );
    }
private:
    /// слияние
    node_type* merge( node_type* left, node_type* right )
    {
        if( left == nullptr )
            return right;
        if( right == nullptr )
            return left;

        node_type* root = nullptr;
        if( left->y > right->y )
        {
            root = left;
            root->right = merge( root->right, right );
        }
        else
        {
            root = right;
            root->left = merge( left, root->left );
        }

        return root;
    }
    /// разделение
    std::pair< node_type*, node_type* > split( node_type* root, const Kty& x )
    {
        if( root == nullptr )
            return std::make_pair( nullptr, nullptr );

        if( comparator( x, root->x ) )
        {
            auto[left, right] = split( root->left, x );
            root->left = right;
            return std::make_pair( left, root );
        }
        else
        {
            auto[left, right] = split( root->right, x );
            root->right = left;
            return std::make_pair( root, right );
        }
    }
    /// добавление
    node_type* add( node_type* root, const Kty& x )
    {
        auto[l, r] = split( root, x );
        node_type* node = new node_type( x, randomator() );
        return merge( merge( l, node ), r );
    }
    /// удаление
    node_type* remove( node_type* root, Kty x )
    {
        Kty v = x;
        auto[l, r] = split( root, --v );
        auto[m, r2] = split( r, x );
        return merge( l, r2 );
    }

    Pr comparator;
    PrPrio randomator;
    NodeTreap< Kty, Prio >* root = nullptr;
};
