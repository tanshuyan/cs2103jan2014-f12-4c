//Exception.h
//v1.0
#include <exception>

#define EXCEPTION_STRING_CONSTRUCTOR :std::exception(desc) {}

class InvalidTaskIDException:public std::exception{
public:
        InvalidTaskIDException();
        InvalidTaskIDException(char* desc) EXCEPTION_STRING_CONSTRUCTOR
};

class CannotUndoException:public std::exception{
public:
        CannotUndoException();
        CannotUndoException(char* desc) EXCEPTION_STRING_CONSTRUCTOR
};

class CannotRedoException:public std::exception{
public:
        CannotRedoException();
        CannotRedoException(char* desc) EXCEPTION_STRING_CONSTRUCTOR
};

class InvalidDateStdStrException:public std::exception{
public:
        InvalidDateStdStrException();
        InvalidDateStdStrException(char* desc) EXCEPTION_STRING_CONSTRUCTOR
};

class InvalidTimeStdStrException:public std::exception{
public:
        InvalidTimeStdStrException();
        InvalidTimeStdStrException(char* desc) EXCEPTION_STRING_CONSTRUCTOR
};
