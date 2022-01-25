#ifndef UNTITLED_NANOID_H
#define UNTITLED_NANOID_H

#include <cstdint>
#include <string>
#include <random>
#include <cstdlib>
#include <stdexcept>

namespace nanoid {

    /**
     * Generator of cryptographically strong random data
     */
    class RandomGenerator {
    private:
        using StdGenerator = std::mt19937;
        using result_type = StdGenerator::result_type;

        StdGenerator _gen32;
    public:
        RandomGenerator() : _gen32(std::random_device()()) {}

        /**
         * Generate random integer
         */
        uint32_t randomInt32() {
            return _gen32();
        }

        uint32_t randomInt32(uint32_t min, uint32_t max) {
            std::uniform_int_distribution<int> range(min, max);
            return range(_gen32);
        }

        /**
         * Fill the buffer with random bytes
         */
        void randomBytes(std::uint8_t* buffer, std::size_t size) {
            // Calculate how many full random data fit into the buffer
            std::size_t reps = (size / sizeof(result_type)) * sizeof(result_type);
            std::size_t i = 0;
            // Fill buffer with full parts of random data
            for (; i < reps; i += sizeof(result_type)) {
                *(result_type*)(buffer + i) = randomInt32();
            }
            if (i == size) return;
            // Fill remaning
            auto last = randomInt32();
            for (; i < size; ++i) {
                *(buffer + i) = (std::uint8_t)((last >> (8 * (i - reps))));
            }
        }
    };


    /**
     * Random ID generator
     */
    class NanoId {
    private:
        static inline const std::string DEFAULT_ALPHABET = "_-0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        static inline const std::size_t DEFAULT_SIZE = 21;

        RandomGenerator mGenerator;
    public:

        std::string generate() {
            return generate(DEFAULT_ALPHABET, DEFAULT_SIZE);
        }

        std::string generate(const std::string& alphabet) {
            return generate(alphabet, DEFAULT_SIZE);
        }

        std::string generate(std::size_t size) {
            return generate(DEFAULT_ALPHABET, size);
        }

        std::string generate(const std::string& alphabet, std::size_t resultSize) {
            if (alphabet.empty() || alphabet.size() >= 256) {
                throw std::invalid_argument("alphabet must contain between 1 and 255 symbols.");
            }
            if (resultSize <= 0) {
                throw std::invalid_argument("resultSize must be greater than zero.");
            }

            std::size_t alphabetSize = alphabet.size();

            // See https://github.com/ai/nanoid/blob/master/format.js for
            // explanation why masking is use (`random % alphabet` is a common
            // mistake security-wise).
            const std::size_t mask = (2 << (31 - clz32((int) ((alphabetSize - 1) | 1)))) - 1;
            const std::size_t step = (std::size_t) std::ceil(1.6 * mask * resultSize / alphabetSize);

            auto idBuilder = std::string(resultSize, '_');
            auto bytes = std::vector<std::uint8_t>(step);

            std::size_t cnt = 0;

            while (true) {
                mGenerator.randomBytes(bytes.data(), bytes.size());

                for (std::size_t i = 0; i < step; i++) {
                    std::size_t alphabetIndex = bytes[i] & mask;

                    if (alphabetIndex >= alphabetSize) continue;
                    idBuilder[cnt] = alphabet[alphabetIndex];
                    if (++cnt == resultSize) {
                        return idBuilder;
                    }
                }
            }
        }

    private:
        /**
         * Leading zeros calculation
         * @see https://stackoverflow.com/a/10439333/7000051
         */
        int clz32(int x) {
            const int numIntBits = sizeof(int) * 8; //compile time constant
            //do the smearing
            x |= x >> 1;
            x |= x >> 2;
            x |= x >> 4;
            x |= x >> 8;
            x |= x >> 16;
            //count the ones
            x -= x >> 1 & 0x55555555;
            x = (x >> 2 & 0x33333333) + (x & 0x33333333);
            x = (x >> 4) + x & 0x0f0f0f0f;
            x += x >> 8;
            x += x >> 16;
            return numIntBits - (x & 0x0000003f); //subtract # of 1s from 32
        }
    };

}
#endif //UNTITLED_NANOID_H
