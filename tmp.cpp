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
