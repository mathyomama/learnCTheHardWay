A txt document for anything that comes up while learning c

"inline function": inline tells the compiler that the function, when called, should be directly replaced by the actual function body (inline expansion). The compiler is not obligated to respect that request.

"static function": static in context to functions means the function can only be referenced in the file in which it was initialized. So static is used to hide certain functions from other parts of the code.

"static variable in a function": (question of scope vs. lifetime) the scope will be within the codeblocks (curly braces).The lifetime changes from the lifetime of the function call to the lifetime of the program when static is invoked on a variable.

"static global variable": The variable becomes private to the file when static is thrown in front of it. This essentially limits the scope of the variable to which file it belongs (just like a static function).

"extern": used (mostly in header files) to show that the variable/function will be used in another place (read as file). This is automatic for functions. This forces a declaration. 
