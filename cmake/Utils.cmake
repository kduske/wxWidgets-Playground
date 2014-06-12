MACRO(SET_XCODE_ATTRIBUTES TARGET)
    # Configure C++
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++98")
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libstdc++")
	# Set Debug information format
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=Debug] "dwarf-with-dsym")
    # Set some warnings
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_CLANG_WARN_EMPTY_BODY YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_WARN_SHADOW YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_WARN_64_TO_32_BIT_CONVERSION YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_CLANG_WARN_IMPLICIT_SIGN_CONVERSION YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_WARN_INITIALIZER_NOT_FULLY_BRACKETED YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_WARN_ABOUT_RETURN_TYPE YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_WARN_MISSING_PARENTHESES YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_WARN_ABOUT_MISSING_PROTOTYPES YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_WARN_ABOUT_MISSING_NEWLINE YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_WARN_SIGN_COMPARE YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_CLANG_WARN_SUSPICIOUS_IMPLICIT_CONVERSION YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_TREAT_INCOMPATIBLE_POINTER_TYPE_WARNINGS_AS_ERRORS YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_TREAT_IMPLICIT_FUNCTION_DECLARATIONS_AS_ERRORS YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_WARN_UNINITIALIZED_AUTOS YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_WARN_UNUSED_FUNCTION YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_WARN_UNUSED_LABEL YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_WARN_UNUSED_VALUE YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_WARN_UNUSED_VARIABLE YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_WARN_NON_VIRTUAL_DESTRUCTOR YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_WARN_HIDDEN_VIRTUAL_FUNCTIONS YES)
    SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_WARN_CXX0X_EXTENSIONS YES)

    IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
        SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH YES)
    ELSE()
        SET_TARGET_PROPERTIES(${TARGET} PROPERTIES XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH NO)
    ENDIF()
ENDMACRO(SET_XCODE_ATTRIBUTES)

MACRO(ADD_TARGET_PROPERTY TARGET PROPERTY VALUE)
    GET_TARGET_PROPERTY(CURRENT_VALUE ${TARGET} ${PROPERTY})
    IF(NOT CURRENT_VALUE)
        SET_PROPERTY(TARGET ${TARGET} PROPERTY ${PROPERTY} ${VALUE})
    ELSE()
        LIST(APPEND CURRENT_VALUE ${VALUE})
        SET_PROPERTY(TARGET ${TARGET} PROPERTY ${PROPERTY} ${CURRENT_VALUE})
    ENDIF()
ENDMACRO(ADD_TARGET_PROPERTY)
