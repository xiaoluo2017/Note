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

// Question 7
/*
istream& getline (char* s, streamsize n );
istream& getline (char* s, streamsize n, char delim );

reference: http://www.cplusplus.com/reference/istream/istream/getline/
*/

// Question 8
class Car{
 
public:
	Car(){
		cout << "Car's Constructor\n";
	}
 
	Car(const Car &ob){ // copy constructor
		cout << "Car's Copy Constructor\n";
	}
 
	//Function that will receive object by value and return object by value.
 
	Car function(Car ob/*call copy constructor*/){
 
		//do something...
		
		//When a function returns an object of that class by value.
		return ob;// call copy constructor
	}
 
};
 
 
int main()
{	
	Car obj1; //call normal constructor
	
	Car obj2 = obj1; // call copy constructor 
	
	/*
	When an object of the same class type is passed by value
	as a parameter to a function.
	function returns an object by value
	*/
	Car obj3 = obj1.function(obj1);
 
 
	return 0;
}
