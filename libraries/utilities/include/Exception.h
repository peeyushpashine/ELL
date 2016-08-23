////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     Exception.h (utilities)
//  Authors:  Ofer Dekel
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <exception>

namespace utilities
{
    /// <summary> Base class for exceptions. </summary>
    class Exception : public std::exception
    {
    public:
        virtual ~Exception() = default;
        
        /// <summary> Gets the message. </summary>
        ///
        /// <returns> A message string; </returns>
        virtual const std::string& GetMessage() const noexcept = 0;
    };

    /// <summary> Base class for exceptions with error codes. </summary>
    ///
    /// <typeparam name="ErrorCodeType"> An enum class with error codes. </typeparam>
    template <typename ErrorCodeType>
    class ErrorCodeException : public Exception
    {
    public:
        /// <summary> Constructs an exception with a give error code from the enum ErrorCodeType. </summary>
        ///
        /// <param name="errorCode"> The error code from ErrorCodeType. </param>
        /// <param name="message"> A message. </param>
        ErrorCodeException(ErrorCodeType errorCode, const std::string& message = "");

        /// <summary> Gets the error code. </summary>
        ///
        /// <returns> The error code. </returns>
        ErrorCodeType GetErrorCode() const noexcept { return _errorCode; };

        /// <summary> Gets the message. </summary>
        ///
        /// <returns> A message string; </returns>
        virtual const std::string& GetMessage() const noexcept override { return _message; }

    private:
        ErrorCodeType _errorCode;
        std::string _message;
    };

    /// <summary> Error codes for exceptions that are the programmer's fault, namely, things that are known at compile time. </summary>
    enum class LogicExceptionErrors
    {
        illegalState,
        notImplemented
    };

    /// <summary> Error codes for exceptions that are the system's fault (missing files, serial ports, TCP ports, etc). </summary>
    enum class SystemExceptionErrors
    {
        fileNotFound,
        serialPortUnavailable
    };

    /// <summary> Error codes for exceptions due to the numeric values in the data. </summary>
    enum class NumericExceptionErrors
    {
        divideByZero,
        overflow,
        didNotConverge
    };

    /// <summary> Error codes for exceptions related to inputs, such as public API calls or the format of files. </summary>
    enum class InputExceptionErrors
    {
        badStringFormat,
        badData,
        indexOutOfRange,
        invalidArgument,
        nullReference,
        typeMismatch
    };

    typedef ErrorCodeException<LogicExceptionErrors> LogicException;
    typedef ErrorCodeException<SystemExceptionErrors> SystemException;
    typedef ErrorCodeException<NumericExceptionErrors> NumericException;
    typedef ErrorCodeException<InputExceptionErrors> InputException;
}

#include "../tcc/Exception.tcc"
