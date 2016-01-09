#ifndef ERRORS_H
#define ERRORS_H

#include <exception>

class BaseError : std::exception {};

// Errors for arguments
class ArgumentError : BaseError {};
class ArgumentShouldBeStrictPositive : ArgumentError {};

// Screen errors
class NotEnoughArgumentsError : ArgumentError {};

// Game errors
class BadWorldSizeException : ArgumentError {};

// Entity errors
class NoTextureArgument : ArgumentError {};

// File errors
class FileException : BaseError {};
class TextureFileException : FileException {};

#endif /* ERRORS_H */