A txt document for anything that comes up while learning c

"inline function": inline tells the compiler that the function, when called, should be directly replaced by the actual function body (inline expansion). The compiler is not obligated to respect that request.

"static function": static in context to functions means the function can only be referenced in the file in which it was initialized. So static is used to hide certain functions from other parts of the code. Also note that if a static function is defined in a header file, that function can be used in source code which includes the header file since the preprocessor creates a single translational/compilational unit in which has the static function is defined. This contrasts from writing a static function in a source code which will be compiled into an object file (and subsequently used in the "main" file).

"static variable in a function": (question of scope vs. lifetime) the scope will be within the codeblocks (curly braces).The lifetime changes from the lifetime of the function call to the lifetime of the program when static is invoked on a variable.

"static global variable": The variable becomes private to the file when static is thrown in front of it. This essentially limits the scope of the variable to which file it belongs (just like a static function).

"extern": used (mostly in header files) to show that the variable/function will be used in another place (read as file). This is automatic for functions. This forces a declaration.

"union": datatype for joining datatypes. Unions are defined like structs syntactically (except replace "struct" with "union"). Rather than having a collection of data storing memory in a struct, each data refers to the same block of memory (so each datatype is like a flavor of that piece of memory). This can save space and make conversions simpler, I guess.

