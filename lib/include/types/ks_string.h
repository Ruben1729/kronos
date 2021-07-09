#pragma once

#include "asf.h"

namespace kronos {

    class String {
    private:
        String(const char* str, bool deallocate)
            : m_Deallocate(deallocate), m_String(str) {
            int i = 0;
            while (str[i] != '\0')
                i++;
            m_Length = i;
        }

    public:
        String(const char* str)
            : m_Deallocate(false), m_String(str) {
            int i = 0;
            while (str[i] != '\0')
                i++;
            m_Length = i;
        }

        String(const String& from)
            : m_Deallocate(true), m_Length(from.m_Length) {
            char * str = new char[m_Length + 1];
            // TODO: Replace with memory copying function
            for (size_t i = 0; i < m_Length + 1; i++)
                str[i] = from.m_String[i];
            m_String = str;
        }

        ~String() {
            if (m_Deallocate) {
                delete[] m_String;
            }
        }

        const char* Ptr() const { return m_String; }
        size_t Size() const { return m_Length; }

        size_t Hash() const {
            size_t hash = 5381;
            for (size_t i = 0; i < m_Length; i++)
                hash = hash * 33 + m_String[i];
            return hash;
        }

        static String Concatenate(const String& first, const String& second) {
            char * newStr = new char[first.m_Length + second.m_Length + 1];

            // TODO: Replace with memory copying functions
            for (uint32_t i = 0; i < first.m_Length; i++)
                newStr[i] = first.m_String[i];
            for (uint32_t i = 0; i < second.m_Length; i++)
                newStr[first.m_Length + i] = second.m_String[i];

            newStr[first.m_Length + second.m_Length] = '\0';

            return String(newStr, true);
        }

        friend String operator+(const String& left, const String& right) {
            return String::Concatenate(left, right);
        }

        String& operator+=(const String& right) {
            *this = Concatenate(*this, right);
            return *this;
        }

        String& operator=(const String& other) {
            if (this == &other)
                return *this;

            // Delete previous buffer
            if (m_Deallocate) {
                delete[] m_String;
            }

            // Allocate new buffer
            char * newStr = new char[other.m_Length + 1];
            m_Length = other.m_Length;
            m_Deallocate = true;

            // TODO: Replace with memory copying function
            for (size_t i = 0; i < other.m_Length + 1; i++)
                newStr[i] = other.m_String[i];

            m_String = newStr;
            return *this;
        }

        friend bool operator==(const String& lhs, const String& rhs) {
            if (lhs.m_Length != rhs.m_Length) {
                return false;
            }
            for (size_t i = 0; i < lhs.m_Length + 1; i++) {
                if (lhs.m_String[i] != rhs.m_String[i]) {
                    return false;
                }
            }
            return true;
        }

        friend bool operator!=(const String& lhs, const String& rhs) {
            return !(lhs == rhs);
        }

        char operator[](size_t idx) {
            return m_String[idx];
        }

    private:
        bool m_Deallocate;
        const char* m_String;
        size_t m_Length;
    };

}