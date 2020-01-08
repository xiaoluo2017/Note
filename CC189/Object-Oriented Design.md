### 7.0
```
// Singleton Class
class Singleton
{
public:
    static Singleton* getInstance()
    {
        if (_instance == NULL)
            _instance = new Singleton();

        return _instance;
    }
    static void resetInstance()
    {

        delete _instance;
        _instance = NULL;
    }
private:
    Singleton() {};
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
    ~Singleton() {};
    static Singleton* _instance;
};

Singleton* Singleton::_instance = 0;
```
> ref: https://stackoverflow.com/questions/8699434/how-to-delete-singleton-pointer/8699599

```
// Factory Method
enum AnimalType { DogType, CatType };

class Animal
{
public:
    static Animal* createAnimal(AnimalType type);
};

class Dog : public Animal {};

class Cat: public Animal {};

Animal* Animal::createAnimal(AnimalType type)
{
    if (type == AnimalType::DogType)
    {
        return new Dog();
    }
    else if (type == AnimalType::CatType)
    {
        return new Cat();
    }
    return NULL;
}
```

```
// Adapter
// 适配的类的API转换成为目标类的API, 使原本接口不匹配而无法一起工作的两个类能够在一起工作
class Shape 
{
public:
    virtual int calculateArea(int r) = 0;
};

class Square : public Shape 
{
public:
    int calculateArea(int r) override
    {
        return r * r;
    }
};

class Circle 
{
public:
    double calculateCircularArea (int r)
    {
        return 3.14 * r * r;
    }
};

class CirCleAdaptor : public Circle, public Shape 
{
public:
    int calculateArea(int r) override
    {
        return (int)calculateCircularArea(r);
    }
};

int main() {
    Shape* circle = new CirCleAdaptor();
    circle->calculateArea(5);
    
    Shape* square = new Square();
    square->calculateArea(5);
}
```
> ref: https://stackoverflow.com/questions/3478225/when-do-we-need-adapter-pattern

```
// observer pattern
import java.util.*; 

class Cow extends java.util.Observable
{
    public void speak() {
        System.out.println("Cow maaaauuu");
        setChanged(); 
        notifyObservers();
    }
}

class Farmer implements java.util.Observer
{
    public void update(Observable o, Object arg) {
        System.out.println("Farmer heard");
    }
}

public class Main
{
    public static void main(String args[]) {
        Cow c = new Cow();
        Farmer f = new Farmer();
        c.addObserver(f);
        c.speak();
    }
}
```
> ref: https://stackoverflow.com/questions/10069299/observer-design-pattern

* Template Method: 
   * In virtual base classes, define the methods that need to provide implementation in subclasses as pure virtual functions
> ref: https://stackoverflow.com/questions/22015933/understanding-template-method-pattern

* Strategy Pattern:
   * It delegates the behavior of the function to another class(pass in object of another class):
> ref: https://stackoverflow.com/questions/91932/how-does-the-strategy-pattern-work

### 7.5

### 7.7
* class UserManager
   * private: 
     * UserManager();
     * static UserManager _instance;
     * unordered_map<int, User> idToUserMap;
     * unordered_map<int, string> idToUsernameMap;
   * public:
     * static UserManager* getInstance();
     * static void resetInstance();
     * idToUserMap, idToUsernameMap setter & getter
* class User
   * private: 
     * int id; 
     * string username; 
     * Date date;
     * vector<User> friendsList; 
     * vector<int> groupChats; 
     * userStatusType status; 
     * string hashedPassword; 
     * unordered_map<int, int> privateChatMap;
   * public:
     * User(int id, string username);
     * void login(string username, string hashedPassword);
     * void logout(string username);
     * void sendRequest(Request r);
     * void receiveRequest(Request r);
     * void addToGroupChat(int id);
     * int startPrivateChat(User u);
     * void sendMessage(int id, string content);
     * id, username, date, friendsList, groupChats getter;
     * status setter & getter
* class Conversation
   * private: int id; vector<User> participants; vector<Message> messages;
   * public:
     * void addMessage(Message m);
     * id, participants, messages getter
* class PrivateChat : public Conversation
   * public:
     * PrivateChat(User u1, User u2);
* class GroupChat : public Conversation
   * public:
     * void addParticipant(User u);
     * void removeParticipant(User u);
* class Message
   * private: User u; Date d; string content
   * public:
     * Message(User u, string s);
     * u, d, content getter
* class Request
   * private: User fromUser; User toUser; Date date; requestStatusType status
   * public:
     * Request(User fu, User tu);
     * fromUser, toUser, date, status getter   
* Enum userStatusType { available, idle, busy, away, offline }
* Enum requestStatusType { unread, read, accept, reject }

### 7.11
* class Entry
   * private: Entry parent; long createdTime; long lastUpdateTime; long lastAccessTime; string name
   * public:
     * Entry(Entry p, string n);
     * bool delete();
     * int getSize() = 0;
     * string getFullPath();
     * name, createdTime, lastUpdateTime, lastAccessTime getter
     * name setter
* class File : public Entry
   * private: string content; int size
   * public:
     * File(Entry p, string n, string c);
     * int getSize();
     * content getter, setter
* class Directory : public Entry
   * private: vector<Entry> _v
   * public:
     * Directory(Entry p, string n);
     * void addEntry(Entry e);
     * void deleteEntry(Entry e);
     * int getSize();
