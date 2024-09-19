# **Object Oriented Programming in C++**

**Object-Oriented Programming (OOP)** is a programming paradigm that uses "objects" to model the real world. In C++, OOP is based on four fundamental principles:

### **1\. Encapsulation**

* **Definition**: It is the practice of grouping data (attributes) and methods (functions) that operate on that data into a single unit, or class.  
* **Benefits**: It protects the internal state of an object and allows users to interact with it through public interfaces.

  ### **2\. Inheritance**

* **Definition**: It is the mechanism by which one class can inherit properties and methods from another class. This allows for the creation of a class hierarchy.  
* **Benefits**: It facilitates code reuse and the creation of hierarchical relationships.

  ### **3\. Polymorphism**

* **Definition**: It is the ability of functions to take different forms. In C++, this can be achieved through function overloading and the use of virtual functions.  
* **Benefits**: It allows a single interface to be used for different data types.

  ### **4\. Abstraction**

* **Definition**: It is the process of simplifying a complex system by highlighting essential features and hiding non-essential ones.  
* **Benefits**: It makes it easier to understand and use complex objects by focusing on what they do, rather than how they do it.


**Class:**  
It is a user-defined data type, which holds its own data members and member functions, which can be accessed and used by creating an instance of that class.

**Object:**  
An Object is an identifiable entity with some characteristics and behavior. An Object is an instance of a Class. When a class is defined, no memory is allocated but when it is instantiated memory is allocated.

---

**Stack Memory Allocation**

Stack memory is a region of memory used to store local variables and function data. It is managed automatically.

### **Characteristics:**

* **Fixed Size**: Memory in the stack has a predefined and limited size, determined at compile time.  
* **Fast Storage**: Memory allocation and deallocation are very fast (LIFO: Last In, First Out).  
* **Local Scope**: Variables in the stack are local to the function in which they are declared and are automatically destroyed when the function ends.  
* **No Manual Release Required**: You do not need to use `delete` to free the memory.

**Heap Memory Allocation**

Heap memory is a region of memory used for dynamic allocation. Programmers must manage this memory manually.

### **Characteristics:**

* **Variable Size**: Memory in the heap can grow and shrink at runtime, depending on the program's needs.  
* **Slower Storage**: Allocation and deallocation are slower than in the stack due to additional management.  
* **Global Scope**: Data in the heap can be accessed from anywhere in the program, as long as you have a valid pointer.  
* **Manual Release Required**: You must use `delete` to free the memory when it is no longer needed, or you may have memory leaks.

### 

### 

### 

### 

---

### 

### **Pointers:**

 A pointer is a variable that stores the memory address of another variable.

* **Syntax**: Declared using the `*` operator.  
* **Characteristics**:  
  * **Can be null**: A pointer can point to nothing (be `nullptr`).  
  * **Pointer arithmetic**: You can perform arithmetic operations to move the pointer to different memory addresses.  
  * **Dereferencing**: To access the pointed value, the `*` operator is used (e.g., `*ptr`).  
  * **Manual management required**: If `new` is used to allocate memory, `delete` must be used to free that memory.  
* **Usage**: Useful for arrays, dynamic data structures, and when you need to manipulate memory addresses directly.

### **References:**

A reference is an alias for another variable. It is not an independent variable.

* **Syntax**: Declared using the `&` operator.  
* **Characteristics**:  
  * **Cannot be null**: A reference must always refer to a valid object and cannot be reassigned to refer to another object.  
  * **No dereferencing needed**: The value can be accessed directly without needing a special operator.  
  * **Less overhead**: It does not involve pointer arithmetic, which can make the code more readable.  
* **Usage**: Commonly used in functions to pass arguments without copying, or to overload operators.

---

### **What are Smart Pointers?**

Smart pointers are objects that act like pointers but also automatically manage memory. They provide a safer and more convenient way to handle dynamic memory, helping to avoid leaks and common errors in memory management.

### **Types of Smart Pointers**

**std::unique\_ptr**:

* **Definition**: Represents a pointer that owns a unique resource. It cannot be copied, only moved.  
  * **Usage**: Ideal for managing resources that should not be shared.  
  * **Automatic Destruction**: Automatically releases when the `unique_ptr` goes out of scope.  
  * **Syntax**: `std::unique_ptr<MyClass> ptr(new MyClass());`

**std::shared\_ptr**:

* **Definition**: Represents a pointer that can be shared among multiple `shared_ptr`s. It uses reference counting to manage memory.  
  * **Usage**: Useful when multiple parts of your code need to share ownership of a resource.  
  * **Automatic Destruction**: Releases when there are no more `shared_ptr`s pointing to the resource.  
  * **Syntax**: `std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();`

**std::weak\_ptr**:

* **Definition**: A pointer that does not affect the reference count of a `shared_ptr`. It is used to avoid reference cycles.  
  * **Usage**: Useful for referring to a resource that may be freed without keeping it alive.  
  * **Conversion to `shared_ptr`**: Must be converted to `shared_ptr` before accessing the resource.  
  * **Syntax**: `std::weak_ptr<MyClass> weakPtr = ptr1; // ptr1 is a shared_ptr`

  ### 

### 

### **Advantages of Smart Pointers**

* **Prevention of Memory Leaks**: Ensure that memory is automatically released when it is no longer needed.  
* **Safety**: Reduce the risk of common errors such as accessing freed memory (dangling pointers) and double freeing memory.  
* **Ease of Use**: Provide a simple interface for memory management without the need to manually allocate and deallocate.


---

### **What are Templates?**

Templates in C++ are a feature that allows the definition of generic functions and classes. This means you can write code that can work with any data type, improving code reuse and flexibility.

### **Types of Templates**

1. **Function Templates**:  
   * Allow the creation of functions that can operate with different data types.  
2. **Class Templates**:  
   * Allow the definition of classes that can handle different data types.

   ### **Advantages of Using Templates**

* **Code Reuse**: Allow writing code that can work with any type, eliminating the need to duplicate functions or classes for different types.  
* **Type Safety**: The compiler checks types at compile time, helping to detect errors before execution.  
* **Flexibility**: Facilitate the creation of data structures and algorithms that are independent of specific data types.

  ### **Limitations**

* **Generated Code**: Templates can generate larger code if used with many different types, as the compiler creates a separate instance for each type used.  
* **Complexity**: They can make the code harder to understand, especially for developers who are not familiar with their use.

