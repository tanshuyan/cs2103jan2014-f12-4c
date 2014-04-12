//@author A0004695A

//Exception.h

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

#define EXCEPTION_CONSTRUCTOR :std::exception(desc) {}

class InvalidDateTimeException:public std::exception{
public:
        InvalidDateTimeException();
        InvalidDateTimeException(const char* desc) EXCEPTION_CONSTRUCTOR
};

class InvalidTaskIDException:public std::exception{
public:
        InvalidTaskIDException();
        InvalidTaskIDException(const char* desc) EXCEPTION_CONSTRUCTOR
};

class CannotUndoException:public std::exception{
public:
        CannotUndoException();
        CannotUndoException(const char* desc) EXCEPTION_CONSTRUCTOR
};

class CannotRedoException:public std::exception{
public:
        CannotRedoException();
        CannotRedoException(const char* desc) EXCEPTION_CONSTRUCTOR
};

class InvalidTaskException:public std::exception{
public:
        InvalidTaskException();
        InvalidTaskException(const char* desc) EXCEPTION_CONSTRUCTOR
};

class EmptyMessageException:public std::exception{
public:
        EmptyMessageException();
        EmptyMessageException(const char* desc) EXCEPTION_CONSTRUCTOR
};
#endif