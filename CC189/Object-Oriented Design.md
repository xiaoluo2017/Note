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
