#include <iostream>
#include <cstddef>
#include <cctype>
#include <cstring>

namespace yalovsky
{
    char * createString(size_t capacity)
    {
        if (capacity == 0)
        {
            return nullptr;
        }

        char * str = nullptr;
        try
        {
            str = new char[capacity];
        }
        catch (const std::bad_alloc &)
        {
            std::cerr << "bad alloc\n";
            return nullptr;
        }
        return str;
    }

    char * readLine(std::istream & input)
    {
        const size_t kInitialCapacity = 64;
        size_t capacity = kInitialCapacity;
        size_t length = 0;

        char * buffer = createString(capacity);
        if (!buffer)
        {
            return nullptr;
        }

        char currentChar = 0;
        bool wasSkipws = input.flags() & std::ios_base::skipws;

        if (wasSkipws)
        {
            input >> std::noskipws;
        }

        while (input.get(currentChar) && currentChar != '\n')
        {
            if (length + 1 >= capacity)
            {

                size_t newCapacity = capacity * 2;
                char * newBuffer = createString(newCapacity);
                if (!newBuffer)
                {
                    delete[] buffer;
                    return nullptr;
                }

                for (size_t i = 0; i < length; ++i)
                {
                    newBuffer[i] = buffer[i];
                }

                delete[] buffer;
                buffer = newBuffer;
                capacity = newCapacity;
            }

            buffer[length] = currentChar;
            ++length;
        }

        buffer[length] = '\0';

        if (wasSkipws)
        {
            input >> std::skipws;
        }

        return buffer;
    }

    char * removeVowels(const char * source)
    {
        if (!source)
        {
            return nullptr;
        }

        size_t sourceLength = std::strlen(source);
        char * result = createString(sourceLength + 1);
        if (!result)
        {
            return nullptr;
        }

        size_t resultIndex = 0;
        for (size_t i = 0; i < sourceLength; ++i)
        {
            char currentChar = source[i];
            bool isVowel = false;


            if (std::isalpha(static_cast<unsigned char>(currentChar)))
            {
                char lowerChar = std::tolower(static_cast<unsigned char>(currentChar));
                switch (lowerChar)
                {
                    case 'a':
                    case 'e':
                    case 'i':
                    case 'o':
                    case 'u':
                    case 'y':
                        isVowel = true;
                        break;
                    default:
                        break;
                }
            }

            if (!isVowel)
            {
                result[resultIndex] = currentChar;
                ++resultIndex;
            }
        }

        result[resultIndex] = '\0';
        return result;
    }
}
