### **Unreal Engine Reflection System**

The Unreal Engine reflection system allows the engine to obtain information about classes and their properties at runtime. This is fundamental for many engine features, such as editor editing, serialization, and integration with Blueprints.

#### **Main Components:**

1. **Reflection Macros**:  
   * It uses macros like `UCLASS`, `UPROPERTY`, and `UFUNCTION` to mark classes, properties, and functions. These macros enable the reflection system to automatically generate the necessary information about these elements.  
2. **UClass**:  
   * Represents metadata about a class. It allows access to information about the class, its properties, and methods at runtime.  
3. **UProperty**:  
   * Represents properties of a `UObject`. Thanks to the macros, these properties can be inspected and modified at runtime.  
   * When you declare a pointer to a `UObject` using `UPROPERTY`, you indicate to the GC to maintain a reference to that object. This means the GC will not delete it while there are references marked with `UPROPERTY`.  
4. **UFunction**:  
   * Allows for dynamic invocation of functions on `UObjects`. Functions marked with `UFUNCTION` can be called from other contexts, such as Blueprints.  
5. **Serialization**:  
   * The reflection system allows the engine to automatically serialize objects. This means that the data of `UObjects` can be efficiently saved and retrieved.  
6. **Editing in the Editor**:  
   * Allows properties marked with `UPROPERTY` to be visible and editable in the Unreal editor, facilitating the configuration and customization of actors and components.  
7. **Interoperability with Blueprints**:  
   * Facilitates the integration between C++ and Blueprints, allowing developers to expose their classes and functions to a visual environment.

   ---

   **What is the Garbage Collector?**

The Garbage Collector in Unreal Engine is a system that automatically manages memory by removing objects that are no longer needed to free resources. This helps prevent memory leaks and maintain game performance.

#### **How It Works:**

1. **References and Counters**:  
   * Unreal uses a reference counting system. Each object has a counter that increases when a new reference is created and decreases when a reference is destroyed.  
   * When an object's reference counter reaches zero, it means there are no more references to that object, and it can be marked for deletion.

2. **Marking and Collection**:  
   * The GC performs a "marking" process where it traverses all objects accessible from roots (like actors in the scene) and marks those that are still reachable.  
   * Afterward, any object not marked is collected, freeing the memory it occupied.

3. **Collection Cycle**:  
   * The GC runs periodically but can also be invoked manually if needed. This can be useful in specific situations to free memory at critical moments.

   

4. **Support for C++ and Blueprints**:  
   * Unreal supports object collection in both C++ and Blueprints. For an object to be collected, it must be derived from `UObject`.  
   * References to objects must be properly managed using smart pointers like `TWeakObjectPtr` to avoid cyclic references that can cause memory leaks.

   #### 

   ---

   **Garbage Collector vs. Manual Memory Management**

**Memory Management**:

* **C++**: In C++, you as the developer are responsible for managing memory manually. This means you must use `new` to create objects and `delete` to free them. If you forget to call `delete`, you can have memory leaks; if you call `delete` more than once or on objects still in use, you can cause access errors (dangling pointers).  
* **Unreal Engine**: Unreal uses a Garbage Collection system to manage the memory of `UObject`. When a `UObject` has no more references (i.e., its reference counter reaches zero), the GC automatically frees it. This simplifies memory management and helps prevent common C++ errors.

**Strong and Weak References**:

* **C++**: There is no concept of "strong" or "weak" references in pure C++. A normal pointer is simply that, a pointer, and there is no automatic management of the object's lifetime to which it points.  
* **Unreal Engine**: It uses `TWeakObjectPtr` and other types of smart pointers that handle weak references, allowing objects to be removed by the GC without causing invalid accesses. This helps avoid memory leaks in situations where objects may reference each other.

**Declarations and Serialization**:

* **C++**: Serialization (saving the state of an object) and exposing it to a graphical editor must be implemented manually or using external libraries.  
* **Unreal Engine**: By using `UPROPERTY`, objects are automatically serialized, allowing them to be saved and edited in the Unreal editor. This is not natively available in C++.

**Cleanup Code Execution**:

**C++**: You must implement destructors and ensure resources are appropriately freed when objects go out of scope.

**Unreal Engine**: The GC automatically handles cleanup. While you can still implement destructors, you don’t have to worry about freeing memory for `UObject` as you would in C++.

