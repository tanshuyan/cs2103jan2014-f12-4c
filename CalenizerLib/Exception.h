//Exception.h
//v1.0
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

#define EXCEPTION_CONSTRUCTOR :std::exception(desc) {}

class InvalidDateTimeException:public std::exception{
public:
        InvalidDateTimeException();
        InvalidDateTimeException(char* desc) EXCEPTION_CONSTRUCTOR
};

class InvalidTaskIDException:public std::exception{
public:
        InvalidTaskIDException();
        InvalidTaskIDException(char* desc) EXCEPTION_CONSTRUCTOR
};

class CannotUndoException:public std::exception{
public:
        CannotUndoException();
        CannotUndoException(char* desc) EXCEPTION_CONSTRUCTOR
};

class CannotRedoException:public std::exception{
public:
        CannotRedoException();
        CannotRedoException(char* desc) EXCEPTION_CONSTRUCTOR
};
#endif