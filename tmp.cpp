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
