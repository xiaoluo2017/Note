// Question 4
#define language 437 
#if language < 400 
    #undef language
#else
    #define language 850 
    #ifdef language
        printf("%d", language);
    #endif 
#endif 

// Question 5.A
class Dog {
    private:
    string type;
    
    public:
    Dog(string type) {
        this->type = type;
    }
    
    string getType() {
        return type;
    }
};

int main()
{
    #define getType(x) x.getType()
    Dog d("Black");
    cout <<getType(d) << endl;
}

// Question 6
/*
STL Containers: <vector>, <list>, <map>, <set>, <stack>, <queue>, 
<unordered_map>, <unordered_set>, <deque>, <array>, <forward_list>, <bitset>

Sequence Containers: <vector>, <deque>, <list>

Associative Containers: <set>(including multiset), <map>(including multimap)

Container Adapters: <stack>, <queue>(including priority_queue)

reference: https://stackoverflow.com/questions/3873802/what-are-containers-adapters-c
*/
